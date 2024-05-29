#include "bluesky.h"

#include <cpr/cpr.h>
#include <json/json.h>

Bluesky::Bluesky() = default;

Bluesky::~Bluesky() = default;

static inline Either<BlueskyError, Json::Value> parseRequest(const cpr::Response &r) {
    if (r.error) {
        return BlueskyError{"NetworkError", r.error.message};
    }

    Json::Value parsed_json;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING err;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

    if (!reader->parse(r.text.c_str(),
                       r.text.c_str() + r.text.length(),
                       &parsed_json, &err)) {
        return BlueskyError{"JsonParseError", err};
    }

    if (r.status_code >= 400) {
        return BlueskyError{
                parsed_json["error"].asString(),
                parsed_json["message"].asString()};
    }

    return parsed_json;
}

std::optional<BlueskyError> Bluesky::signUp(
        const std::string &provider,
        const std::string &identifier,
        const std::string &password) {
    /* Unimplemented! */
    throw std::exception();
}

std::optional<BlueskyError> Bluesky::signIn(
        const std::string &provider,
        const std::string &identifier,
        const std::string &password) {
    cpr::Response r = cpr::Post(
            cpr::Url{provider + "/xrpc/com.atproto.server.createSession"},
            cpr::Body{R"({"identifier": ")" + identifier + R"(", "password": ")" + password + "\"}"},
            cpr::Header{{"Content-Type", "application/json"}});

    auto parse_result = parseRequest(r);
    Json::Value parsed_json;
    if (!parse_result.isSuccess) {
        return parse_result.getError();
    } else {
        parsed_json = std::move(parse_result.getSuccess());
    }

    session = {
            .did = parsed_json["did"].asString(),
            .handle = parsed_json["handle"].asString(),
            .email = parsed_json["email"].asString(),
            .emailConfirmed = parsed_json["emailConfirmed"].asBool(),
            .emailAuthFactor = parsed_json["emailAuthFactor"].asBool(),
            .accessJWT = parsed_json["accessJwt"].asString(),
            .refreshJWT = parsed_json["refreshJwt"].asString(),
            .provider = provider,
    };

    return {};
}

Either<BlueskyError, BlueskyProfile> Bluesky::getProfile() const {
    cpr::Response r = cpr::Get(
            cpr::Url{session.provider + "/xrpc/app.bsky.actor.getProfile?actor=" + session.did},
            cpr::Header{{"Content-Type", "application/json"}},
            cpr::Header{{"authorization", "Bearer " + session.accessJWT}});

    auto parse_result = parseRequest(r);
    Json::Value parsed_json;
    if (!parse_result.isSuccess) {
        return parse_result.getError();
    } else {
        parsed_json = std::move(parse_result.getSuccess());
    }

    return BlueskyProfile{
            .did = parsed_json["did"].asString(),
            .handle = parsed_json["handle"].asString(),
            .displayName = parsed_json["displayName"].asString(),
            .avatar = parsed_json["avatar"].asString(),
            .followersCount = parsed_json["followersCount"].asUInt64(),
            .followsCount = parsed_json["followsCount"].asUInt64(),
            .postsCount = parsed_json["postsCount"].asUInt64(),
    };
}

static inline constexpr enum BlueskyNotification::Reason notificationReasonToEnum(const std::string &reason) {
    if (reason == "like")
        return BlueskyNotification::Reason::LIKE;
    else if (reason == "repost")
        return BlueskyNotification::Reason::REPOST;
    else if (reason == "follow")
        return BlueskyNotification::Reason::FOLLOW;
    else if (reason == "mention")
        return BlueskyNotification::Reason::MENTION;
    else if (reason == "reply")
        return BlueskyNotification::Reason::REPLY;
    else if (reason == "quote")
        return BlueskyNotification::Reason::QUOTE;
    else
        throw std::logic_error("Unknown notification reason!");
}

Either<BlueskyError, std::vector<BlueskyNotification>> Bluesky::fetchNotifications(u_int64_t limit) const {
    cpr::Response r = cpr::Get(
            cpr::Url{session.provider + "/xrpc/app.bsky.notification.listNotifications?limit=" + std::to_string(limit)},
            cpr::Header{{"Content-Type", "application/json"}},
            cpr::Header{{"authorization", "Bearer " + session.accessJWT}});

    auto parse_result = parseRequest(r);
    Json::Value parsed_json;
    if (!parse_result.isSuccess) {
        return parse_result.getError();
    } else {
        parsed_json = std::move(parse_result.getSuccess());
    }

    std::vector<BlueskyNotification> notifications;
    for (const auto &notification: parsed_json["notifications"]) {
        notifications.push_back({
                .uri = notification["uri"].asString(),
                .cid = notification["cid"].asString(),
                .author = {
                        .did = notification["author"]["did"].asString(),
                        .handle = notification["author"]["handle"].asString(),
                        .displayName = notification["author"]["displayName"].asString(),
                        .avatar = notification["author"]["avatar"].asString(),
                        .viewer = {
                                .muted = notification["author"]["viewer"]["muted"].asBool(),
                                .blockedBy = notification["author"]["viewer"]["blockedBy"].asBool(),
                                .followedBy = notification["author"]["viewer"]["followedBy"].asString(),
                        },
                },
                .reason = notificationReasonToEnum(notification["reason"].asString()),
                .reasonAsString = notification["reason"].asString(),
                .isRead = notification["isRead"].asBool(),
                .indexedAt = notification["indexedAt"].asString(),
        });
    }

    return notifications;
}

static inline constexpr enum BlueskyPreference::Type preferenceTypeToEnum(const std::string &type) {
    if (type == "feed")
        return BlueskyPreference::Type::FEED;
    else if (type == "list")
        return BlueskyPreference::Type::LIST;
    else if (type == "timeline")
        return BlueskyPreference::Type::TIMELINE;
    else
        throw std::logic_error("Unknown preference type! (type: " + type + ")");
}

Either<BlueskyError, std::vector<BlueskyPreference>> Bluesky::fetchPreferences() const {
    cpr::Response r = cpr::Get(
            cpr::Url{session.provider + "/xrpc/app.bsky.actor.getPreferences"},
            cpr::Header{{"Content-Type", "application/json"}},
            cpr::Header{{"authorization", "Bearer " + session.accessJWT}});

    auto parse_result = parseRequest(r);
    if (!parse_result.isSuccess) {
        return parse_result.getError();
    }

    Json::Value parsed_json = std::move(parse_result.getSuccess());

    std::vector<BlueskyPreference> preferences;
    for (const auto &preference: parsed_json["preferences"]) {
        if (preference["$type"] == "app.bsky.actor.defs#savedFeedsPrefV2") {
            for (const auto &item: preference["items"]) {
                preferences.push_back({
                        .type = preferenceTypeToEnum(item["type"].asString()),
                        .typeString = item["type"].asString(),
                        .value = item["value"].asString(),
                        .pinned = item["pinned"].asBool(),
                });
            }
        }
    }

    return preferences;
}

Either<BlueskyError, BlueskyFeed> Bluesky::fetchFeed(
        const std::string &at_uri,
        u_int64_t limit,
        const std::string &cursor) const {
    cpr::Response r = cpr::Get(
            cpr::Url{session.provider + "/xrpc/app.bsky.feed.getFeed?feed=" + at_uri +
                     "&limit=" + std::to_string(limit) +
                     (!cursor.empty() ? std::string("&cursor=" + cursor) : "")},
            cpr::Header{{"Content-Type", "application/json"}},
            cpr::Header{{"authorization", "Bearer " + session.accessJWT}});

    auto parse_result = parseRequest(r);
    if (!parse_result.isSuccess) {
        return parse_result.getError();
    }

    Json::Value parsed_json = std::move(parse_result.getSuccess());

    std::vector<BlueskyPost> posts;
    for (const auto &feed_item: parsed_json["feed"]) {
        const auto &feed = feed_item["post"];
        posts.push_back({
                .uri = feed["uri"].asString(),
                .cid = feed["cid"].asString(),
                .author = {
                        .did = feed["author"]["did"].asString(),
                        .handle = feed["author"]["handle"].asString(),
                        .displayName = feed["author"]["displayName"].asString(),
                        .avatar = feed["author"]["avatar"].asString(),
                        .replyCount = feed["author"]["replyCount"].asUInt64(),
                        .repostCount = feed["author"]["repostCount"].asUInt64(),
                        .likeCount = feed["author"]["likeCount"].asUInt64(),
                        .indexedAt = feed["author"]["indexedAt"].asString(),
                },
                .record = {
                        .type = feed["record"]["$type"].asString(),
                        .text = feed["record"]["text"].asString(),
                },
                .context = feed["context"].asString(),
        });
    }

    return (BlueskyFeed){.cursor = parsed_json["cursor"].asString(),
                         .posts = std::move(posts)};
}

Either<BlueskyError, BlueskyFeed> Bluesky::fetchFeed(const std::string &at_uri, u_int64_t limit) const {
    return fetchFeed(at_uri, limit, "");
}

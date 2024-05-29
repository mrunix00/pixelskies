#pragma once

#include "utils.h"
#include <optional>
#include <string>
#include <vector>

struct BlueskyPost {
    std::string uri;
    std::string cid;
    struct {
        std::string did;
        std::string handle;
        std::string displayName;
        std::string avatar;
        u_int64_t replyCount;
        u_int64_t repostCount;
        u_int64_t likeCount;
        std::string indexedAt;
    } author;
    struct {
        std::string type;
        std::string text;
    } record;
    std::string context;
};

struct BlueskyFeed {
    std::string cursor;
    std::vector<BlueskyPost> posts;
};

struct BlueskyPreference {
    enum class Type {
        FEED,
        LIST,
        TIMELINE,
    } type;
    std::string typeString;
    std::string value;
    bool pinned;
};

struct BlueskyNotification {
    std::string uri;
    std::string cid;
    struct {
        std::string did;
        std::string handle;
        std::string displayName;
        std::string avatar;
        struct {
            bool muted;
            bool blockedBy;
            std::string followedBy;
        } viewer;
    } author;
    enum class Reason {
        LIKE,
        REPOST,
        FOLLOW,
        MENTION,
        REPLY,
        QUOTE,
    } reason;
    std::string reasonAsString;
    struct {
        std::string type;
        std::string createdAt;
        std::string subject;
    } record;
    bool isRead;
    std::string indexedAt;
};

struct BlueskyError {
    std::string code{};
    std::string message{};
};

struct BlueskyProfile {
    std::string did;
    std::string handle;
    std::string displayName;
    std::string avatar;
    u_int64_t followersCount;
    u_int64_t followsCount;
    u_int64_t postsCount;
};

struct BlueskySession {
    std::string did;
    std::string handle;
    std::string email;
    bool emailConfirmed;
    bool emailAuthFactor;
    std::string accessJWT;
    std::string refreshJWT;
    std::string provider;
};

class Bluesky {
public:
    BlueskySession session{};

    Bluesky();

    ~Bluesky();

    std::optional<BlueskyError> signIn(
            const std::string &provider,
            const std::string &identifier,
            const std::string &password);

    std::optional<BlueskyError> signUp(
            const std::string &provider,
            const std::string &identifier,
            const std::string &password);

    [[nodiscard]] Either<BlueskyError, BlueskyProfile> getProfile() const;
    [[nodiscard]] Either<BlueskyError, std::vector<BlueskyNotification>> fetchNotifications(u_int64_t limit) const;
    [[nodiscard]] Either<BlueskyError, std::vector<BlueskyPreference>> fetchPreferences() const;
    [[nodiscard]] Either<BlueskyError, BlueskyFeed> fetchFeed(const std::string &at_uri, u_int64_t limit, const std::string &cursor) const;
    [[nodiscard]] Either<BlueskyError, BlueskyFeed> fetchFeed(const std::string &at_uri, u_int64_t limit) const;
};
#include "bluesky.h"
#include "cli/cli.h"
#include "cli/clifilesession.h"

int main() {
    auto rootMenu = std::make_unique<cli::Menu>("cli");
    Bluesky bluesky;

    cli::SetColor();
    rootMenu->Insert(
            "login", {"id", "password"},
            [&bluesky](std::ostream &out, const std::string &id, const std::string &password) {
                auto err = bluesky.signIn(
                        "https://bsky.social", id, password);
                if (err.has_value()) {
                    std::cerr << "Error: " << err->message << std::endl;
                } else {
                    out << "Logged-in as " << bluesky.session.handle << std::endl;
                }
            },
            "Log into Bluesky");
    rootMenu->Insert(
            "profile",
            [&bluesky](std::ostream &out) {
                auto result = bluesky.getProfile();
                if (!result.isSuccess) {
                    std::cerr << "Error: " << result.getError().message << std::endl;
                } else {
                    auto profile = result.getSuccess();
                    out << "==== Profile ====\n"
                        << "DID: " << profile.did << "\n"
                        << "Handle: " << profile.handle << "\n"
                        << "Display Name: " << profile.displayName << "\n"
                        << "Avatar: " << profile.avatar << "\n"
                        << "Followers: " << profile.followersCount << "\n"
                        << "Follows: " << profile.followsCount << "\n"
                        << "Posts: " << profile.postsCount << "\n";
                }
            },
            "Log into Bluesky");
    rootMenu->Insert(
            "notifications", {"count"},
            [&bluesky](std::ostream &out, int count) {
                auto result = bluesky.fetchNotifications(count);
                if (result.isSuccess) {
                    for (const auto &notification: result.getSuccess()) {
                        out << "==== Notification ====\n"
                            << "Type: " << notification.reasonAsString << "\n"
                            << "Author: " << notification.author.handle << "\n"
                            << "Time: " << notification.indexedAt << "\n"
                            << "Is read: " << (notification.isRead ? std::string("true") : std::string("false")) << '\n';
                    }
                } else {
                    std::cerr << "Error: " << result.getError().message << std::endl;
                }
            },
            "Fetch notifications");
    rootMenu->Insert(
            "preferences",
            [&bluesky](std::ostream &out) {
                auto result = bluesky.fetchPreferences();
                if (!result.isSuccess) {
                    std::cerr << "Error: " << result.getError().message << std::endl;
                } else {
                    auto preferences = result.getSuccess();
                    for (const auto &preference: preferences) {
                        out << "==== Preference ====\n"
                            << "Type: " << preference.typeString << "\n"
                            << "Value: " << preference.value << "\n";
                    }
                }
            },
            "Fetch preferences");
    rootMenu->Insert(
            "feed",
            [&bluesky](std::ostream &out) {
                auto result = bluesky.fetchPreferences();
                if (!result.isSuccess) {
                    std::cerr << "Error: " << result.getError().message << std::endl;
                } else {
                    auto preferences = result.getSuccess();
                    std::string feed_uri;
                    for (const auto &preference: preferences) {
                        if (preference.type == BlueskyPreference::Type::FEED) {
                            feed_uri = preference.value;
                            break;
                        }
                    }
                    auto feed = bluesky.fetchFeed(feed_uri, 5);
                    if (!feed.isSuccess) {
                        std::cerr << "Error: " << feed.getError().message << std::endl;
                    } else {
                        for (const auto &post: feed.getSuccess().posts) {
                            out << "==== Post ====\n"
                                << "Author: " << post.author.displayName << "(" << post.author.handle << ")\n"
                                << "Type: " << post.record.type << "\n"
                                << post.record.text << "\n";
                        }
                    }
                }
            },
            "Fetch preferences");

    cli::Cli cli(std::move(rootMenu));
    cli::CliFileSession input(cli);
    input.Start();

    return EXIT_SUCCESS;
}

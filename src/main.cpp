#include "bluesky.h"
#include <cli/cli.h>
#include <cli/clifilesession.h>

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

    cli::Cli cli(std::move(rootMenu));
    cli::CliFileSession input(cli);
    input.Start();

    return EXIT_SUCCESS;
}

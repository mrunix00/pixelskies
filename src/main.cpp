#include "bluesky.h"
#include <cli/cli.h>
#include <cli/clifilesession.h>

int main() {
    auto rootMenu = std::make_unique<cli::Menu>("cli");
    Bluesky bluesky;

    cli::SetColor();
    rootMenu->Insert(
            "hello",
            [](std::ostream &out) { out << "Hello, world\n"; },
            "Print hello world");
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

    cli::Cli cli(std::move(rootMenu));
    // global exit action
    cli.ExitAction([](auto &out) { out << "Goodbye and thanks for all the fish.\n"; });

    cli::CliFileSession input(cli);
    input.Start();

    return EXIT_SUCCESS;
}

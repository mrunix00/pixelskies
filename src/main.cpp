#include "bluesky.h"
#include <cli/cli.h>
#include <cli/clifilesession.h>

int main() {
    auto rootMenu = std::make_unique<cli::Menu>("cli");
    Bluesky bsky;

    cli::SetColor();
    rootMenu->Insert(
            "hello",
            [](std::ostream &out) { out << "Hello, world\n"; },
            "Print hello world");
    rootMenu->Insert(
            "login", {"id", "password"},
            [&bsky](std::ostream &out, const std::string &id, const std::string &password) {
                auto err = bsky.signIn(
                        "https://bsky.social", id, password);
                if (err.has_value()) {
                    std::cerr << "Error: " << err->message << std::endl;
                } else {
                    out << "Logged-in as " << bsky.session.handle << std::endl;
                }
            },
            "Log into Bluesky");
    rootMenu->Insert(
            "profile",
            [&bsky](std::ostream &out) {
                auto result = bsky.getProfile();
                if (result.isFailed()) {
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
            "answer",
            [](std::ostream &out, int x) { out << "The answer is: " << x << "\n"; },
            "Print the answer to Life, the Universe and Everything ");
    rootMenu->Insert(
            "nocolor",
            [](std::ostream &out) { out << "Colors OFF\n"; cli::SetNoColor(); },
            "Disable colors in the cli");

    auto subMenu = std::make_unique<cli::Menu>("sub");
    subMenu->Insert(
            "hello",
            [](std::ostream &out) { out << "Hello, submenu world\n"; },
            "Print hello world in the submenu");
    subMenu->Insert(
            "demo",
            [](std::ostream &out) { out << "This is a sample!\n"; },
            "Print a demo string");

    auto subSubMenu = std::make_unique<cli::Menu>("subsub");
    subSubMenu->Insert(
            "hello",
            [](std::ostream &out) { out << "Hello, subsubmenu world\n"; },
            "Print hello world in the sub-submenu");
    subMenu->Insert(std::move(subSubMenu));

    rootMenu->Insert(std::move(subMenu));


    cli::Cli cli(std::move(rootMenu));
    // global exit action
    cli.ExitAction([](auto &out) { out << "Goodbye and thanks for all the fish.\n"; });

    cli::CliFileSession input(cli);
    input.Start();

    return EXIT_SUCCESS;
}

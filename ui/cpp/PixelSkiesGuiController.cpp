#include "PixelSkiesGuiController.h"
#include <iostream>

PixelSkiesGuiController::PixelSkiesGuiController(QQmlApplicationEngine *engine, QObject *parent)
    : QObject(parent), engine(engine) {}

void PixelSkiesGuiController::signIn(const QString &identifier, const QString &password) {
    std::optional<BlueskyError> error = bluesky.signIn(
            "https://bsky.social",
            identifier.toStdString(),
            password.toStdString());
    if (error.has_value()) {
        std::cerr << "Error: " << error->code << " " << error->message << std::endl;
    } else {
        engine->rootObjects()[0]
                ->findChild<QObject *>("loader")
                ->setProperty("source", "HomePage.qml");
    }
}

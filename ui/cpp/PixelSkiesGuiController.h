#pragma once

#include "bluesky.h"
#include <QObject>
#include <QQmlApplicationEngine>

class PixelSkiesGuiController : public QObject {
    Q_OBJECT
private:
    Bluesky bluesky;
    QQmlApplicationEngine *engine;

public:
    explicit PixelSkiesGuiController(QQmlApplicationEngine *engine = nullptr, QObject *parent = nullptr);

signals:
public slots:
    void signIn(const QString &identifier, const QString &password);
};

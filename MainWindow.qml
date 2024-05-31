import QtQuick
import QtQuick.Controls
import "ui"

Window {
    width: 640
    height: 480
    visible: true
    title: "PixelSkies"
    color: "#161E27"

    BlueskyTextInput {
        anchors.centerIn: parent
        width: 400
        height: 40
    }
}

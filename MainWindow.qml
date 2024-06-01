import QtQuick
import "ui"

Window {
    width: 640
    height: 480
    visible: true
    title: "PixelSkies"
    color: "#161E27"

    Grid {
        anchors.centerIn: parent
        spacing: 20
        BlueskyTextInput {
            width: 400
        }
        BlueskyButton {
            label: "Submit"
            width: 100
        }

    }
}

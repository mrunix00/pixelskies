import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "PixelSkies"
    color: "#161E27"

    Text {
        id: welcome
        text: "Welcome to PixelSkies!"
        color: "#FFFFFF"
        height: 40
        font.pixelSize: 24
        verticalAlignment: Text.AlignVCenter
        anchors.centerIn: parent
    }
}

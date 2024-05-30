import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: "PixelSkies"
    color: "#161E27"

    Button {
        text: "Click me!"
        palette.buttonText: down ? "#454B52" : "#ffffff"
        anchors.centerIn: parent
        padding: 10
        background: Rectangle {
            color: parent.down ? "#123352" : "#208BFE"
            radius: 20
        }
    }
}

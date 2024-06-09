import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: "PixelSkies"
    color: "#161E27"

    Loader {
        objectName: "loader"
        anchors.fill: parent
        source: "LoginPage.qml"
    }
}

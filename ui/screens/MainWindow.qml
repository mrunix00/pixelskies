import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "PixelSkies"
    color: "#161E27"

    Loader {
        objectName: "loader"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 40
        anchors.rightMargin: 40
        source: "LoginPage.qml"
    }
}

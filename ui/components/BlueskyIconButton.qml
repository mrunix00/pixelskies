import QtQuick 6.2
import QtQuick.Controls.Material 6.2

Button {
    id: button
    Material.foreground: down ? "#3E4852" : "#ffffff"
    font.bold: true
    font.pixelSize: 24
    background: Rectangle {
        color: "#00000000"
        anchors.fill: parent
    }
}
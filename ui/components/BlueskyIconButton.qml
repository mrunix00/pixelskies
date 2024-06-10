import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material

Button {
    id: button
    Material.foreground: down ? "#3E4852" : "#ffffff"
    font.bold: true
    font.pixelSize: 24
    Layout.fillWidth: true
    display: width <= 75 ? AbstractButton.IconOnly : AbstractButton.TextBesideIcon
    background: Rectangle {
        color: "#00000000"
        anchors.fill: parent
    }
}
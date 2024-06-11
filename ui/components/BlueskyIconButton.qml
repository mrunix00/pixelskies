import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material

Button {
    id: button
    states: [
        State {
            when: parent.width <= 75
            PropertyChanges {
                target: button; display: AbstractButton.IconOnly
            }
            PropertyChanges {
                target: button; Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
        },
        State {
            when: parent.width > 75
            PropertyChanges {
                target: button; display: AbstractButton.TextBesideIcon
            }
            PropertyChanges {
                target: button; Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            }
        }
    ]
    Material.foreground: down ? "#3E4852" : "#ffffff"
    font.bold: true
    font.pixelSize: 20
    icon.width: 25
    icon.height: 25
    rightPadding: 25
    leftPadding: 25
    background: Rectangle {
        color: "#00000000"
        anchors.fill: parent
    }
}
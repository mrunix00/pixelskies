import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "../components"

Rectangle {
    color: "#00000000"
    ColumnLayout {
        spacing: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 40
        anchors.rightMargin: 40

        GridLayout {
            id: gridLayout
            uniformCellHeights: true
            columnSpacing: 20
            rowSpacing: 20
            columns: 2

            Text {
                id: idText
                text: "Identifier"
                color: "#FFFFFF"
                height: 40
                font.pixelSize: 24
                verticalAlignment: Text.AlignVCenter
            }
            BlueskyTextInput {
                id: idInput
                Layout.fillWidth: true
                nextTab: passwordInput
            }

            Text {
                id: passwordText
                text: "Password"
                color: "#FFFFFF"
                height: 40
                font.pixelSize: 24
                verticalAlignment: Text.AlignVCenter
            }
            BlueskyTextInput {
                id: passwordInput
                Layout.fillWidth: true
                obscured: true
                nextTab: idInput
            }
        }

        BlueskyButton {
            text: "Sign-in"
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            onClicked: gui.signIn(idInput.text, passwordInput.text)
        }
    }
}
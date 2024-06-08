import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "../components"

ColumnLayout {
    spacing: 20

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
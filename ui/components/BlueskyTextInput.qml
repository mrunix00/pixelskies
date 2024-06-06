import QtQuick

Item {
    property alias text: textInput.text
    property bool obscured: false
    property alias textInput: textInput
    property Item nextTab
    height: 40

    Rectangle {
        color: "#1E2936"
        radius: 20
        anchors.fill: parent
        y: textInput.cursorRectangle.y + 20
    }

    TextInput {
        id: textInput
        height: parent.height
        width: parent.width - 40
        x: 20
        text: text
        clip: true
        color: "#ffffff"
        selectionColor: "#3584E4"
        verticalAlignment: Text.AlignVCenter
        focus: true
        KeyNavigation.tab: nextTab.textInput
        echoMode: obscured ? TextInput.Password : TextInput.Normal
    }
}
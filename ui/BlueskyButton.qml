import QtQuick
import QtQuick.Controls

Item {
    property string label

    height: 40

    Button {
        id: button
        text: label
        palette.buttonText: down ? "#3E4852" : "#ffffff"
        height: parent.height
        topPadding: 10
        bottomPadding: 10
        leftPadding: 20
        rightPadding: 20
        background: Rectangle {
            anchors.fill: parent
            color: button.down ? "#123352" : "#208BFE"
            radius: 20
        }
    }
}
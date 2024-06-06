import QtQuick
import QtQuick.Controls

Button {
    id: button
    height: 40
    palette.buttonText: down ? "#3E4852" : "#ffffff"
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
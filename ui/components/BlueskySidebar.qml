import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle {
    property alias children: sidebarColumn.children
    border.color: "#2E4153"
    color: "#00000000"
    Layout.fillHeight: true
    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
    ColumnLayout {
        id: sidebarColumn
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.rightMargin: 0
    }
}
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "../components"

RowLayout {
    spacing: 0
    children: [
        BlueskySidebar {
            children: [
                BlueskyIconButton {
                    text: "Home"
                    icon.source: "qrc:/resources/material/home.svg"
                },
                BlueskyIconButton {
                    text: "Search"
                    icon.source: "qrc:/resources/material/search.svg"
                },
                BlueskyIconButton {
                    text: "Notifications"
                    icon.source: "qrc:/resources/material/notifications.svg"
                },
                BlueskyIconButton {
                    text: "Chat"
                    icon.source: "qrc:/resources/material/chat.svg"
                },
                BlueskyIconButton {
                    text: "Profile"
                    icon.source: "qrc:/resources/material/profile.svg"
                },
                BlueskyIconButton {
                    text: "Settings"
                    icon.source: "qrc:/resources/material/settings.svg"
                }
            ]
        },
        Rectangle {
            color: "#00000000"
            border.color: "#00000000"
            Layout.fillHeight: true
            Layout.fillWidth: true
            ColumnLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                children: [
                    Text {
                        text: "PixelSkies"
                        color: "#FFFFFF"
                        height: 40
                        font.pixelSize: 24
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        lineHeight: 1.5
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    },
                    Rectangle {
                        height: 1
                        Layout.fillWidth: true
                        color: "#2E4153"
                    }
                ]
            }
        }
    ]
}

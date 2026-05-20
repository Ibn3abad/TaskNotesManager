/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.9
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import TaskNotesManager
import "../components"

Item {
    id: root

    signal aboutRequested()

    property bool mobileMode: Qt.platform.os === "android" || width < 900

    RowLayout {
        anchors.fill: parent
        spacing: 0
        visible: !root.mobileMode

        Sidebar {
            Layout.preferredWidth: 260
            Layout.fillHeight: true
            onAboutRequested: root.aboutRequested()
        }

        TaskList {
            Layout.preferredWidth: 420
            Layout.fillHeight: true
        }

        NoteEditor {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Drawer {
        id: menuDrawer
        width: Math.min(root.width * 0.86, 340)
        height: root.height
        edge: i18n.rtl ? Qt.RightEdge : Qt.LeftEdge

        Sidebar {
            anchors.fill: parent
            onAboutRequested: {
                menuDrawer.close()
                root.aboutRequested()
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        visible: root.mobileMode

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 58
            color: "#0f172a"
            border.color: "#1e293b"
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                spacing: 10

                Button {
                    text: "☰"
                    Layout.preferredWidth: 48
                    onClicked: menuDrawer.open()
                    Accessible.name: i18n.language !== "" ? i18n.text("menu") : "Menu"
                }

                Label {
                    text: "TaskNest"
                    color: "#f8fafc"
                    font.pixelSize: 22
                    font.bold: true
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                }

                Button {
                    text: i18n.language !== "" ? i18n.text("about") : ""
                    onClicked: root.aboutRequested()
                }
            }
        }

        TabBar {
            id: mobileTabs
            Layout.fillWidth: true
            currentIndex: 0

            TabButton { text: i18n.language !== "" ? i18n.text("tasks") : "" }
            TabButton { text: i18n.language !== "" ? i18n.text("details") : "" }
        }

        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: mobileTabs.currentIndex

            TaskList {
                onTaskActivated: mobileTabs.currentIndex = 1
            }

            NoteEditor {}
        }
    }
}

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

Rectangle {
    id: root
    color: "#0f172a"

    signal aboutRequested()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 18
        spacing: 16

        Label {
            text: "TaskNest"
            color: "#f8fafc"
            font.pixelSize: 28
            font.bold: true
        }

        Label {
            text: i18n.language !== "" ? i18n.text("tagline") : ""
            color: "#94a3b8"
            font.pixelSize: 13
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: "#1e293b"
        }

        Label {
            text: i18n.language !== "" ? i18n.text("language") : ""
            color: "#cbd5e1"
            font.pixelSize: 12
            font.bold: true
        }

        ComboBox {
            id: languageBox
            Layout.fillWidth: true
            textRole: "label"
            valueRole: "code"
            model: [
                { label: "Deutsch", code: "de" },
                { label: "English", code: "en" },
                { label: "العربية", code: "ar" }
            ]
            Component.onCompleted: {
                for (var i = 0; i < model.length; ++i) {
                    if (model[i].code === i18n.language) {
                        currentIndex = i
                        break
                    }
                }
            }
            onActivated: i18n.language = currentValue
        }

        Label {
            text: i18n.language !== "" ? i18n.text("filters") : ""
            color: "#cbd5e1"
            font.pixelSize: 12
            font.bold: true
        }

        Repeater {
            model: [
                { labelKey: "allTasks", mode: "all" },
                { labelKey: "open", mode: "open" },
                { labelKey: "inProgress", mode: "in_progress" },
                { labelKey: "done", mode: "done" },
                { labelKey: "highPriority", mode: "high" }
            ]

            delegate: Rectangle {
                Layout.fillWidth: true
                height: 38
                radius: 10
                color: taskModel.filterMode === modelData.mode ? "#1d4ed8" : "transparent"
                border.color: taskModel.filterMode === modelData.mode ? "#60a5fa" : "transparent"
                border.width: 1

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 12
                    anchors.rightMargin: 12
                    text: i18n.language !== "" ? i18n.text(modelData.labelKey) : ""
                    color: taskModel.filterMode === modelData.mode ? "white" : "#cbd5e1"
                    font.pixelSize: 14
                    elide: Text.ElideRight
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        taskModel.setFilterMode(modelData.mode)
                        noteModel.loadForTask(taskModel.selectedTaskId)
                    }
                }
            }
        }

        Button {
            Layout.fillWidth: true
            text: i18n.language !== "" ? i18n.text("about") : ""
            onClicked: root.aboutRequested()
        }

        Item { Layout.fillHeight: true }

        Rectangle {
            Layout.fillWidth: true
            radius: 12
            color: "#111827"
            border.color: "#334155"
            border.width: 1
            height: 110

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 4

                Label {
                    text: i18n.language !== "" ? i18n.text("sqliteActive") : ""
                    color: "#22c55e"
                    font.bold: true
                }

                Label {
                    text: databaseManager.databasePath()
                    color: "#94a3b8"
                    font.pixelSize: 11
                    wrapMode: Text.WrapAnywhere
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }
}

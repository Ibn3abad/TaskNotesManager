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

    signal taskActivated()
    color: "#111827"
    border.color: "#1f2937"
    border.width: 1

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 18
        spacing: 12

        Label {
            text: i18n.language !== "" ? i18n.text("tasks") : ""
            color: "#f9fafb"
            font.pixelSize: 24
            font.bold: true
        }

        TextField {
            id: titleInput
            Layout.fillWidth: true
            placeholderText: i18n.language !== "" ? i18n.text("newTask") : ""
            color: "#f9fafb"
            placeholderTextColor: "#64748b"
            background: Rectangle {
                radius: 10
                color: "#1f2937"
                border.color: titleInput.activeFocus ? "#2563eb" : "#374151"
            }
            onAccepted: addButton.clicked()
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            ComboBox {
                id: priorityBox
                Layout.fillWidth: true
                textRole: "label"
                valueRole: "value"
                model: [
                    { label: i18n.language !== "" ? i18n.text("low") : "", value: "low" },
                    { label: i18n.language !== "" ? i18n.text("medium") : "", value: "medium" },
                    { label: i18n.language !== "" ? i18n.text("high") : "", value: "high" }
                ]
                currentIndex: 1
            }

            Button {
                id: addButton
                text: i18n.language !== "" ? i18n.text("add") : ""
                enabled: titleInput.text.trim().length > 0
                onClicked: {
                    taskModel.addTask(titleInput.text, "", priorityBox.currentValue)
                    titleInput.clear()
                    noteModel.loadForTask(taskModel.selectedTaskId)
                    todoModel.loadForTask(taskModel.selectedTaskId)
                    root.taskActivated()
                }
            }
        }

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 10
            model: taskModel

            delegate: TaskCard {
                width: ListView.view.width
                taskIdValue: taskId
                titleValue: title
                descriptionValue: description
                statusValue: status
                priorityValue: priority
                selectedValue: selected
                onSelectRequested: {
                    taskModel.selectTask(taskIdValue)
                    noteModel.loadForTask(taskIdValue)
                    todoModel.loadForTask(taskIdValue)
                    root.taskActivated()
                }
                onDeleteRequested: {
                    taskModel.deleteTask(taskIdValue)
                    noteModel.loadForTask(taskModel.selectedTaskId)
                    todoModel.loadForTask(taskModel.selectedTaskId)
                }
            }
        }
    }
}

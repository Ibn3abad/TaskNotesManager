/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.8
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: "#0b1120"

    Connections {
        target: taskModel
        function onSelectedTaskChanged() {
            noteModel.loadForTask(taskModel.selectedTaskId)
            todoModel.loadForTask(taskModel.selectedTaskId)
            editTitle.text = taskModel.selectedTaskTitle
            editDescription.text = taskModel.selectedTaskDescription
            statusBox.currentIndex = statusIndex(taskModel.selectedTaskStatus)
            editPriorityBox.currentIndex = priorityIndex(taskModel.selectedTaskPriority)
            noteTitle.clear()
            noteContent.clear()
            todoInput.clear()
            noteMode.currentIndex = 0
        }
    }

    function statusLabel(value) {
        if (value === "open") return i18n.text("open")
        if (value === "in_progress") return i18n.text("inProgress")
        if (value === "done") return i18n.text("done")
        return value
    }

    function priorityLabel(value) {
        if (value === "low") return i18n.text("low")
        if (value === "medium") return i18n.text("medium")
        if (value === "high") return i18n.text("high")
        return value
    }

    function statusIndex(value) {
        if (value === "in_progress") return 1
        if (value === "done") return 2
        return 0
    }

    function priorityIndex(value) {
        if (value === "low") return 0
        if (value === "high") return 2
        return 1
    }

    function addTodoFromInput() {
        if (taskModel.selectedTaskId.length > 0 && todoInput.text.trim().length > 0) {
            todoModel.addTodo(taskModel.selectedTaskId, todoInput.text)
            todoInput.clear()
        }
    }

    ScrollView {
        anchors.fill: parent
        clip: true

        ColumnLayout {
            width: Math.max(280, root.width - 32)
            anchors.margins: Qt.platform.os === "android" ? 12 : 22
            spacing: 12

            Label {
                text: taskModel.selectedTaskId.length > 0 ? taskModel.selectedTaskTitle : (i18n.language !== "" ? i18n.text("noTaskSelected") : "")
                color: "#f8fafc"
                font.pixelSize: 26
                font.bold: true
                Layout.fillWidth: true
                elide: Text.ElideRight
            }

            Label {
                text: taskModel.selectedTaskId.length > 0
                      ? (i18n.language !== "" ? (i18n.text("status") + ": " + root.statusLabel(taskModel.selectedTaskStatus) + "  |  " + i18n.text("priority") + ": " + root.priorityLabel(taskModel.selectedTaskPriority)) : "")
                      : (i18n.language !== "" ? i18n.text("selectTaskHint") : "")
                color: "#94a3b8"
                font.pixelSize: 13
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#1e293b"
            }

            GroupBox {
                title: i18n.language !== "" ? i18n.text("editTask") : ""
                Layout.fillWidth: true
                enabled: taskModel.selectedTaskId.length > 0

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 8

                    TextField {
                        id: editTitle
                        Layout.fillWidth: true
                        placeholderText: i18n.language !== "" ? i18n.text("title") : ""
                    }

                    TextArea {
                        id: editDescription
                        Layout.fillWidth: true
                        Layout.preferredHeight: 50
                        placeholderText: i18n.language !== "" ? i18n.text("description") : ""
                        wrapMode: TextArea.Wrap
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        ComboBox {
                            id: statusBox
                            Layout.fillWidth: true
                            textRole: "label"
                            valueRole: "value"
                            model: [
                                { label: i18n.language !== "" ? i18n.text("open") : "", value: "open" },
                                { label: i18n.language !== "" ? i18n.text("inProgress") : "", value: "in_progress" },
                                { label: i18n.language !== "" ? i18n.text("done") : "", value: "done" }
                            ]
                        }

                        ComboBox {
                            id: editPriorityBox
                            Layout.fillWidth: true
                            textRole: "label"
                            valueRole: "value"
                            model: [
                                { label: i18n.language !== "" ? i18n.text("low") : "", value: "low" },
                                { label: i18n.language !== "" ? i18n.text("medium") : "", value: "medium" },
                                { label: i18n.language !== "" ? i18n.text("high") : "", value: "high" }
                            ]
                        }
                    }

                    Button {
                        text: i18n.language !== "" ? i18n.text("saveChanges") : ""
                        enabled: taskModel.selectedTaskId.length > 0 && editTitle.text.trim().length > 0
                        onClicked: {
                            taskModel.updateTask(taskModel.selectedTaskId, editTitle.text, editDescription.text, statusBox.currentValue, editPriorityBox.currentValue)
                            noteModel.loadForTask(taskModel.selectedTaskId)
                            todoModel.loadForTask(taskModel.selectedTaskId)
                        }
                    }
                }
            }

            GroupBox {
                title: i18n.language !== "" ? i18n.text("checklist") : ""
                Layout.fillWidth: true
                Layout.preferredHeight: Qt.platform.os === "android" ? 260 : 220
                enabled: taskModel.selectedTaskId.length > 0

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 8

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        TextField {
                            id: todoInput
                            Layout.fillWidth: true
                            placeholderText: i18n.language !== "" ? i18n.text("newTodo") : ""
                            onAccepted: root.addTodoFromInput()
                        }

                        Button {
                            id: addTodoButton
                            text: i18n.language !== "" ? i18n.text("addTodo") : ""
                            enabled: taskModel.selectedTaskId.length > 0 && todoInput.text.trim().length > 0
                            onClicked: root.addTodoFromInput()
                        }
                    }

                    Label {
                        text: i18n.language !== "" ? (i18n.text("todoProgress") + ": " + todoModel.doneCount + " " + i18n.text("todosDone") + ", " + todoModel.openCount + " " + i18n.text("todosOpen")) : ""
                        color: "#94a3b8"
                        font.pixelSize: 12
                    }

                    ListView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true
                        spacing: 6
                        model: todoModel

                        delegate: Rectangle {
                            width: ListView.view.width
                            height: 42
                            radius: 10
                            color: done ? "#0f172a" : "#111827"
                            border.color: done ? "#1e293b" : "#334155"
                            border.width: 1

                            RowLayout {
                                anchors.fill: parent
                                anchors.leftMargin: 10
                                anchors.rightMargin: 8
                                spacing: 8

                                CheckBox {
                                    checked: done
                                    onClicked: todoModel.toggleTodo(todoId, checked)
                                }

                                Label {
                                    text: model.text
                                    color: done ? "#64748b" : "#f8fafc"
                                    font.strikeout: done
                                    Layout.fillWidth: true
                                    elide: Text.ElideRight
                                }

                                Button {
                                    text: "X"
                                    onClicked: todoModel.deleteTodo(todoId)
                                }
                            }
                        }
                    }
                }
            }

            GroupBox {
                title: i18n.language !== "" ? i18n.text("newNote") : ""
                Layout.fillWidth: true
                enabled: taskModel.selectedTaskId.length > 0

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 8

                    TextField {
                        id: noteTitle
                        Layout.fillWidth: true
                        placeholderText: i18n.language !== "" ? i18n.text("title") : ""
                    }

                    TabBar {
                        id: noteMode
                        Layout.fillWidth: true
                        currentIndex: 0

                        TabButton { text: i18n.language !== "" ? i18n.text("editMarkdown") : "" }
                        TabButton { text: i18n.language !== "" ? i18n.text("previewMarkdown") : "" }
                    }

                    StackLayout {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 120
                        currentIndex: noteMode.currentIndex

                        TextArea {
                            id: noteContent
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            placeholderText: i18n.language !== "" ? i18n.text("notePlaceholder") : ""
                            wrapMode: TextArea.Wrap
                            selectByMouse: true
                        }

                        Rectangle {
                            color: "#020617"
                            radius: 10
                            border.color: "#334155"
                            border.width: 1
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            ScrollView {
                                anchors.fill: parent
                                anchors.margins: 12
                                clip: true

                                Text {
                                    width: parent.width
                                    text: noteContent.text.length > 0 ? noteContent.text : (i18n.language !== "" ? i18n.text("markdownPreviewEmpty") : "")
                                    textFormat: Text.MarkdownText
                                    wrapMode: Text.WordWrap
                                    color: "#e5e7eb"
                                    linkColor: "#38bdf8"
                                    font.pixelSize: 14
                                    onLinkActivated: Qt.openUrlExternally(link)
                                }
                            }
                        }
                    }

                    Label {
                        text: i18n.language !== "" ? i18n.text("markdownHelp") : ""
                        color: "#94a3b8"
                        font.pixelSize: 11
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                    }

                    Button {
                        text: i18n.language !== "" ? i18n.text("saveNote") : ""
                        enabled: taskModel.selectedTaskId.length > 0 && (noteTitle.text.trim().length > 0 || noteContent.text.trim().length > 0)
                        onClicked: {
                            noteModel.addNote(taskModel.selectedTaskId, noteTitle.text, noteContent.text)
                            noteTitle.clear()
                            noteContent.clear()
                            noteMode.currentIndex = 0
                        }
                    }
                }
            }

            Label {
                text: i18n.language !== "" ? i18n.text("notes") : ""
                color: "#e5e7eb"
                font.pixelSize: 18
                font.bold: true
            }

            ListView {
                Layout.fillWidth: true
                Layout.preferredHeight: Math.max(260, contentHeight)
                clip: true
                spacing: 10
                model: noteModel

                delegate: Rectangle {
                    width: ListView.view.width
                    radius: 12
                    color: "#111827"
                    border.color: "#334155"
                    border.width: 1
                    height: Math.max(120, markdownText.implicitHeight + 88)

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 8

                        RowLayout {
                            Layout.fillWidth: true

                            Label {
                                text: title
                                color: "#f8fafc"
                                font.pixelSize: 15
                                font.bold: true
                                Layout.fillWidth: true
                                elide: Text.ElideRight
                            }

                            Label {
                                text: i18n.language !== "" ? i18n.text("markdownPreview") : ""
                                color: "#38bdf8"
                                font.pixelSize: 11
                            }

                            Button {
                                text: "X"
                                onClicked: noteModel.deleteNote(noteId)
                            }
                        }

                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: Math.max(50, markdownText.implicitHeight + 20)
                            color: "#020617"
                            radius: 10
                            border.color: "#1e293b"
                            border.width: 1

                            Text {
                                id: markdownText
                                anchors.fill: parent
                                anchors.margins: 10
                                text: content
                                textFormat: Text.MarkdownText
                                color: "#cbd5e1"
                                linkColor: "#38bdf8"
                                wrapMode: Text.WordWrap
                                font.pixelSize: 14
                                onLinkActivated: Qt.openUrlExternally(link)
                            }
                        }

                        Label {
                            text: updatedAt
                            color: "#64748b"
                            font.pixelSize: 10
                        }
                    }
                }
            }
        }
    }
}

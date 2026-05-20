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

    property string taskIdValue: ""
    property string titleValue: ""
    property string descriptionValue: ""
    property string statusValue: ""
    property string priorityValue: ""
    property bool selectedValue: false

    signal selectRequested()
    signal deleteRequested()

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

    radius: 14
    height: 92
    color: selectedValue ? "#1e3a8a" : "#1f2937"
    border.color: selectedValue ? "#60a5fa" : "#374151"
    border.width: 1

    MouseArea {
        anchors.fill: parent
        onClicked: root.selectRequested()
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 14
        spacing: 10

        Rectangle {
            Layout.preferredWidth: 8
            Layout.fillHeight: true
            radius: 4
            color: priorityValue === "high" ? "#ef4444" : priorityValue === "medium" ? "#f59e0b" : "#22c55e"
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 4

            Label {
                text: titleValue
                color: "#f9fafb"
                font.pixelSize: 16
                font.bold: true
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Label {
                text: descriptionValue.length > 0 ? descriptionValue : (i18n.language !== "" ? i18n.text("noDescription") : "")
                color: "#9ca3af"
                font.pixelSize: 12
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            RowLayout {
                spacing: 8
                Label { text: i18n.language !== "" ? root.statusLabel(statusValue) : ""; color: "#cbd5e1"; font.pixelSize: 11 }
                Label { text: "•"; color: "#64748b"; font.pixelSize: 11 }
                Label { text: i18n.language !== "" ? root.priorityLabel(priorityValue) : ""; color: "#cbd5e1"; font.pixelSize: 11 }
            }
        }

        Button {
            text: i18n.language !== "" ? i18n.text("delete") : ""
            onClicked: root.deleteRequested()
        }
    }
}

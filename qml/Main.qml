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
import QtQuick.Window
import TaskNotesManager

ApplicationWindow {
    id: root
    visible: true
    width: 1280
    height: 820
    minimumWidth: Qt.platform.os === "android" ? 0 : 900
    minimumHeight: Qt.platform.os === "android" ? 0 : 600
    visibility: Qt.platform.os === "android" ? Window.FullScreen : Window.AutomaticVisibility
    title: i18n.language !== "" ? i18n.text("appTitle") : ""
    color: "#111827"

    LayoutMirroring.enabled: i18n.rtl
    LayoutMirroring.childrenInherit: true

    Dashboard {
        anchors.fill: parent
        onAboutRequested: aboutDialog.open()
    }

    Dialog {
        id: aboutDialog
        modal: true
        title: i18n.language !== "" ? i18n.text("aboutTitle") : ""
        standardButtons: Dialog.Close
        anchors.centerIn: parent
        width: Math.min(parent.width - 32, 560)

        contentItem: ColumnLayout {
            spacing: 14
            Label {
                text: "TaskNest"
                font.pixelSize: 28
                font.bold: true
                color: "#f8fafc"
                Layout.fillWidth: true
            }
            Label {
                text: i18n.language !== "" ? i18n.text("aboutText") : ""
                color: "#cbd5e1"
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
        }

        background: Rectangle {
            color: "#111827"
            border.color: "#334155"
            radius: 14
        }
    }
}

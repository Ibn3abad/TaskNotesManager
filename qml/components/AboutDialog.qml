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

Dialog {
    id: aboutDialog

    modal: true
    focus: true
    title: i18n.language !== "" ? i18n.text("aboutTitle") : "About TaskNest"
    standardButtons: Dialog.NoButton
    width: Math.min(parent ? parent.width - 32 : 560, 560)
    anchors.centerIn: parent

    background: Rectangle {
        color: "#111827"
        border.color: "#334155"
        border.width: 1
        radius: 14
    }

    contentItem: ColumnLayout {
        spacing: 14

        Label {
            text: "TaskNest"
            font.pixelSize: 28
            font.bold: true
            color: "#f8fafc"
            Layout.fillWidth: true
        }

        Text {
            text: i18n.language !== "" ? i18n.text("aboutText") : ""
            textFormat: Text.RichText
            wrapMode: Text.WordWrap
            color: "#cbd5e1"
            linkColor: "#60a5fa"
            Layout.fillWidth: true

            onLinkActivated: function(link) {
                console.log("Opening link:", link)
                Qt.openUrlExternally(link)
            }
        }

        Button {
            Layout.fillWidth: true
            text: i18n.language !== "" ? i18n.text("openGithub") : "Open GitHub"

            onClicked: {
                Qt.openUrlExternally("https://github.com/Ibn3abad/TaskNotesManager")
            }
        }

        Button {
            Layout.alignment: Qt.AlignRight
            text: i18n.language !== "" ? i18n.text("close") : "Close"

            onClicked: {
                aboutDialog.close()
            }
        }
    }
}

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
import QtQuick.Window
import TaskNotesManager
import "components"
import "pages"

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

    AboutDialog {
        id: aboutDialog
    }
}

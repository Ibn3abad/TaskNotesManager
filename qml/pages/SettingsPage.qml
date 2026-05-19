/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.8
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

import QtQuick
import QtQuick.Controls

Item {
    Label {
        anchors.centerIn: parent
        text: i18n.language !== "" ? i18n.text("language") : ""
        color: "#e5e7eb"
    }
}

import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.0

import Backend 1.0

ApplicationWindow {
    id: mainWindow

    x: 0
    y: 0

    width: 2000
    height: 1000

    visible: true

    SystemPalette {
        id: palette
        colorGroup: SystemPalette.Active
    }

    Pages {
        id: pages
        anchors.fill: parent
    }

    // ApplicationSettings {
    //     id: settings
    // }
}
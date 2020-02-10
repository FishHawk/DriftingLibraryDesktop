import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

Row {
    id: root

    property string key: "key"
    property string value: "value"

    spacing: 10

    Label {
        width: 80
        font.pointSize: 12
        text: key + ":"
    }

    Label {
        width: root.width - 90
        font.pointSize: 12
        text: value
        wrapMode: Text.WordWrap
    }
}
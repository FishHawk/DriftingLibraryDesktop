import QtQuick 2.14
import QtQuick.Controls 2.14

Label {
    id: tag

    leftPadding: 5
    rightPadding: 5
    bottomPadding: 3
    font.pointSize: 10

    background: Rectangle {
        color: "transparent"
        border.color: tag.color
        border.width: 1
        radius: 4
    }
}
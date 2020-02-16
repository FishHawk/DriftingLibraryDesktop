import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

ListView {
    spacing: 2
    orientation: ListView.Horizontal
    model: viewModel.images
    cacheBuffer: 1000000000
    preferredHighlightBegin: width / 2 - 200
    preferredHighlightEnd: width / 2 + 200
    highlightRangeMode: ListView.StrictlyEnforceRange
    highlightMoveDuration: 200
    highlightMoveVelocity: -1
    delegate: Image {
        height: parent.height
        sourceSize.width: width; sourceSize.height: height
        fillMode: Image.PreserveAspectFit
        smooth: false
        source: viewModel.url + modelData
        MouseArea {
            anchors.fill: parent
            onClicked: root.index = index
        }
    }

    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: true
        onWheel: {
            let new_index = index - wheel.angleDelta.y / 120
            new_index = new_index < 0 ? 0 : new_index
            new_index = new_index > (viewModel.images.length - 1) ? (viewModel.images.length - 1) : new_index
            index = new_index
        }
    }
}
import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

import Backend 1.0

Item {
    id: root

    property var viewModel: Backend.mangaReaderViewModel
    property int index

    function back() {
        index = 0
        pages.navigate(Pages.Page.Detail)
    }
    function prevPage() {
        if (index > 0)
            index -= 1
        else {
            Backend.openPrevChapter()
            index = viewModel.images.length - 1
        }
    }
    function nextPage() {
        if (index < viewModel.images.length - 1)
            index += 1
        else {
            Backend.openNextChapter()
            index = 0
        }
    }
    function openMenu() {
        previewPanel.open()
    }
    function closeMenu() {
        previewPanel.close()
    }

    focus: pages.isPage(Pages.Page.Reader)
    Keys.onLeftPressed: prevPage()
    Keys.onRightPressed: nextPage()
    Keys.onUpPressed: openMenu()
    Keys.onDownPressed: closeMenu()

    Image {
        id: image
        anchors.fill: parent
        visible: viewModel.images.length != 0
        fillMode: Image.PreserveAspectFit
        source: viewModel.images.length != 0 ? viewModel.url + viewModel.images[index] : ""
        // need test, to reduce Moire pattern
        // mipmap: true
    }
    Label {
        anchors.centerIn: parent
        visible: viewModel.images.length == 0
        text: "No Image"
        font.pointSize: 80
    }
    Label {
        anchors.centerIn: parent
        visible: image.status == Image.Error
        text: "Image Error"
        font.pointSize: 80
    }

    RowLayout {
        anchors.fill: parent
        MouseArea { Layout.preferredWidth: parent.width / 3; Layout.fillHeight: true; onClicked: prevPage() }
        MouseArea { Layout.preferredWidth: parent.width / 3; Layout.fillHeight: true; onClicked: openMenu() }
        MouseArea { Layout.preferredWidth: parent.width / 3; Layout.fillHeight: true; onClicked: nextPage() }
    }

    Popup {
        id: previewPanel
        x: 0
        y: parent.height - height
        width: parent.width
        height: 400
        modal: true

        ColumnLayout {
            anchors.fill: parent
            Label { text: index + " / " + (viewModel.images.length - 1)}
            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 2
                orientation: ListView.Horizontal
                model: viewModel.images
                currentIndex: index
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
                Component.onCompleted: currentIndex = root.index

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
            Slider {
                Layout.fillWidth: true
                value: root.index
                from: 0; to: viewModel.images.length - 1
                stepSize: 1.0
                onValueChanged: root.index = parseInt(value)
            }
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
    Button {
        text: "back"
        onClicked: back()
    }
}
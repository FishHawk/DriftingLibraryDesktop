import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

import Backend 1.0

Item {
    id: root

    property var imageModel: Backend.chapterImageModel
    property int index

    function back() {
        index = 0
        pages.back()
    }
    function prevPage() {
        if (index > 0)
            index -= 1
        else {
            Backend.openPrevChapter()
            index = imageModel.length - 1
        }
    }
    function nextPage() {
        console.log("test")
        if (index < imageModel.length - 1)
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

    focus: true
    Keys.onLeftPressed: prevPage()
    Keys.onRightPressed: nextPage()
    Keys.onUpPressed: openMenu()
    Keys.onDownPressed: closeMenu()

    Image {
        id: image
        anchors.fill: parent
        visible: imageModel.length != 0
        fillMode: Image.PreserveAspectFit
        source: imageModel.length != 0 ? imageModel[index] : ""
        // need test, to reduce Moire pattern
        // mipmap: true
    }
    Label {
        anchors.centerIn: parent
        visible: imageModel.length == 0
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
        y: parent.height - height + 1
        width: parent.width
        height: 400
        modal: true

        ColumnLayout {
            anchors.fill: parent
            Label { text: index + " / " + (imageModel.length - 1)}
            // Loader {
            //     id: loader
            //     Layout.fillWidth: true
            //     Layout.fillHeight: true
            //     asynchronous: true
            //     source: "ImagePreview.qml"
            //     Binding {
            //         target: loader.item
            //         property: "currentIndex"
            //         value: root.index
            //         when: loader.status == Loader.Ready
            //     }
            //     onLoaded: item.currentIndex = root.index
            // }

            Slider {
                Layout.fillWidth: true
                value: root.index
                from: 0; to: imageModel.length - 1
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
            new_index = new_index > (imageModel.length - 1) ? (imageModel.length - 1) : new_index
            index = new_index
        }
    }
    Button {
        text: "back"
        onClicked: back()
    }
}
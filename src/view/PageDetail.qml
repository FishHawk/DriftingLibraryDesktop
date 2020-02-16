import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

import Backend 1.0

RowLayout {
    id: root

    property var viewModel: Backend.mangaDetailViewModel

    spacing: 0

    Item {
        Layout.preferredWidth: 400
        Layout.fillHeight: true

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 10

            Button {
                text: "back"
                onClicked: pages.navigate(Pages.Page.Library)
            }

            Image {
                Layout.fillWidth: true
                // binding loop, need solve
                Layout.preferredHeight: paintedHeight / paintedWidth * width
                fillMode: Image.PreserveAspectFit
                source: viewModel.thumb
            }

            Entry { Layout.fillWidth: true; key: "title"; value: viewModel.title }
            TagEntry { Layout.fillWidth: true }
            Item { Layout.fillHeight: true }
        }

    }

    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: palette.base

        Loader {
            id: y
            anchors.fill: parent
            signal chapterChoosed(int collection, int chapter, int index)
            property var collections: root.viewModel.collections
            property var preview: root.viewModel.preview
            source: {
                if (root.viewModel.depth == 0)
                    return "BrowserChapterDepth0.qml"
                else if (root.viewModel.depth == 1)
                    return "BrowserChapterDepth1.qml"
                else if (root.viewModel.depth == 2)
                    return "BrowserChapterDepth2.qml"
            }
            onChapterChoosed: {
                Backend.openChapter(collection, chapter)
                pages.gotoPageReader(index)
            }
        }
    }
}
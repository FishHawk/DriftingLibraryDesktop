import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

import Backend 1.0

RowLayout {
    id: root

    property var viewModel: Backend.mangaDetailViewModel

    spacing: 0

    Pane {
        Layout.preferredWidth: 400
        Layout.fillHeight: true

        ColumnLayout {
            anchors.fill: parent
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

        ColumnLayout {
            anchors.fill: parent

            TabBar {
                id: bar
                Layout.fillWidth: true
                Repeater {
                    model: root.viewModel.collections
                    TabButton {
                        text: modelData.title
                    }
                }
            }

            StackLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                currentIndex: bar.currentIndex
                Repeater {
                    model: root.viewModel.collections
                    BrowserChapterGrid {
                        model: modelData.chapters
                        onChapterChoosed: {
                            Backend.openChapter(index, chapterIndex)
                            pages.navigate(Pages.Page.Reader)
                        }
                    }
                }
            }
        }
    }
}
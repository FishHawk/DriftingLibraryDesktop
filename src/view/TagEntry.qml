import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

import Backend 1.0

Grid {
    id: root

    columns: 2
    flow: Grid.TopToBottom
    spacing: 10

    Repeater {
        model: viewModel.tags
        Label {
            width: 80
            font.pointSize: 12
            text: modelData.key + ":"
        }
    }

    Repeater {
        model: viewModel.tags
        Flow {
            width: root.width - 90
            spacing: 10

            Repeater {
                id: tags
                model: modelData.value
                property int tagIndex: index
                Tag {
                    color: "grey"
                    text: modelData
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            let key = viewModel.tags[tags.tagIndex].key
                            let value = modelData
                            pageLibrary.query(key + ":" + value)
                            pages.back()
                        }
                    }
                }
            }
        }
    }
}
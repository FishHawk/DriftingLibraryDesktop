import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

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
            id: tags

            property color tagColor: modelData.color

            width: root.width - 90
            spacing: 10

            Repeater {
                model: modelData.value
                Tag {
                    // color: tags.tagColor
                    color: "grey"
                    text: modelData
                }
            }
        }
    }
}
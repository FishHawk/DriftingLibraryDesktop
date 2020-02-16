import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

ColumnLayout {
    TabBar {
        id: bar
        Layout.fillWidth: true
        Repeater {
            model: collections
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
            model: collections
            ButtonGrid {
                model: modelData.chapters
                onSelected: chapterChoosed(index, chapterIndex, 0)
            }
        }
    }
}
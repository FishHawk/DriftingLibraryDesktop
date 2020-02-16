import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

ButtonGrid {
    model: collections[0].chapters
    onSelected: chapterChoosed(0, chapterIndex, 0)
}
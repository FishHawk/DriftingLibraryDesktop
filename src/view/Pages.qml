import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

StackLayout {
    id: pages

    function back() {
        if (currentIndex > 0)
            currentIndex = currentIndex - 1
    }

    function gotoPageDetail() {
        if (pageDetail.source == "")
            pageDetail.source = "PageDetail.qml"
        currentIndex = 1
    }

    function gotoPageReader(index) {
        if (pageReader.source == "")
            pageReader.source = "PageReader.qml"
        pageReader.item.index = index
        currentIndex = 2
    }

    PageLibrary { id: pageLibrary }
    Loader { id: pageDetail }
    Loader { id: pageReader; focus: pages.currentIndex == 2 }
}
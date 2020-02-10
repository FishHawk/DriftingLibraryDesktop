import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

StackLayout {
    currentIndex: 0
    enum Page { Library, Detail, Reader }

    function navigate(page) {
        if (page == Pages.Page.Library)
            currentIndex = 0
        else if (page == Pages.Page.Detail)
            currentIndex = 1
        else if (page == Pages.Page.Reader)
            currentIndex = 2
    }

    function isPage(page) {
        if (page == Pages.Page.Library)
            return currentIndex == 0
        else if (page == Pages.Page.Detail)
            return currentIndex == 1
        else if (page == Pages.Page.Reader)
            return currentIndex == 2
    }

    PageLibrary { id: pageLibrary }
    PageDetail { id: pageDetail }
    PageReader { id: pageReader }
}
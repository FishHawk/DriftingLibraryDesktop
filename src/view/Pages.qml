import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

Loader {
    id: pages
    source: "PageLibrary.qml"
    enum Page { Library, Detail, Reader }

    function navigate(page) {
        if (page == Pages.Page.Library)
            source = "PageLibrary.qml"
        else if (page == Pages.Page.Detail)
            source = "PageDetail.qml"
        else if (page == Pages.Page.Reader)
            source = "PageReader.qml"
    }

    function gotoPageReader(index) {
        setSource("PageReader.qml", {"index": index});
    }

    function isPage(page) {
        if (page == Pages.Page.Library)
            return source == "PageLibrary.qml"
        else if (page == Pages.Page.Detail)
            return source == "PageDetail.qml"
        else if (page == Pages.Page.Reader)
            return source == "PageReader.qml"
    }
}
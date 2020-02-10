import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.3


import Backend 1.0

Rectangle {
    color: palette.base

    ColumnLayout {
        anchors.fill: parent

        BrowserMangaGrid {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: Backend.mangaListViewModel
            onMangaChoosed: {
                Backend.openManga(mangaSummary)
                pages.navigate(Pages.Page.Detail)
            }
        }
        RowLayout {
            Button {
                text: "Set Library"
                onClicked: dialog.open()
            }
            Label {
                text: "Library Url:   " + Backend.libraryUrl
            }
        }
    }


    Dialog {
        id: dialog
        title: "Set Library Url"
        width: 800
        modality: Qt.WindowModality
        standardButtons: Dialog.Ok | Dialog.Cancel

        RowLayout {
            anchors.fill: parent
            Label { text: "Library Url:   " }
            TextField {
                id: inputUrl;
                Layout.fillWidth: true;
                text: Backend.libraryUrl
            }
        }
        onAccepted: {
            Backend.setLibraryUrl(inputUrl.text)
        }
    }
}
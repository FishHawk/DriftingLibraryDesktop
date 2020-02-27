import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.3


import Backend 1.0

Rectangle {
    color: palette.base

    ColumnLayout {
        anchors.fill: parent

        TextField {
            id: queryTextInput
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 800
            placeholderText: "Search Library"
            onAccepted: {
                Backend.libraryModel.query(text)
                focus = false
            }
        }
        BrowserMangaGrid {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: Backend.libraryModel
            onMangaChoosed: {
                Backend.openManga(mangaSummary)
                pages.navigate(Pages.Page.Detail)
            }
        }
        RowLayout {
            Button {
                text: "Manage Library"
                onClicked: dialog.open()
            }
            ComboBox{
                function getAddress() {
                    if (delegateModel && currentIndex >= 0)
                        return delegateModel.items.get(currentIndex).model.address
                    else
                        return "unset"
                }
                id: librarySelector
                textRole: "name"
                model: Backend.entrancesModel
                onActivated: Backend.openLibrary(currentIndex)
            }
            Label {
                text: "Library Url:   " + librarySelector.getAddress()
            }
        }
    }


    Dialog {
        id: dialog
        title: "Set Library Url"
        width: 800
        standardButtons: Dialog.Ok | Dialog.Cancel

        RowLayout {
            anchors.fill: parent
            Label { text: "Library Url:   " }
            TextField {
                id: inputUrl;
                Layout.fillWidth: true;
                // text: Backend.libraryUrl
            }
        }
        onAccepted: {
            queryTextInput.text = "";
            Backend.setLibraryUrl(inputUrl.text)
        }
    }
}
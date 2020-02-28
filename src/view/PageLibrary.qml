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
        title: "Manage Library"
        width: 600
        height: 400
        standardButtons: Dialog.Ok | Dialog.Cancel

        ColumnLayout {
            anchors.fill: parent
            RowLayout {
                Layout.fillWidth: true
                Label {
                    Layout.preferredWidth: 100;
                    horizontalAlignment: Text.AlignHCenter;
                    text: "Name"
                }
                Label {
                    Layout.fillWidth: true;
                    horizontalAlignment: Text.AlignHCenter;
                    text: "Address"
                }
                Button {
                    text: "Add"
                    onClicked: Backend.entrancesModel.create()
                }
            }
            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: Backend.entrancesModel
                delegate: RowLayout {
                    width: parent.width
                    TextField {
                        Layout.preferredWidth: 100;
                        text: name
                        onEditingFinished: model.name = text
                    }
                    TextField {
                        Layout.fillWidth: true;
                        text: address
                        onEditingFinished: model.address = text
                    }
                    Button {
                        text: "Delete"
                        onClicked: Backend.entrancesModel.remove(index)
                    }
                }
            }
        }

        onAccepted: {
            queryTextInput.text = ""
            librarySelector.currentIndex = 0
            librarySelector.activated(librarySelector.currentIndex)
        }
    }
}
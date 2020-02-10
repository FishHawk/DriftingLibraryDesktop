#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include <QUrl>
#include <QtCore/QObject>

#include "view_model/manga_list_view_model.hpp"
#include "view_model/manga_detail_view_model.hpp"
#include "view_model/manga_reader_view_model.hpp"

class Backend : public QObject {
    Q_OBJECT

public:
    Q_PROPERTY(QUrl libraryUrl READ libraryUrl NOTIFY libraryUrlChanged)
    Q_PROPERTY(MangaListViewModel* mangaListViewModel MEMBER m_manga_list_view_model NOTIFY mangaListViewModelChanged)
    Q_PROPERTY(MangaDetailViewModel *mangaDetailViewModel MEMBER m_manga_detail_view_model NOTIFY mangaDetailViewModelChanged)
    Q_PROPERTY(MangaReaderViewModel *mangaReaderViewModel MEMBER m_manga_reader_view_model NOTIFY mangaReaderViewModelChanged)

signals:
    void libraryUrlChanged();
    void mangaListViewModelChanged();
    void mangaDetailViewModelChanged();
    void mangaReaderViewModelChanged();

public:
    Backend();

    QUrl libraryUrl();
    Q_INVOKABLE bool setLibraryUrl(QString user_input);

    Q_INVOKABLE QVariant loadSetting(const QString &key, const QVariant &defaultValue = QVariant()) {
        return m_settings.value(key, defaultValue);
    }
    Q_INVOKABLE void saveSetting(const QString &key, const QVariant &value = QVariant()) {
        m_settings.setValue(key, value);
    }

    Q_INVOKABLE void openManga(QString manga_title);
    Q_INVOKABLE void openChapter(int collection_index, int chapter_index);
    Q_INVOKABLE bool openPrevChapter();
    Q_INVOKABLE bool openNextChapter();

private:
    QSettings m_settings{"settings"};
    MangaListViewModel *m_manga_list_view_model;
    MangaDetailViewModel *m_manga_detail_view_model;
    MangaReaderViewModel *m_manga_reader_view_model;

    int m_collection_index;
    int m_chapter_index;
};

#endif // BACKEND_HPP
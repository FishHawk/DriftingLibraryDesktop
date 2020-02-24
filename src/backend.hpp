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

#include "library.hpp"
#include "model/local/library_model.hpp"
#include "model/remote/library_model.hpp"
#include "model/local/manga_model.hpp"
#include "model/remote/manga_model.hpp"

class Backend : public QObject {
    Q_OBJECT

public:
    Q_PROPERTY(QUrl libraryUrl READ libraryUrl NOTIFY libraryUrlChanged)
    Q_PROPERTY(model::LibraryModel *mangaLibraryViewModel MEMBER m_manga_library_view_model NOTIFY mangaLibraryViewModelChanged)
    Q_PROPERTY(model::MangaModel *mangaDetailViewModel MEMBER m_manga_detail_view_model NOTIFY mangaDetailViewModelChanged)
    Q_PROPERTY(QList<QUrl> chapterImageModel MEMBER m_chapter_image_model NOTIFY chapterImageModelChanged)

signals:
    void libraryUrlChanged();
    void mangaLibraryViewModelChanged();
    void mangaDetailViewModelChanged();
    void chapterImageModelChanged();

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
    LibraryAddress m_library_address;
    model::LibraryModel *m_manga_library_view_model;
    model::MangaModel *m_manga_detail_view_model;
    QList<QUrl> m_chapter_image_model;

    int m_collection_index;
    int m_chapter_index;
};

#endif // BACKEND_HPP
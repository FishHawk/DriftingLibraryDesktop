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

#include "model/entrances_model.hpp"
#include "model/local/library_model.hpp"
#include "model/local/manga_model.hpp"
#include "model/remote/library_model.hpp"
#include "model/remote/manga_model.hpp"

class Backend : public QObject {
    Q_OBJECT

public:
    Q_PROPERTY(model::EntrancesModel *entrancesModel MEMBER m_entrances CONSTANT)
    Q_PROPERTY(model::LibraryModel *libraryModel MEMBER m_library NOTIFY libraryModelChanged)
    Q_PROPERTY(model::MangaModel *mangaModel MEMBER m_manga NOTIFY mangaModelChanged)
    Q_PROPERTY(QList<QUrl> chapterImageModel MEMBER m_chapter_image_model NOTIFY chapterImageModelChanged)

signals:
    void libraryUrlChanged();
    void libraryModelChanged();
    void mangaModelChanged();
    void chapterImageModelChanged();

public:
    Backend();

    Q_INVOKABLE QVariant loadSetting(const QString &key, const QVariant &defaultValue = QVariant()) {
        return m_settings.value(key, defaultValue);
    }
    Q_INVOKABLE void saveSetting(const QString &key, const QVariant &value = QVariant()) {
        m_settings.setValue(key, value);
    }

    Q_INVOKABLE void openLibrary(unsigned int index);
    Q_INVOKABLE void openManga(QString manga_title);
    Q_INVOKABLE void openChapter(int collection_index, int chapter_index);
    Q_INVOKABLE bool openPrevChapter();
    Q_INVOKABLE bool openNextChapter();

private:
    QSettings m_settings{"settings"};

    model::EntrancesModel *m_entrances;
    model::LibraryModel *m_library;
    model::MangaModel *m_manga;
    QList<QUrl> m_chapter_image_model;

    int m_collection_index;
    int m_chapter_index;
};

#endif // BACKEND_HPP
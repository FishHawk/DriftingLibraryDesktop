#ifndef MANGA_DETAIL_VIEW_MODEL
#define MANGA_DETAIL_VIEW_MODEL

#include <QColor>
#include <QDir>
#include <QObject>
#include <QUrl>

#include "view_model/tag_view_model.hpp"

class MangaChapter : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString title MEMBER m_title CONSTANT)

    MangaChapter(QString title)
        : m_title(title) {}

    QString m_title;
};

class MangaCollection : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString title MEMBER m_title CONSTANT)
    Q_PROPERTY(QList<MangaChapter *> chapters MEMBER m_chapters CONSTANT)

    MangaCollection(QString title)
        : m_title(title) {}

    QString m_title;
    QList<MangaChapter *> m_chapters;
};

class MangaDetailViewModel : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString title MEMBER m_title CONSTANT)
    Q_PROPERTY(QUrl thumb MEMBER m_thumb CONSTANT)
    Q_PROPERTY(QList<MangaCollection *> collections MEMBER m_collections CONSTANT)
    Q_PROPERTY(QList<TagViewModel *> tagEntrys MEMBER m_tags CONSTANT)

    MangaDetailViewModel() = default;
    MangaDetailViewModel(QUrl manga_url);

    QString m_title;
    QUrl m_thumb;
    QList<MangaCollection *> m_collections;
    QList<TagViewModel *> m_tags;

private:
    void loadContentFile(QDir manga_dir);
};

#endif
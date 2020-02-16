#ifndef MANGA_DETAIL_VIEW_MODEL
#define MANGA_DETAIL_VIEW_MODEL

#include <QColor>
#include <QDir>
#include <QObject>
#include <QUrl>

#include "view_model/manga_reader_view_model.hpp"
#include "view_model/tag_view_model.hpp"

class CollectionViewModel : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString title MEMBER m_title CONSTANT)
    Q_PROPERTY(QStringList chapters MEMBER m_chapters CONSTANT)

    CollectionViewModel(QString title)
        : m_title(title) {}
    void add_chapter(QString chapter) { m_chapters << chapter; };

    QString m_title;
    QStringList m_chapters;
};

class MangaDetailViewModel : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString title MEMBER m_title CONSTANT)
    Q_PROPERTY(QUrl thumb MEMBER m_thumb CONSTANT)

    Q_PROPERTY(int depth MEMBER m_depth CONSTANT)
    Q_PROPERTY(QList<CollectionViewModel *> collections MEMBER m_collections CONSTANT)
    Q_PROPERTY(MangaReaderViewModel *preview MEMBER m_preview CONSTANT)

    Q_PROPERTY(QList<TagViewModel *> tagEntrys MEMBER m_tags CONSTANT)

    MangaDetailViewModel() = default;
    MangaDetailViewModel(QUrl manga_url);

    QString m_title;
    QUrl m_thumb;

    int m_depth;
    QList<CollectionViewModel *> m_collections;
    MangaReaderViewModel *m_preview;

    QList<TagViewModel *> m_tags;
};

#endif
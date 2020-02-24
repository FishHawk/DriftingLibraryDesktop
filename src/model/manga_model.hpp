#ifndef MODEL_MANGA_MODEL
#define MODEL_MANGA_MODEL

#include <QColor>
#include <QDir>
#include <QObject>
#include <QUrl>

#include "model/manga_content_model.hpp"
#include "model/manga_tag_model.hpp"

namespace model {

class MangaModel : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QUrl thumb MEMBER m_thumb CONSTANT)

    Q_PROPERTY(QList<TagModel *> tags READ tags NOTIFY tagsChanged)

    Q_PROPERTY(int depth READ depth NOTIFY depth NOTIFY collectionsChanged)
    Q_PROPERTY(QList<CollectionModel *> collections READ collections NOTIFY collectionsChanged)

    // Q_PROPERTY(bool hasPreview MEMBER m_has_preview CONSTANT)
    Q_PROPERTY(QList<QUrl> preview MEMBER m_preview CONSTANT)

    QString title() { return m_title; }
    int depth() { return m_depth; }
    QList<CollectionModel *> collections() { return m_collections; }
    QList<TagModel *> tags() { return m_tags; }

    MangaModel() = default;
    MangaModel(QUrl manga_url);

    virtual QList<QUrl> openChapter(unsigned int collection_index, unsigned int chapter_index) = 0;

signals:
    void titleChanged();
    void collectionsChanged();
    void tagsChanged();

public:
    QUrl m_url;
    QString m_title;
    QUrl m_thumb;

    QList<TagModel *> m_tags;

    int m_depth;
    QList<CollectionModel *> m_collections;

    // bool m_has_preview;
    QList<QUrl> m_preview;
};

} // namespace model

#endif
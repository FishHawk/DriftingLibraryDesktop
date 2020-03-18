#ifndef MODEL_MANGA_CONTENT_MODEL_HPP
#define MODEL_MANGA_CONTENT_MODEL_HPP

#include <QUrl>
#include <QDir>

namespace model {

class CollectionModel : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString title MEMBER m_title CONSTANT)
    Q_PROPERTY(QStringList chapters MEMBER m_chapters CONSTANT)

    CollectionModel(QString title)
        : m_title(title) {}
    void add_chapter(QString chapter, int count = -1) {
        m_chapters << chapter;
        m_counts.push_back(count);
    };

    QString m_title;
    QStringList m_chapters;
    std::vector<int> m_counts;
};

class ContentModel : public QObject {
    Q_OBJECT
public:
    static int detact_dir_depth(const QDir &dir);
    static QList<CollectionModel *> get_collections(const QDir &dir, int depth);
    static QUrl get_thumb(const QDir &dir);
};

} // namespace model

#endif
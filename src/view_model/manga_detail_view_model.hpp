#ifndef MANGA_DETAIL_VIEW_MODEL
#define MANGA_DETAIL_VIEW_MODEL

#include <QObject>
#include <QUrl>
#include <QColor>
#include <QDir>

class MangaTagEntry : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString key MEMBER m_key CONSTANT)
    Q_PROPERTY(QStringList value MEMBER m_value CONSTANT)
    Q_PROPERTY(QColor color MEMBER m_color CONSTANT)

    QString m_key;
    QStringList m_value;
    QColor m_color;
};

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
    Q_PROPERTY(QList<MangaTagEntry *> tagEntrys MEMBER m_tag_entrys CONSTANT)

    MangaDetailViewModel() = default;
    MangaDetailViewModel(QUrl manga_url);

    QString m_title;
    QUrl m_thumb;
    QList<MangaCollection *> m_collections;
    QList<MangaTagEntry *> m_tag_entrys;

private:
    void loadContentFile(QDir manga_dir);
    void loadTagFile(QDir manga_dir);
};

#endif
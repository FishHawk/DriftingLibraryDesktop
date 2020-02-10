#ifndef MANGA_READER_VIEW_MODEL
#define MANGA_READER_VIEW_MODEL

#include <QObject>
#include <QUrl>

class MangaReaderViewModel : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QUrl url MEMBER m_url CONSTANT)
    Q_PROPERTY(QStringList images MEMBER m_images CONSTANT)

    MangaReaderViewModel() = default;
    MangaReaderViewModel(QUrl chapter_url);

    QUrl m_url;
    QStringList m_images;
};

#endif
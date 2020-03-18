#include "manga_model.hpp"

#include <QCollator>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using model::local::MangaModel;

MangaModel::MangaModel(QUrl url)
    : ::model::MangaModel(url) {
    QDir manga_dir(url.toLocalFile());

    // load metadata
    auto metadata = MetadataModel::loadMetadataFile(manga_dir);

    m_title = MetadataModel::get_title(metadata);
    if (m_title.isEmpty())
        m_title = manga_dir.dirName();

    m_tags = MetadataModel::get_tags(metadata);

    // load collections
    m_thumb = ContentModel::get_thumb(manga_dir);
    m_depth = ContentModel::detact_dir_depth(manga_dir);
    m_collections = ContentModel::get_collections(manga_dir, m_depth);

    if (m_depth == 0)
        m_preview = this->openChapter(0, 0);
}

QList<QUrl> MangaModel::openChapter(unsigned int collection_index, unsigned int chapter_index) {
    auto collection = m_collections[collection_index];
    auto chapter = collection->m_chapters[chapter_index];
    QUrl chapter_url = m_url.toString() + "/" + collection->m_title + "/" + chapter;
    QDir chapter_dir(chapter_url.toLocalFile());

    auto images = chapter_dir.entryList(QStringList() << "*.jpg"
                                                      << "*.jpeg"
                                                      << "*.png",
                                        QDir::Files);
    QCollator collator;
    collator.setNumericMode(true);
    std::sort(images.begin(), images.end(), collator);

    QList<QUrl> image_urls;
    for (const auto &image : images) {
        image_urls.append(QUrl::fromLocalFile(chapter_dir.filePath(image)));
    }
    return image_urls;
}

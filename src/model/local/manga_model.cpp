#include "manga_model.hpp"

#include <QCollator>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "model/util.hpp"

using model::local::MangaModel;

MangaModel::MangaModel(QUrl url)
    : ::model::MangaModel(url) {
    QDir manga_dir(url.toLocalFile());
    m_title = manga_dir.dirName();
    m_thumb = QUrl::fromLocalFile(util::search_thumb(manga_dir));

    // load collections
    QCollator collator;
    collator.setNumericMode(true);

    auto default_collection = new CollectionModel("");
    auto level1_folders = manga_dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    if (level1_folders.isEmpty()) {
        default_collection->add_chapter("");
        m_depth = 0;
    } else {
        std::sort(level1_folders.begin(), level1_folders.end(), collator);
        for (const auto &level1_folder_name : level1_folders) {
            auto level2_folders = QDir(manga_dir.filePath(level1_folder_name)).entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
            if (level2_folders.isEmpty()) {
                default_collection->add_chapter(level1_folder_name);
                m_depth = 1;
            } else {
                std::sort(level2_folders.begin(), level2_folders.end(), collator);
                auto collection = new CollectionModel(level1_folder_name);
                for (const auto &level2_folder_name : level2_folders) {
                    collection->add_chapter(level2_folder_name);
                }
                m_collections.append(collection);
                m_depth = 2;
            }
        }
    }
    if (m_depth < 2)
        m_collections.append(default_collection);
    if (m_depth == 0) {
        m_preview = this->openChapter(0, 0);
    }

    // load tags
    TagModel::createDefaultFile(manga_dir);
    m_tags = TagModel::loadFromLocalFile(manga_dir);
}

QList<QUrl> MangaModel::openChapter(unsigned int collection_index, unsigned int chapter_index) {
    auto collection = m_collections[collection_index];
    auto chapter = collection->m_chapters[chapter_index];
    QUrl chapter_url = m_url.toString() + "/" + collection->m_title + "/" + chapter;
    QDir chapter_dir(chapter_url.toLocalFile());

    auto images = chapter_dir.entryList(util::image_name_filters(), QDir::Files);
    QCollator collator;
    collator.setNumericMode(true);
    std::sort(images.begin(), images.end(), collator);

    QList<QUrl> image_urls;
    for (const auto &image : images) {
        image_urls.append(QUrl::fromLocalFile(chapter_dir.filePath(image)));
    }
    return image_urls;
}
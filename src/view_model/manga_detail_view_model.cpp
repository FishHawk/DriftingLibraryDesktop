#include "manga_detail_view_model.hpp"

#include <QCollator>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "view_model/util.hpp"

MangaDetailViewModel::MangaDetailViewModel(QUrl manga_url)
    : m_preview{nullptr} {
    QDir manga_dir(manga_url.toLocalFile());
    m_title = manga_dir.dirName();
    m_thumb = QUrl::fromLocalFile(util::search_thumb(manga_dir));

    // load collections
    QCollator collator;
    collator.setNumericMode(true);

    auto default_collection = new CollectionViewModel("");
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
                auto collection = new CollectionViewModel(level1_folder_name);
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
        m_preview = new MangaReaderViewModel(manga_url);
    }

    // load tags
    TagViewModel::createDefaultFile(manga_dir);
    m_tags = TagViewModel::loadFromLocalFile(manga_dir);
}
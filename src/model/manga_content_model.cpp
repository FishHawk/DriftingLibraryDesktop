#include "manga_content_model.hpp"

#include <QCollator>
#include <QJsonDocument>
#include <QJsonObject>

using model::CollectionModel;
using model::ContentModel;

int ContentModel::detact_dir_depth(const QDir &dir) {
    auto level1_folders = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    if (level1_folders.isEmpty())
        return 0;

    for (const auto &level1_folder_name : level1_folders) {
        auto level2_folders = QDir(dir.filePath(level1_folder_name)).entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
        if (!level2_folders.isEmpty())
            return 2;
    }

    return 1;
}

QList<CollectionModel *> ContentModel::get_collections(const QDir &dir, int depth) {
    QCollator collator;
    collator.setNumericMode(true);

    QList<CollectionModel *> m_collections;
    auto default_collection = new CollectionModel("");
    auto level1_folders = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    if (level1_folders.isEmpty()) {
        default_collection->add_chapter("");
    } else {
        std::sort(level1_folders.begin(), level1_folders.end(), collator);
        for (const auto &level1_folder_name : level1_folders) {
            auto level2_folders = QDir(dir.filePath(level1_folder_name)).entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
            if (level2_folders.isEmpty()) {
                default_collection->add_chapter(level1_folder_name);
            } else {
                std::sort(level2_folders.begin(), level2_folders.end(), collator);
                auto collection = new CollectionModel(level1_folder_name);
                for (const auto &level2_folder_name : level2_folders) {
                    collection->add_chapter(level2_folder_name);
                }
                m_collections.append(collection);
            }
        }
    }
    if (depth < 2)
        m_collections.append(default_collection);
    return m_collections;
}

QUrl ContentModel::get_thumb(const QDir &dir) {
    auto thumb_files = dir.entryList(QStringList() << "thumb.jpg"
                                                   << "thumb.png",
                                     QDir::Files, QDir::Name);
    if (!thumb_files.isEmpty())
        return QUrl::fromLocalFile(dir.filePath(thumb_files.front()));

    QCollator collator;
    collator.setNumericMode(true);

    auto search_image = [&collator](auto &&self, const QDir &dir, int depth) {
        auto image_files = dir.entryList(QStringList() << "*.jpg"
                                                       << "*.jpeg"
                                                       << "*.png",
                                         QDir::Files, QDir::Name);
        if (!image_files.isEmpty()) {
            std::sort(image_files.begin(), image_files.end(), collator);
            return dir.filePath(image_files.front());
        } else if (depth > 0) {
            auto sub_dirs = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);
            for (const auto &sub_dir : sub_dirs) {
                auto thumb = self(self, QDir(dir.filePath(sub_dir)), depth - 1);
                if (!thumb.isEmpty())
                    return thumb;
            }
        }
        return QString();
    };
    return QUrl::fromLocalFile(search_image(search_image, dir, 2));
}
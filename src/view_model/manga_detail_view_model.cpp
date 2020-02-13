#include "manga_detail_view_model.hpp"

#include <QCollator>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>


QUrl detectThumb(QDir manga_dir) {
    // need auto detect
    return QUrl::fromLocalFile(manga_dir.filePath("thumb.jpg"));
}

void MangaDetailViewModel::loadContentFile(QDir manga_dir) {
    QFile content_file(manga_dir.filePath("content.json"));

    // auto create content.json at first time
    if (!content_file.exists()) {
        QJsonArray collections_json;
        for (const auto &collection_title : manga_dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot)) {
            QDir collection_dir = manga_dir.filePath(collection_title);
            QJsonObject collection_json;

            collection_json.insert("title", collection_title);

            // sort chapter title with nature order
            auto chapter_titles = collection_dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);
            QCollator collator;
            collator.setNumericMode(true);
            std::sort(chapter_titles.begin(), chapter_titles.end(), collator);

            QJsonArray chapters_json;
            for (const auto &chapter_title : chapter_titles) {
                QJsonObject chapter_json;
                chapter_json.insert("title", chapter_title);
                chapters_json.append(chapter_json);
            }
            collection_json.insert("chapters", chapters_json);

            collections_json.append(collection_json);
        }

        QJsonObject content_json;
        content_json.insert("collections", collections_json);

        content_file.open(QIODevice::WriteOnly | QIODevice::Text);
        content_file.write(QJsonDocument(content_json).toJson(QJsonDocument::Indented));
        content_file.close();
    }

    // parser content.json
    content_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument content_json = QJsonDocument::fromJson(content_file.readAll());
    for (const auto &collection_json : content_json.object().value("collections").toArray()) {
        QString title = collection_json.toObject().value("title").toString();
        auto collection = new MangaCollection(title);

        for (const auto &chapter_json : collection_json.toObject().value("chapters").toArray()) {
            QString title = chapter_json.toObject().value("title").toString();
            int count = chapter_json.toObject().value("count").toInt();
            collection->m_chapters.append(new MangaChapter(title));
        }
        m_collections.append(collection);
    }
    content_file.close();
}

MangaDetailViewModel::MangaDetailViewModel(QUrl manga_url) {
    QDir manga_dir(manga_url.toLocalFile());
    m_title = manga_dir.dirName();
    m_thumb = detectThumb(manga_dir);

    loadContentFile(manga_dir);
    TagViewModel::createDefaultFile(manga_dir);
    m_tags = TagViewModel::loadFromLocalFile(manga_dir);
}
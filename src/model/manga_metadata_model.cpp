#include "manga_metadata_model.hpp"

#include <QJsonDocument>
#include <QJsonObject>

using model::MetadataModel;
using model::TagModel;

QList<TagModel *> TagModel::parseJson(QJsonArray tags_json) {
    QList<TagModel *> tags;
    for (const auto &tag_json : tags_json) {
        auto tag = new TagModel();

        tag->m_key = tag_json.toObject().value("key").toString();
        for (const auto &value_json : tag_json.toObject().value("value").toArray()) {
            tag->m_value.append(value_json.toString());
        }

        tags.push_back(tag);
    }
    return tags;
}

void MetadataModel::createDefaultMetadataFile(QDir manga_dir) {
    QFile metadata_file(manga_dir.filePath("metadata.json"));
    if (!metadata_file.exists()) {
        QJsonObject default_metadata;
        default_metadata.insert("tags", QJsonArray());
        metadata_file.open(QIODevice::WriteOnly | QIODevice::Text);
        metadata_file.write(QJsonDocument(default_metadata).toJson(QJsonDocument::Indented));
        metadata_file.close();
    }
}

QJsonObject MetadataModel::loadMetadataFile(QDir manga_dir) {
    createDefaultMetadataFile(manga_dir);

    QFile metadata_file(manga_dir.filePath("metadata.json"));
    metadata_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonObject metadata = QJsonDocument::fromJson(metadata_file.readAll()).object();
    metadata_file.close();

    return metadata;
}

QList<TagModel *> MetadataModel::get_tags(QJsonObject metadata) {
    return TagModel::parseJson(metadata.value("tags").toArray());
}
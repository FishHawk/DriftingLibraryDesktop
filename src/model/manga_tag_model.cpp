#include "manga_tag_model.hpp"

#include <QJsonDocument>
#include <QJsonObject>

using model::TagModel;

QList<TagModel *> TagModel::parseJson(QJsonArray tags_json) {
    QList<TagModel *> tags;
    for (const auto &tag_json : tags_json) {
        auto tag = new TagModel();

        tag->m_key = tag_json.toObject().value("key").toString();
        for (const auto &value_json : tag_json.toObject().value("value").toArray()) {
            tag->m_value.append(value_json.toString());
        }

        auto colorName = tag_json.toObject().value("color").toString();
        if (QColor::isValidColor(colorName)) {
            tag->m_color = QColor(colorName);
        } else {
            tag->m_color = QColor("grey");
        }

        tags.push_back(tag);
    }
    return tags;
}

QList<TagModel *> TagModel::loadFromLocalFile(QDir manga_dir) {
    QFile tags_file(manga_dir.filePath("tags.json"));
    tags_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonArray tags_json = QJsonDocument::fromJson(tags_file.readAll()).object().value("tags").toArray();
    tags_file.close();
    return parseJson(tags_json);
}


void TagModel::createDefaultFile(QDir manga_dir) {
    QFile tags_file(manga_dir.filePath("tags.json"));
    if (!tags_file.exists()) {
        QJsonObject tags_json;
        tags_json.insert("tags", QJsonArray());

        tags_file.open(QIODevice::WriteOnly | QIODevice::Text);
        tags_file.write(QJsonDocument(tags_json).toJson(QJsonDocument::Indented));
        tags_file.close();
    }
}
#include "manga_model.hpp"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "model/util.hpp"

using model::remote::MangaModel;

MangaModel::MangaModel(QUrl url)
    : ::model::MangaModel(url) {
    m_thumb = QUrl(m_url.toString() + "/content/thumb");
    auto nam = util::get_nam();

    // construct request
    QUrl detail_url(m_url.toString() + "/detail");
    QNetworkRequest request;
    request.setUrl(detail_url);

    // process reply
    auto reply = nam->get(request);
    connect(reply, &QNetworkReply::finished, [this, request, reply]() {
        if (reply->error()) {
            // todo popup message
        } else {
            QString str = (QString)reply->readAll();
            QJsonObject detail_json = QJsonDocument::fromJson(str.toUtf8()).object();
            m_title = detail_json.value("title").toString();
            m_tags = TagModel::parseJson(detail_json.value("tags").toArray());

            m_depth = 2;
            for (const auto &collections_json : detail_json.value("collections").toArray()) {
                auto collection = new model::CollectionModel(collections_json.toObject().value("title").toString());
                for (const auto &chapters_json : collections_json.toObject().value("chapters").toArray()) {
                    auto chapter_title = chapters_json.toObject().value("title").toString();
                    auto chapter_count = chapters_json.toObject().value("count").toInt();
                    collection->add_chapter(chapter_title, chapter_count);
                }
                m_collections.append(collection);
            }

            emit titleChanged();
            emit tagsChanged();
            emit collectionsChanged();
        }
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::sslErrors, [this, request, reply]() {
        // todo popup message
        reply->deleteLater();
    });
}

QList<QUrl> MangaModel::openChapter(unsigned int collection_index, unsigned int chapter_index) {
    auto collection_title = m_collections[collection_index]->m_title;
    auto chapter_title = m_collections[collection_index]->m_chapters[chapter_index];
    auto count = m_collections[collection_index]->m_counts[chapter_index];

    QList<QUrl> image_urls;
    for (int i = 0; i < count; i++) {
        image_urls.append(m_url.toString() + "/content/" +
                          collection_title + "/" +
                          chapter_title + "/" +
                          QString::number(i + 1));
    }
    return image_urls;
}
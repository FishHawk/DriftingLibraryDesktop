#include "model/remote/library_model.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>

#include "model/remote/manga_model.hpp"
#include "model/util.hpp"

using model::remote::LibraryModel;

LibraryModel::LibraryModel(QUrl library_url)
    : ::model::LibraryModel(library_url) {
    request();
}

bool LibraryModel::canFetchMore(const QModelIndex &parent) const {
    return m_can_fetch_more;
}

void LibraryModel::fetchMore(const QModelIndex &parent) {
    request();
}

void LibraryModel::query(QString patterns) {
    // not support temporarily
}

void LibraryModel::request() {
    if (m_is_waiting_reply)
        return;
    auto nam = util::get_nam();

    // construct request
    QNetworkRequest request;
    QUrl url(m_url.toString() + "/mangas");
    QUrlQuery query;
    if (m_mangas.size() > 0)
        query.addQueryItem("last_id", m_mangas.back()->id);
    query.addQueryItem("limit", "5");
    url.setQuery(query);
    request.setUrl(url);

    // process reply
    auto reply = nam->get(request);
    m_is_waiting_reply = true;
    connect(reply, &QNetworkReply::finished, [this, request, reply]() {
        if (reply->error()) {
            // todo popup message
        } else {
            QString str = (QString)reply->readAll();
            QJsonArray mangas_json = QJsonDocument::fromJson(str.toUtf8()).array();

            auto count = mangas_json.count();
            if (count < 5)
                m_can_fetch_more = false;

            beginInsertRows(QModelIndex(), m_mangas.size(), m_mangas.size() + count - 1);
            for (const auto &manga_json : mangas_json) {
                QString id = manga_json.toObject().value("_id").toString();
                QString title = manga_json.toObject().value("title").toString();
                QUrl thumb = m_url.resolved("./manga/" + id + "/content/thumb");
                m_mangas.push_back(new MangaSummary{id, title, thumb});
            }
            endInsertRows();
            m_is_waiting_reply = false;
        }
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::sslErrors, [this, request, reply]() {
        // todo popup message
        reply->deleteLater();
        m_is_waiting_reply = false;
    });
}

model::MangaModel *LibraryModel::openManga(QString id) {
    return new model::remote::MangaModel(QUrl(m_url.toString() + "/manga/" + id));
}
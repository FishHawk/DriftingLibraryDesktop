#include "manga_model.hpp"

#include <QCollator>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "model/util.hpp"

using namespace model;

MangaModel::MangaModel(QUrl manga_url)
    : m_url(manga_url) {
}
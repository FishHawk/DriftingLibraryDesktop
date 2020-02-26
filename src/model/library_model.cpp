#include "library_model.hpp"

using model::LibraryModel;

LibraryModel::LibraryModel(QUrl url)
    : m_url(url) {}

LibraryModel::~LibraryModel() {
    clear();
}

int LibraryModel::rowCount(const QModelIndex &) const {
    return m_mangas.size();
}

QVariant LibraryModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_mangas.size())
        return QVariant();

    if (role == MangaSummaryRole::IdRole)
        return QVariant::fromValue(m_mangas.at(index.row())->id);
    else if (role == MangaSummaryRole::TitleRole)
        return QVariant::fromValue(m_mangas.at(index.row())->title);
    else if (role == MangaSummaryRole::ThumbRole)
        return QVariant::fromValue(m_mangas.at(index.row())->thumb);
    else
        return QVariant();
}

QHash<int, QByteArray> LibraryModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[MangaSummaryRole::IdRole] = "mangaId";
    roles[MangaSummaryRole::TitleRole] = "title";
    roles[MangaSummaryRole::ThumbRole] = "thumb";
    return roles;
}

void LibraryModel::clear() {
    for (auto manga : m_mangas) {
        delete manga;
    }
    m_mangas.clear();
}
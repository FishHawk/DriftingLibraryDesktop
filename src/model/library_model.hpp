#ifndef MODEL_LIBRARY_MODEL_HPP
#define MODEL_LIBRARY_MODEL_HPP

#include <QAbstractListModel>
#include <QObject>
#include <QUrl>

#include "model/manga_model.hpp"
#include "model/tag_filter.hpp"

namespace model {

struct MangaSummary {
    QString id;
    QString title;
    QUrl thumb;
};

class LibraryModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum MangaSummaryRole {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        ThumbRole
    };

    explicit LibraryModel(QUrl library_address);
    virtual ~LibraryModel();

    int rowCount(const QModelIndex &) const override {
        return m_mangas.size();
    }

    QVariant data(const QModelIndex &index, int role) const override {
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

    Q_INVOKABLE virtual void query(QString patterns) = 0;
    virtual MangaModel *openManga(QString id) = 0;

protected:
    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[MangaSummaryRole::IdRole] = "mangaId";
        roles[MangaSummaryRole::TitleRole] = "title";
        roles[MangaSummaryRole::ThumbRole] = "thumb";
        return roles;
    };

    void clear();

    int m_size;
    QUrl m_url;
    TagFilter m_tag_filter;
    std::vector<MangaSummary *> m_mangas;
};

} // namespace model

#endif
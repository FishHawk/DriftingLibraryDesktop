#ifndef MODEL_LIBRARY_MODEL_HPP
#define MODEL_LIBRARY_MODEL_HPP

#include <QAbstractListModel>
#include <QUrl>

#include "model/manga_model.hpp"
#include "model/tag_filter.hpp"

namespace model {

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

    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE virtual void query(QString patterns) = 0;
    virtual MangaModel *openManga(QString id) = 0;

protected:
    struct MangaSummary {
        QString id;
        QString title;
        QUrl thumb;
    };

    void clear();

    QUrl m_url;
    std::vector<MangaSummary *> m_mangas;
    TagFilter m_tag_filter;
};

} // namespace model

#endif
#ifndef MANGA_LIST_VIEW_MODEL
#define MANGA_LIST_VIEW_MODEL

#include <QAbstractListModel>
#include <QObject>
#include <QUrl>

#include "library.hpp"
#include "view_model/tag_filter.hpp"

struct MangaSummary {
    QString title;
    QUrl thumb;
};

class MangaLibraryViewModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum MangaSummaryRole {
        TitleRole = Qt::UserRole + 1,
        ThumbRole
    };

    explicit MangaLibraryViewModel(LibraryAddress library_address);
    ~MangaLibraryViewModel();

    int rowCount(const QModelIndex &) const override {
        return m_mangas.size();
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || index.row() < 0 || index.row() >= m_mangas.size())
            return QVariant();

        if (role == MangaSummaryRole::TitleRole)
            return QVariant::fromValue(m_mangas.at(index.row())->title);
        else if (role == MangaSummaryRole::ThumbRole)
            return QVariant::fromValue(m_mangas.at(index.row())->thumb);
        else
            return QVariant();
    }

    Q_INVOKABLE void query(QString patterns);

protected:
    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[MangaSummaryRole::TitleRole] = "title";
        roles[MangaSummaryRole::ThumbRole] = "thumb";
        return roles;
    };

private:
    void load();
    void clear();

    int m_size;
    LibraryAddress m_library_address;
    TagFilter m_tag_filter;
    std::vector<MangaSummary *> m_mangas;
};

#endif
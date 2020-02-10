#ifndef MANGA_LIST_VIEW_MODEL
#define MANGA_LIST_VIEW_MODEL

#include <QObject>
#include <QUrl>
#include <QAbstractListModel>

struct MangaSummary {
    QString title;
    QUrl thumb;
};

class MangaListViewModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum MangaSummaryRole {
        TitleRole = Qt::UserRole + 1,
        ThumbRole
    };

    explicit MangaListViewModel(QUrl library_url);

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

protected:
    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[MangaSummaryRole::TitleRole] = "title";
        roles[MangaSummaryRole::ThumbRole] = "thumb";
        return roles;
    };

private:
    int m_size;
    QList<MangaSummary *> m_mangas;
};

#endif
#ifndef MODEL_ENTRANCES_MODEL
#define MODEL_ENTRANCES_MODEL

#include <QAbstractListModel>
#include <QUrl>

#include "model/library_model.hpp"

namespace model {

class EntrancesModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum LibraryEntranceRole {
        NameRole = Qt::UserRole + 1,
        AddressRole
    };

    EntrancesModel();
    virtual ~EntrancesModel();

    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    LibraryModel* openLibrary(unsigned int index);

private:
    struct LibraryEntrance {
        QString name;
        QUrl address;
    };

    std::vector<LibraryEntrance> m_entrances;
};

} // namespace model

#endif
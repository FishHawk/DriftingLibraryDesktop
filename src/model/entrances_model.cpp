#include "entrances_model.hpp"

#include "model/local/library_model.hpp"
#include "model/remote/library_model.hpp"

using model::EntrancesModel;

EntrancesModel::EntrancesModel() {
    m_entrances.push_back(LibraryEntrance{"local", QUrl::fromLocalFile("/home/wh/Projects/DriftingLibrary/default")});
    m_entrances.push_back(LibraryEntrance{"remote", QUrl("http://172.18.0.1:8080/api/")});
}

EntrancesModel::~EntrancesModel() {
}

int EntrancesModel::rowCount(const QModelIndex &) const {
    return m_entrances.size();
}

QVariant EntrancesModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_entrances.size())
        return QVariant();

    if (role == LibraryEntranceRole::NameRole)
        return QVariant::fromValue(m_entrances.at(index.row()).name);
    else if (role == LibraryEntranceRole::AddressRole)
        return QVariant::fromValue(m_entrances.at(index.row()).address);
    else
        return QVariant();
}

QHash<int, QByteArray> EntrancesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[LibraryEntranceRole::NameRole] = "name";
    roles[LibraryEntranceRole::AddressRole] = "address";
    return roles;
}

model::LibraryModel *EntrancesModel::openLibrary(unsigned int index) {
    if (index >= m_entrances.size())
        return nullptr;

    auto library_url = m_entrances[index].address;
    if (library_url.isLocalFile()) {
        return new model::local::LibraryModel(library_url);
    } else {
        return new model::remote::LibraryModel(library_url);
    }
}
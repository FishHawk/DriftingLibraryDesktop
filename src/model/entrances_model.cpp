#include "entrances_model.hpp"

#include "model/local/library_model.hpp"
#include "model/remote/library_model.hpp"

#include <QDebug>
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

bool EntrancesModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.row() < 0 || index.row() >= m_entrances.size())
        return false;

    auto &entrance = m_entrances[index.row()];
    if (role == LibraryEntranceRole::NameRole) {
        entrance.name = value.toString();
        emit dataChanged(index, index);
        return true;
    } else if (role == LibraryEntranceRole::AddressRole) {
        entrance.address = QUrl::fromUserInput(value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QHash<int, QByteArray> EntrancesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[LibraryEntranceRole::NameRole] = "name";
    roles[LibraryEntranceRole::AddressRole] = "address";
    return roles;
}

bool EntrancesModel::insertRow(int row, const QModelIndex &parent) {
    if (row < 0 || row > m_entrances.size())
        return false;
    beginInsertRows(parent, row, row);
    m_entrances.insert(m_entrances.begin() + row, LibraryEntrance{"default", QUrl()});
    endInsertRows();
    return true;
}

bool EntrancesModel::removeRow(int row, const QModelIndex &parent) {
    if (row < 0 || row >= m_entrances.size())
        return false;
    beginRemoveRows(parent, row, row);
    m_entrances.erase(m_entrances.begin() + row);
    endRemoveRows();
    return true;
}

model::LibraryModel *EntrancesModel::openLibrary(unsigned int index) {
    if (index >= m_entrances.size())
        return nullptr;

    auto library_url = m_entrances[index].address;
    if (!library_url.isValid())
        return nullptr;
    else if (library_url.isLocalFile()) {
        return new model::local::LibraryModel(library_url);
    } else {
        return new model::remote::LibraryModel(library_url);
    }
}
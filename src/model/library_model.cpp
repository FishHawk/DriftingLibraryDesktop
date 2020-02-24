#include "library_model.hpp"

#include <QCollator>
#include <QDebug>
#include <QDir>
#include <QDirIterator>

#include "model/util.hpp"

using model::LibraryModel;

LibraryModel::LibraryModel(QUrl url)
    : m_url(url){};

LibraryModel::~LibraryModel() {
    clear();
};

void LibraryModel::clear() {
    for (auto manga : m_mangas) {
        delete manga;
    }
    m_mangas.clear();
}
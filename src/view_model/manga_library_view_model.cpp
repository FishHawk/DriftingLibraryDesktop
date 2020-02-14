#include "manga_library_view_model.hpp"

#include <QCollator>
#include <QDebug>
#include <QDir>
#include <QDirIterator>

#include "view_model/util.hpp"

MangaLibraryViewModel::MangaLibraryViewModel(LibraryAddress library_address)
    : m_library_address(library_address) {
    load();
}

MangaLibraryViewModel::~MangaLibraryViewModel() {
    clear();
}

void MangaLibraryViewModel::query(QString patterns) {
    m_tag_filter.set(patterns);

    beginResetModel();
    clear();
    load();
    endResetModel();
}

void MangaLibraryViewModel::load() {
    QDir library_dir(m_library_address.libraryUrl().toLocalFile());
    auto manga_titles = library_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    // filter
    if (!m_tag_filter.empty()) {
        QStringList filtered_manga_title;
        for (const auto &title : manga_titles) {
            QDir manga_dir = m_library_address.mangaUrl(title).toLocalFile();
            auto tags = TagViewModel::loadFromLocalFile(manga_dir);

            if (m_tag_filter.check(title, tags))
                filtered_manga_title << title;
            qDeleteAll(tags);
        }
        manga_titles = filtered_manga_title;
    }

    // sort
    QCollator collator;
    collator.setNumericMode(true);
    std::sort(manga_titles.begin(), manga_titles.end(), collator);

    // load
    for (const auto &title : manga_titles) {
        QDir manga_dir = m_library_address.mangaUrl(title).toLocalFile();
        QUrl thumb = QUrl::fromLocalFile(util::search_thumb(manga_dir));
        m_mangas.push_back(new MangaSummary{title, thumb});
    }
}

void MangaLibraryViewModel::clear() {
    for (auto manga : m_mangas) {
        delete manga;
    }
    m_mangas.clear();
}
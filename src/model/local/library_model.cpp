#include "model/local/library_model.hpp"

#include <QCollator>
#include <QDir>
#include <QDirIterator>

#include "model/local/manga_model.hpp"
#include "model/manga_content_model.hpp"

using model::local::LibraryModel;

LibraryModel::LibraryModel(QUrl url)
    : ::model::LibraryModel(url) {
    load();
}

void LibraryModel::query(QString patterns) {
    m_tag_filter.set(patterns);

    beginResetModel();
    clear();
    load();
    endResetModel();
}

void LibraryModel::load() {
    QDir library_dir(m_url.toLocalFile());
    auto manga_titles = library_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    // filter
    if (!m_tag_filter.empty()) {
        QStringList filtered_manga_title;
        for (const auto &title : manga_titles) {
            QDir manga_dir = QUrl(m_url.toString() + '/' + title + '/').toLocalFile();

            auto metadata = MetadataModel::loadMetadataFile(manga_dir);
            auto tags = MetadataModel::get_tags(metadata);

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
        QDir manga_dir = QUrl(m_url.toString() + '/' + title + '/').toLocalFile();
        QUrl thumb = ContentModel::get_thumb(manga_dir);
        m_mangas.push_back(new MangaSummary{title, title, thumb});
    }
}

model::MangaModel *LibraryModel::openManga(QString id) {
    return new model::local::MangaModel(m_url.toString() + "/" + id);
}
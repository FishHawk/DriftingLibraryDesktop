#include "manga_list_view_model.hpp"

#include <QDir>

MangaListViewModel::MangaListViewModel(QUrl library_url) {
    QDir library_dir(library_url.toLocalFile());
    auto manga_folders = library_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).filter(QRegExp("[1-9]\\d*[.].*"));
    for (const auto &title : manga_folders) {
        // todo: need default action
        auto thumb = QUrl::fromLocalFile(library_dir.filePath(title + QDir::separator() + "thumb.jpg"));

        m_mangas.append(new MangaSummary{title, thumb});
    }
}
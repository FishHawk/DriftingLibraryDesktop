#include "manga_reader_view_model.hpp"

#include <QDir>
#include <QCollator>
#include <QDebug>

MangaReaderViewModel::MangaReaderViewModel(QUrl chapter_url)
    : m_url(chapter_url) {
    QDir chapter_dir(chapter_url.toLocalFile());
    chapter_dir.setNameFilters(QStringList() << "*.jpg"
                                             << "*.png");
    auto images = chapter_dir.entryList(QDir::Files);

    QCollator collator;
    collator.setNumericMode(true);
    std::sort(images.begin(), images.end(), collator);
    m_images = images;
}
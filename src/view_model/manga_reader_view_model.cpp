#include "manga_reader_view_model.hpp"

#include <QCollator>
#include <QDebug>
#include <QDir>

#include "view_model/util.hpp"

MangaReaderViewModel::MangaReaderViewModel(QUrl chapter_url)
    : m_url(chapter_url) {
    QDir chapter_dir(chapter_url.toLocalFile());
    auto images = chapter_dir.entryList(util::image_name_filters(), QDir::Files);

    QCollator collator;
    collator.setNumericMode(true);
    std::sort(images.begin(), images.end(), collator);
    m_images = images;
}
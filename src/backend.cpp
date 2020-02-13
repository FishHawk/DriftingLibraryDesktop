#include "backend.hpp"

#include <QCollator>

#include <utility>

#include "library.hpp"

Backend::Backend()
    : m_manga_detail_view_model(new MangaDetailViewModel),
      m_manga_reader_view_model(new MangaReaderViewModel) {
    setLibraryUrl(m_settings.value("libraryUrl", "").toString());
}

QUrl Backend::libraryUrl() {
    return m_library_address.libraryUrl();
}

bool Backend::setLibraryUrl(QString str) {
    auto library_url = QUrl::fromUserInput(str);
    if (library_url.isValid()) {
        m_library_address.setLibraryUrl(library_url);
        m_settings.setValue("libraryUrl", library_url);
        emit libraryUrlChanged();

        m_manga_library_view_model = new MangaLibraryViewModel(library_url);
        emit mangaLibraryViewModelChanged();
        return true;
    } else {
        return false;
    }
}

void Backend::openManga(QString manga_title) {
    auto manga_url = m_library_address.mangaUrl(manga_title);
    auto new_view_model = new MangaDetailViewModel(manga_url);

    std::swap(new_view_model, m_manga_detail_view_model);
    emit mangaDetailViewModelChanged();
    if (new_view_model != nullptr)
        delete new_view_model;
}

void Backend::openChapter(int collection_index, int chapter_index) {
    m_collection_index = collection_index;
    m_chapter_index = chapter_index;

    auto collection = m_manga_detail_view_model->m_collections[m_collection_index];
    auto chapter = collection->m_chapters[m_chapter_index];
    auto chapter_url = m_library_address.chapterUrl(m_manga_detail_view_model->m_title,
                                                    collection->m_title,
                                                    chapter->m_title);
    auto new_view_model = new MangaReaderViewModel(chapter_url);

    std::swap(new_view_model, m_manga_reader_view_model);
    emit mangaReaderViewModelChanged();
    if (new_view_model != nullptr)
        delete new_view_model;
}

bool Backend::openPrevChapter() {
    auto collections = m_manga_detail_view_model->m_collections;
    auto chapters = collections[m_collection_index]->m_chapters;
    if (m_chapter_index > 0) {
        m_chapter_index -= 1;
    } else if (m_collection_index > 0) {
        m_collection_index -= 1;
        m_chapter_index = 0;
    } else {
        return false;
    }
    openChapter(m_collection_index, m_chapter_index);
    return true;
}

bool Backend::openNextChapter() {
    auto collections = m_manga_detail_view_model->m_collections;
    auto chapters = collections[m_collection_index]->m_chapters;
    if (m_chapter_index < chapters.length() - 1) {
        m_chapter_index += 1;
    } else if (m_collection_index < collections.length() - 1) {
        m_collection_index += 1;
        m_chapter_index = 0;
    } else {
        return false;
    }
    openChapter(m_collection_index, m_chapter_index);
    // qDebug() <<m_chapter_index;
    return true;
}
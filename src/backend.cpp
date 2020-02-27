#include "backend.hpp"

#include <QCollator>

#include <utility>

#include "library.hpp"

Backend::Backend()
    : m_entrances(new model::EntrancesModel()),
      m_library(m_entrances->openLibrary(0)),
      m_manga(nullptr) {}

void Backend::openLibrary(unsigned int index) {
    auto new_library = m_entrances->openLibrary(index);

    std::swap(new_library, m_library);
    emit libraryModelChanged();
    if (new_library != nullptr)
        delete new_library;
}

void Backend::openManga(QString manga_title) {
    auto new_view_model = m_library->openManga(manga_title);

    std::swap(new_view_model, m_manga);
    emit mangaModelChanged();
    if (new_view_model != nullptr)
        delete new_view_model;
}

void Backend::openChapter(int collection_index, int chapter_index) {
    m_collection_index = collection_index;
    m_chapter_index = chapter_index;
    m_chapter_image_model = m_manga->openChapter(collection_index, chapter_index);
    emit chapterImageModelChanged();
}

bool Backend::openPrevChapter() {
    if (m_chapter_index > 0) {
        m_chapter_index -= 1;
    } else if (m_collection_index > 0) {
        m_collection_index -= 1;
        auto collections = m_manga->m_collections;
        auto chapters = collections[m_collection_index]->m_chapters;
        m_chapter_index = chapters.length() - 1;
    } else {
        return false;
    }
    openChapter(m_collection_index, m_chapter_index);
    return true;
}

bool Backend::openNextChapter() {
    auto collections = m_manga->m_collections;
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
    return true;
}
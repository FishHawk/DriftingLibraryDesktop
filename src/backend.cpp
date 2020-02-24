#include "backend.hpp"

#include <QCollator>

#include <utility>

#include "library.hpp"

Backend::Backend()
    : m_manga_detail_view_model(nullptr) {
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

        // for test
        // m_manga_library_view_model = new model::local::LibraryModel(library_url);
        m_manga_library_view_model = new model::remote::LibraryModel(QUrl("http://172.18.0.1:8080/api/"));
        // if (library_url.isLocalFile()) {
        //     m_manga_library_view_model = new model::local::LibraryModel(library_url);
        // } else {
        //     m_manga_library_view_model = new model::remote::LibraryModel(library_url);
        // }
        emit mangaLibraryViewModelChanged();
        return true;
    } else {
        return false;
    }
}

void Backend::openManga(QString manga_title) {
    auto new_view_model = m_manga_library_view_model->openManga(manga_title);

    std::swap(new_view_model, m_manga_detail_view_model);
    emit mangaDetailViewModelChanged();
    if (new_view_model != nullptr)
        delete new_view_model;
}

void Backend::openChapter(int collection_index, int chapter_index) {
    m_collection_index = collection_index;
    m_chapter_index = chapter_index;
    m_chapter_image_model = m_manga_detail_view_model->openChapter(collection_index, chapter_index);
    emit chapterImageModelChanged();
}

bool Backend::openPrevChapter() {
    if (m_chapter_index > 0) {
        m_chapter_index -= 1;
    } else if (m_collection_index > 0) {
        m_collection_index -= 1;
        auto collections = m_manga_detail_view_model->m_collections;
        auto chapters = collections[m_collection_index]->m_chapters;
        m_chapter_index = chapters.length() - 1;
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
    return true;
}
#ifndef LIBRARY_URL
#define LIBRARY_URL

#include <QDir>
#include <QUrl>

class Library {
public:
    static Library *getSingleton() {
        static auto library = new Library();
        return library;
    }

    QUrl libraryUrl() const { return m_library_url; }
    void setLibraryUrl(QUrl library_url) { m_library_url = library_url; }

    QDir libraryDir() const { return m_library_url.toLocalFile(); }

    QUrl mangaUrl(QString title) const {
        return m_library_url.toString() + '/' + title + '/';
    }

    QUrl chapterUrl(QString title, QString collection_title, QString chapter_title) {
        return m_library_url.toString() + '/' +
               title + '/' +
               collection_title + '/' +
               chapter_title + '/';
    }

private:
    Library() = default;
    QUrl m_library_url;
};

#endif
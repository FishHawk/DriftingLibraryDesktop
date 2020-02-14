#include "util.hpp"

QStringList util::image_name_filters() {
    return QStringList() << "*.jpg"
                         << "*.jpeg"
                         << "*.png";
}

QString util::search_thumb(QDir dir, unsigned int depth) {
    auto image_files = dir.entryList(util::image_name_filters(), QDir::Files, QDir::Name);
    if (!image_files.isEmpty())
        return dir.filePath(image_files.front());
    else if (depth > 0) {
        auto sub_dirs = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);
        for (const auto &sub_dir : sub_dirs) {
            auto thumb = util::search_thumb(QDir(dir.filePath(sub_dir)), depth - 1);
            if (thumb != "")
                return thumb;
        }
    }
    return "";
}
#ifndef UTIL_HPP
#define UTIL_HPP

#include <QDir>
#include <QNetworkAccessManager>

namespace util {

QStringList image_name_filters();

QString search_thumb(QDir dir, unsigned int depth = 2);

QNetworkAccessManager *get_nam();

} // namespace util

#endif
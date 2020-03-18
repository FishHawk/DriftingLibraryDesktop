#include "util.hpp"

QNetworkAccessManager *util::get_nam() {
    static QNetworkAccessManager *nam = new QNetworkAccessManager;
    return nam;
}
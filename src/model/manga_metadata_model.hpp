#ifndef METADATA_VIEW_MODEL
#define METADATA_VIEW_MODEL

#include <QColor>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>

namespace model {

class TagModel : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString key MEMBER m_key CONSTANT)
    Q_PROPERTY(QStringList value MEMBER m_value CONSTANT)

    static QList<TagModel *> parseJson(const QJsonArray& tags_json);

    QString m_key;
    QStringList m_value;
    QColor m_color;
};

class MetadataModel : public QObject {
    Q_OBJECT
public:
    static void createDefaultMetadataFile(const QDir &manga_dir);
    static QJsonObject loadMetadataFile(const QDir &manga_dir);
    static QList<TagModel *> get_tags(const QJsonObject &metadata);
    static QString get_title(const QJsonObject &metadata);
};

} // namespace model

#endif
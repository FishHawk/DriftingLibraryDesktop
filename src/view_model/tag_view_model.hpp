#ifndef TAG_VIEW_MODEL
#define TAG_VIEW_MODEL

#include <QColor>
#include <QFile>
#include <QDir>
#include <QJsonArray>
#include <QObject>

class TagViewModel : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString key MEMBER m_key CONSTANT)
    Q_PROPERTY(QStringList value MEMBER m_value CONSTANT)
    Q_PROPERTY(QColor color MEMBER m_color CONSTANT)

    static QList<TagViewModel *> parseJson(QJsonArray tags_json);
    static QList<TagViewModel *> loadFromLocalFile(QDir manga_dir);
    static void createDefaultFile(QDir manga_dir);

    QString m_key;
    QStringList m_value;
    QColor m_color;
};

#endif
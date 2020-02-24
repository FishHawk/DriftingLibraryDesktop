#ifndef MODEL_REMOTE_LIBRARY_MODEL_HPP
#define MODEL_REMOTE_LIBRARY_MODEL_HPP

#include "model/library_model.hpp"

namespace model {
namespace remote {

class LibraryModel : public model::LibraryModel {
    Q_OBJECT
public:
    explicit LibraryModel(QUrl library_url);
    ~LibraryModel() = default;

    Q_INVOKABLE void query(QString patterns) override;
    model::MangaModel *openManga(QString id) override;

private:
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    void request();
    bool m_can_fetch_more = true;
    bool m_is_waiting_reply = false;
};

} // namespace remote
} // namespace model

#endif
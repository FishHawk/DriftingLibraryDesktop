#ifndef MODEL_LOCAL_LIBRARY_MODEL_HPP
#define MODEL_LOCAL_LIBRARY_MODEL_HPP

#include "model/library_model.hpp"

namespace model {
namespace local {

class LibraryModel : public model::LibraryModel {
    Q_OBJECT
public:
    explicit LibraryModel(QUrl url);
    ~LibraryModel() = default;

    Q_INVOKABLE void query(QString patterns) override;
    model::MangaModel* openManga(QString id) override;

protected:
    void load();
};

} // namespace local
} // namespace model

#endif
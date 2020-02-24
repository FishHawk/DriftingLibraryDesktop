#ifndef MODEL_REMOTE_MANGA_MODEL_HPP
#define MODEL_REMOTE_MANGA_MODEL_HPP

#include "model/manga_model.hpp"

namespace model {
namespace remote {

class MangaModel : public model::MangaModel {
    Q_OBJECT
public:
    explicit MangaModel(QUrl url);
    ~MangaModel() = default;
    QList<QUrl> openChapter(unsigned int collection_index, unsigned int chapter_index) override;
};

} // namespace local
} // namespace model

#endif
#ifndef TAG_FILTER
#define TAG_FILTER

#include <QString>
#include <vector>

#include "manga_tag_model.hpp"

class TagFilter {
public:
    TagFilter() = default;

    bool empty() { return m_patterns.empty(); }

    void set(QString input) {
        m_patterns.clear();
        if (input.isEmpty())
            return;

        for (auto &token : input.split(';')) {
            MatchPattern pattern{"", "", false, false, false};
            if (token.front() == '-') {
                pattern.is_exclusion_mode = true;
                token = token.mid(1);
            }
            if (token.back() == '$') {
                pattern.is_exact_mode = true;
                token.chop(1);
            }
            int split_pos = token.indexOf(':');
            if (split_pos >= 0) {
                pattern.key = token.left(split_pos);
                pattern.value = token.mid(split_pos + 1);
            } else {
                pattern.value = token;
            }
            m_patterns.push_back(pattern);
        }
    }

    bool check(const QString &title, const QList<model::TagModel *> &tags) const {
        for (const auto &pattern : m_patterns) {
            bool is_passed = pattern.is_exclusion_mode;

            // check title
            bool is_matched = (!pattern.has_key) &&
                              (pattern.is_exact_mode && title == pattern.value ||
                               !pattern.is_exact_mode && title.contains(pattern.value));
            if (is_matched) {
                is_passed = !pattern.is_exclusion_mode;
            } else {
                // check tag
                for (const auto &tag : tags) {
                    bool is_matched = (pattern.has_key && tag->m_key == pattern.key || !pattern.has_key) &&
                                      (pattern.is_exact_mode && tag->m_value.contains(pattern.value) ||
                                       !pattern.is_exact_mode && !tag->m_value.filter(pattern.value).empty());
                    if (is_matched) {
                        is_passed = !pattern.is_exclusion_mode;
                        break;
                    }
                }
            }

            if (!is_passed)
                return false;
        }
        return true;
    }

private:
    struct MatchPattern {
        QString key;
        QString value;
        bool has_key;
        bool is_exclusion_mode;
        bool is_exact_mode;
    };
    std::vector<MatchPattern> m_patterns;
};
#endif
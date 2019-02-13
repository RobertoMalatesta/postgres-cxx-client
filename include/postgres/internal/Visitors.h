#pragma once

#include <string>
#include <postgres/internal/Classifier.h>

namespace postgres {
namespace internal {

template <typename T>
struct FieldsCollector {
    void accept(const char* const table, const char* const name) {
        if (!res_.empty()) {
            res_ += ",";
        }
        res_ += name;
    };

    std::string res_;
};

template <typename T>
struct PlaceholdersCollector {
    void accept(const char* const table, const char* const name) {
        res_ += res_.empty() ? "$" : ",$";
        res_ += std::to_string(++idx_);
    };

    int         idx_ = 0;
    std::string res_;
};

template <typename T>
struct AssigmentsCollector {
    void accept(const char* const table, const char* const name) {
        if (!res_.empty()) {
            res_ += ",";
        }
        res_ += name;
        res_ += "=$";
        res_ += std::to_string(++idx_);
    };

    int         idx_ = 0;
    std::string res_;
};

template <typename T>
struct ExcludedAssigmentsCollector {
    void accept(const char* const table, const char* const name) {
        if (!res_.empty()) {
            res_ += ",";
        }
        res_ += name;
        res_ += "=EXCLUDED.";
        res_ += name;
    };

    std::string res_;
};

}  // namespace internal
}  // namespace postgres

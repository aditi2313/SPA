#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "IndexableFilter.h"
#include "PKB/data/AssignData.h"
#include "PKB/tables/IndexableTable.h"
#include "common/Exceptions.h"

namespace filter {

    typedef std::unique_ptr<pkb::AssignTable> AssignTablePtr;
    typedef IndexableFilter<pkb::AssignData> AssignFilter;

    class AssignFilterByLine : public IndexableFilter<std::shared_ptr<pkb::AssignData>> {
    public:
        explicit AssignFilterByLine(int line) : line_(line) {}

        inline AssignTablePtr FilterTable(AssignTablePtr table) override {
            AssignTablePtr result = std::make_unique<pkb::AssignTable>();
            auto row = table->get_row(line_);
            result->add_row(row->get_line(), row);
            return result;
        }

    private:
        int line_;
    };

    class AssignFilterByVariable : public IndexableFilter<std::shared_ptr<pkb::AssignData>> {
    public:
        explicit AssignFilterByVariable(std::string variable)
                : variable_(std::move(variable)) {}

        AssignTablePtr FilterTable(AssignTablePtr) override;

    private:
        std::string variable_;
    };

}  // namespace filter

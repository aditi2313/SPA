#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "PKB/data/NextData.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/filter/filters/PredicateFilter.h"

using std::string;
using std::vector;

std::unique_ptr<pkb::NextTable> InitialiseNextTestTable(
        vector<vector<int>> next_im_lines);

TEST_CASE("Test Next by next lines Filter") {
    vector<vector<int>> next_im_lines = {{2, 3}, {5, 6}, {9}};
    vector<vector<int>> result_lines = {{2, 3}};

    auto table = InitialiseNextTestTable(next_im_lines);
    std::unordered_set<int> filtered = {2};
    filter::NextPredicateFilter next_lines_filter(
            [filtered](pkb::NextData data) {
                for (auto next : data.get_next_im_list()) {
                    if (filtered.find(next) != filtered.end()) {
                        return true;
                    }
                }
                return false;
            });
    auto& new_table = next_lines_filter.FilterTable(*table);
    auto expected = InitialiseNextTestTable(result_lines);
    //REQUIRE(*expected == *new_table);
}

TEST_CASE("Test Next by line filter") {
    vector<vector<int>> next_im_lines = {{2, 3}, {5, 6}, {9}};
    vector<vector<int>> result_lines = {{2, 3}};

    auto table = InitialiseNextTestTable(next_im_lines);
    filter::NextIndexFilter caller_filter(0);

    auto &new_table = caller_filter.FilterTable(*table);
    auto expected = InitialiseNextTestTable(result_lines);

    //REQUIRE(*expected == *new_table);
}

std::unique_ptr<pkb::NextTable> InitialiseNextTestTable(
        vector<vector<int>> next_im_lines) {
    std::unique_ptr<pkb::NextTable> result =
            std::make_unique<pkb::NextTable>();
    for (int i = 0; i < next_im_lines.size(); ++i) {
        pkb::NextData data(i);
        for (int j = 0; j < next_im_lines.at(i).size(); ++j) {
            data.add_to_next_im_list(next_im_lines.at(i).at(j));
        }
        result->add_row(i, data);
    }
    return std::move(result);
}

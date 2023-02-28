#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "PKB/data/CallsData.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/filter/filters/PredicateFilter.h"

using std::string;
using std::vector;

std::unique_ptr<pkb::CallsTable> InitialiseCallsTestTable(
        vector<vector<string>> callees);

TEST_CASE("Test Calls by callee Filter") {
    vector<vector<string>> callees = {
            {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

    vector<vector<string>> result_variables =
            {{"a", "b", "c"}, {"a", "b"}};
    auto table = InitialiseCallsTestTable(callees);
    std::unordered_set<string> filtered = {"a"};
    filter::CallsPredicateFilter callee_filter(
            [filtered](pkb::CallsData data) {
                for (auto var : data.get_callee_list()) {
                    if (filtered.find(var) != filtered.end()) {
                        return true;
                    }
                }
                return false;
            });
    auto new_table = callee_filter.FilterTable(std::move(table));
    auto expected = InitialiseCallsTestTable(result_variables);
    REQUIRE(*expected == *new_table);
}

TEST_CASE("Test Calls by Caller filter") {
    vector<vector<string>> callees = {
            {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

    vector<vector<string>> result_variables = {{"a", "b", "c"}};
    auto table = InitialiseCallsTestTable(callees);
    filter::CallsIndexFilter caller_filter("x");

    auto new_table = caller_filter.FilterTable(std::move(table));
    auto expected = InitialiseCallsTestTable(result_variables);

    REQUIRE(*expected == *new_table);
}

std::unique_ptr<pkb::CallsTable> InitialiseCallsTestTable(
        vector<vector<string>> callees) {
    vector<string> callers = {"x", "y", "z"};
    std::unique_ptr<pkb::CallsTable> result =
            std::make_unique<pkb::CallsTable>();
    for (int i = 0; i < callees.size(); ++i) {
        pkb::CallsData data(callers.at(i), callees.at(i).at(0));
        for (int j = 1; j < callees.at(i).size(); ++j) {
            data.add_to_list(callees.at(i).at(j));
        }
        result->add_row(callers.at(i), data);
    }
    return std::move(result);
}

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
        vector<vector<string>> direct_callees);

TEST_CASE("Test Calls by callee Filter") {
    vector<vector<string>> direct_callees = {
            {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

    vector<vector<string>> result_callees =
            {{"a", "b", "c"}, {"a", "b"}};
    auto table = InitialiseCallsTestTable(direct_callees);
    std::unordered_set<string> filtered = {"a"};
    filter::CallsPredicateFilter callee_filter(
            [filtered](pkb::CallsData data) {
                for (auto var : data.get_direct_calls()) {
                    if (filtered.find(var) != filtered.end()) {
                        return true;
                    }
                }
                return false;
            });
    auto new_table = callee_filter.FilterTable(std::move(table));
    auto expected = InitialiseCallsTestTable(result_callees);
    REQUIRE(*expected == *new_table);
}

TEST_CASE("Test Calls by Caller filter") {
    vector<vector<string>> direct_callees = {
            {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

    vector<vector<string>> result_callees = {{"a", "b", "c"}};
    auto table = InitialiseCallsTestTable(direct_callees);
    filter::CallsIndexFilter caller_filter("x");

    auto new_table = caller_filter.FilterTable(std::move(table));
    auto expected = InitialiseCallsTestTable(result_callees);

    REQUIRE(*expected == *new_table);
}

std::unique_ptr<pkb::CallsTable> InitialiseCallsTestTable(
        vector<vector<string>> direct_callees) {
    vector<string> callers = {"x", "y", "z"};
    std::unique_ptr<pkb::CallsTable> result =
            std::make_unique<pkb::CallsTable>();
    for (int i = 0; i < direct_callees.size(); ++i) {
        pkb::CallsData data(callers.at(i));
        for (int j = 0; j < direct_callees.at(i).size(); ++j) {
            data.add_to_direct_calls(direct_callees.at(i).at(j));
        }
        result->add_row(callers.at(i), data);
    }
    return std::move(result);
}

#include <catch.hpp>
#include <utility>

#include <QPS/models/PQL.h>
#include <QPS/preprocessor/SelectClParser.h>
#include <QPS/preprocessor/Validator.h>
#include <common/Exceptions.h>

using namespace qps;  // NOLINT

std::unique_ptr<Query> BuildQuery(
    std::vector<std::pair<SynonymName, EntityName>> synonyms,
    std::vector<std::string> selected_synonyms);  // Forward declaration

TEST_CASE("Test IsWildcard") {
  Validator validator;
  SECTION("No wildcard used for Modifies") {
    // No wildcard
    std::string query = "stmt s; Select s such that Modifies(s, 2)";
    std::unique_ptr<Query> expected_query =
        BuildQuery({{"s", PQL::kStmtEntityName}}, {"s"});
    expected_query->add_clause(std::make_unique<qps::ModifiesClause>(
        expected_query->CreateArgument("s"),
        expected_query->CreateArgument("2")));
    REQUIRE(Validator::IsWildcard(expected_query));
  }
  SECTION("No WildCard used for Uses") {
    std::string query = "stmt s; Select s such that Uses(s, 2)";
    std::unique_ptr<Query> expected_query =
        BuildQuery({{"s", PQL::kStmtEntityName}}, {"s"});
    expected_query->add_clause(
        std::make_unique<qps::UsesClause>(expected_query->CreateArgument("s"),
                                          expected_query->CreateArgument("2")));

    REQUIRE(Validator::IsWildcard(expected_query));
  }

  SECTION("Wildcard used for Modifies") {
    std::string query = "stmt s; Select s such that Modifies(_, s)";
    std::unique_ptr<Query> expected_query =
        BuildQuery({{"s", PQL::kStmtEntityName}}, {"s"});
    expected_query->add_clause(std::make_unique<qps::ModifiesClause>(
        expected_query->CreateArgument("_"),
        expected_query->CreateArgument("s")));
    REQUIRE_THROWS_AS(!Validator::IsWildcard(expected_query),
                      PqlSemanticErrorException);
  }

  SECTION("Wildcard used for Uses") {
    std::string query = "stmt s; Select s such that Uses(_, s)";
    std::unique_ptr<Query> expected_query =
        BuildQuery({{"s", PQL::kStmtEntityName}}, {"s"});
    expected_query->add_clause(
        std::make_unique<qps::UsesClause>(expected_query->CreateArgument("_"),
                                          expected_query->CreateArgument("s")));
    REQUIRE_THROWS_AS(!Validator::IsWildcard(expected_query),
                      PqlSemanticErrorException);
  }

  SECTION("Wildcard used for Follows") {
    std::string query = "stmt s; Select s such that Follows(_, s)";
    std::unique_ptr<Query> expected_query =
        BuildQuery({{"s", PQL::kStmtEntityName}}, {"s"});
    expected_query->add_clause(std::make_unique<qps::FollowsClause>(
        expected_query->CreateArgument("_"),
        expected_query->CreateArgument("s")));
    REQUIRE(Validator::IsWildcard(expected_query));
  }
}
TEST_CASE("Test SynonymCheck") {
  Validator validator;
  SECTION("Synonym used is declared once") {
    // All used synonyms are declared
    std::unique_ptr<Query> query =
        BuildQuery({{"v", PQL::kVariableEntityName}}, {"v"});
    query->add_clause(std::make_unique<ModifiesClause>(
        query->CreateArgument("6"), query->CreateArgument("v")));

    REQUIRE(Validator::SynonymCheck(query));
  }

  SECTION("Undeclared synoym used") {
    // One undeclared synonym used
    std::string query_string2 = "variable v; Select v such that Modifies(6, a)";

    std::unique_ptr<Query> expected_query2 =
        BuildQuery({{"v", PQL::kVariableEntityName}}, {"v"});
    expected_query2->add_clause(
        std::make_unique<ModifiesClause>(expected_query2->CreateArgument("6"),
                                         expected_query2->CreateArgument("a")));

    REQUIRE_THROWS_AS(!Validator::SynonymCheck(expected_query2),
                      PqlSemanticErrorException);
  }
}
//
TEST_CASE("DesignEntitySynonym checker") {
  SECTION("Synonym declared more than once") {
    std::string query =
        "variable v; stmt v;"
        "Select v such that Modifies(v, 2)";
    std::unique_ptr<Query> expected_query = BuildQuery(
        {{"v", PQL::kVariableEntityName}, {"v", PQL::kStmtEntityName}},
        {"v", "v"});
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(expected_query->CreateArgument("v"),
                                         expected_query->CreateArgument("2")));

    REQUIRE_THROWS_AS(!Validator::isDeclaredOnce(expected_query),
                      PqlSemanticErrorException);
  }

  SECTION("Valid synonym for Modifies Clause") {
    std::string wrong_synonym = "stmt s; Select v such that Modifies(s, 2)";
    std::unique_ptr<Query> expected_query_valid_synonym =
        BuildQuery({{"s", PQL::kStmtEntityName}}, {"s"});
    expected_query_valid_synonym->add_clause(std::make_unique<ModifiesClause>(
        expected_query_valid_synonym->CreateArgument("s"),
        expected_query_valid_synonym->CreateArgument("2")));
    REQUIRE(Validator::DesignEntitySynonyms(expected_query_valid_synonym));
  }
  SECTION("Valid synonym for Follows Clause") {
    std::string wrong_synonym = "stmt s; Select s such that Follows(s, 2)";
    std::unique_ptr<Query> expected_query_right_synonym =
        BuildQuery({{"s", PQL::kStmtEntityName}}, {"s"});
    expected_query_right_synonym->add_clause(std::make_unique<FollowsClause>(
        expected_query_right_synonym->CreateArgument("s"),
        expected_query_right_synonym->CreateArgument("2")));
    REQUIRE(Validator::DesignEntitySynonyms(expected_query_right_synonym));
  }

  SECTION("Synonym of the wrong type for Modifies") {
    std::string wrong_synonym = "variable v; Select v such that Modifies(v, 2)";
    std::unique_ptr<Query> expected_query_wrong_synonym =
        BuildQuery({{"v", PQL::kVariableEntityName}}, {"v"});
    expected_query_wrong_synonym->add_clause(std::make_unique<ModifiesClause>(
        expected_query_wrong_synonym->CreateArgument("v"),
        expected_query_wrong_synonym->CreateArgument("2")));
    REQUIRE_THROWS_AS(
        !Validator::DesignEntitySynonyms(expected_query_wrong_synonym),
        PqlSemanticErrorException);
  }
  SECTION("Synonym of the wrong type for Follows") {
    std::string wrong_synonym = "variable v; Select v such that Follows(v, 2)";
    std::unique_ptr<Query> expected_query_wrong_synonym =
        BuildQuery({{"v", PQL::kVariableEntityName}}, {"v"});
    expected_query_wrong_synonym->add_clause(std::make_unique<FollowsClause>(
        expected_query_wrong_synonym->CreateArgument("v"),
        expected_query_wrong_synonym->CreateArgument("2")));
    REQUIRE_THROWS_AS(
        !Validator::DesignEntitySynonyms(expected_query_wrong_synonym),
        PqlSemanticErrorException);
  }
}

TEST_CASE("Overall Validation") {
  SelectClParser parser;
  SECTION("Semantically invalid") {
    std::string query = "variable v; Select v such that Modifies(v, 2)";
    std::unique_ptr<Query> expected_query =
        BuildQuery({{"v", PQL::kVariableEntityName}}, {"v"});
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(expected_query->CreateArgument("v"),
                                         expected_query->CreateArgument("2")));

    REQUIRE_THROWS_AS(Validator::validate(expected_query),
                      PqlSemanticErrorException);
  }
  SECTION("Semantically valid") {
    std::string query = "variable v; Select v such that Modifies(2, v)";
    QueryPtr parsed_query = parser.ParseQuery(query);
    QueryPtr expected_query =
        BuildQuery({{"v", PQL::kVariableEntityName}}, {"v"});
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(expected_query->CreateArgument("2"),
                                         expected_query->CreateArgument("v")));

    REQUIRE(*Validator::validate(expected_query) == *parsed_query);
  }
}

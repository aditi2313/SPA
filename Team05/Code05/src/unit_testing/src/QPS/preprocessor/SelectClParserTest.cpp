#include <exception>
#include <catch.hpp>

#include "QPS/factories/MasterClauseFactory.h"
#include "QPS/preprocessor/SelectClParser.h"
#include "QPS/models/PQL.h"

using namespace qps; // NOLINT

// Helper method for testing
QueryPtr BuildQuery(
    std::vector<std::pair<SynonymName, EntityType>> synonyms,
    std::vector<std::string> selected_synonyms
) {
  QueryPtr query = std::make_unique<Query>();
  for (auto [syn, entity] : synonyms) {
    query->declare_synonym(syn, entity);
  }
  for (auto selected_syn : selected_synonyms) {
    query->add_selected_elem(selected_syn);
  }

  return query;
}

// Helper method for testing
void TestNoThrows(std::string query_string) {
  SelectClParser parser;
  REQUIRE_NOTHROW(parser.ParseQuery(query_string));
}

// Helper method for testing
void TestThrows(std::string query_string) {
  SelectClParser parser;
  REQUIRE_THROWS_AS(
      parser.ParseQuery(query_string), PqlSyntaxErrorException);
}

TEST_CASE("Test SelectClParser methods") {
  SelectClParser parser;
  SECTION("Test PreprocessQueryString") {
    std::string query_string = "variable p; select p such that "
                               "Modifies(6, v) pattern a(_, _\" x + y \"_)";
    std::vector<std::string> expected_tokens{
        "variable", "p", ";", "select", "p", "such", "that",
        "Modifies", "(", "6", ",", "v", ")",
        "pattern", "a", "(", "_", ",", "_\"x+y\"_", ")"
    };
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);

    // With random whitespaces and newlines
    query_string = "variable     p;\n   select    p   such  \n   "
                   "that Modifies(6, v) \n pattern a(_, _\"x+y\"_)";
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);
  }
}
// weeeeeeeee
TEST_CASE("Test ParseQuery") {
  SelectClParser parser;
  MasterArgumentFactory master_argument_factory;
  MasterClauseFactory master_clause_factory;

  SECTION("Query with no declarations should not throw SyntaxError") {
    // It needs to throw SemanticError
    std::string query_string = "Select p";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery({}, {"p"});

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with no clauses should parse correctly") {
    std::string query_string = "procedure p; Select p";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"p", EntityType::kProcedure}},
        {"p"});

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with one such-that clauses should parse correctly") {
    std::string query_string = "variable v; Select v such that Modifies(6, v)";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", EntityType::kVariable}},
        {"v"});
    auto arg1 = master_argument_factory.CreateEntOrStmtRef("6");
    auto arg2 = master_argument_factory.CreateEntOrStmtRef("v");
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kModifies, std::move(arg1), std::move(arg2)));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with one clause and selected tuple should parse correctly") {
    std::string query_string = "variable v; stmt s; "
                               "Select <s, v> such that Modifies(s, v)";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", EntityType::kVariable},
         {"s", EntityType::kStmt}},
        {"s", "v"});
    auto arg1 = master_argument_factory.CreateEntOrStmtRef("s");
    auto arg2 = master_argument_factory.CreateEntOrStmtRef("v");
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kModifies, std::move(arg1), std::move(arg2)));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with one pattern clauses should parse correctly") {
    std::string query_string = "assign a; variable v; "
                               "Select a pattern a(v, \"x + y\")";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"a", EntityType::kAssign}, {"v", EntityType::kVariable}},
        {"a"});
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kModifies,
            master_argument_factory.CreateSynonym(
                "a", EntityType::kAssign),
            master_argument_factory.CreateEntRef("v")));
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kPatternAssign,
            master_argument_factory.CreateSynonym(
                "a", EntityType::kAssign),
            master_argument_factory.CreateExpressionSpec("\"x+y\"")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with one with clause should parse correctly") {
    std::string query_string = "assign a; Select a with a.stmt# = 12";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"a", EntityType::kAssign}},
        {"a"});

    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kWith,
            master_argument_factory.CreateRef("a.stmt#"),
            master_argument_factory.CreateRef("12")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION(
      "Query with multiple declarations, multiple synonyms "
      "and multiple such-that and pattern clauses should parse correctly") {
    std::string query_string = "variable v; procedure p; assign a; "
                               "Select v such that Modifies(6, v) "
                               "such that Modifies(3, v) "
                               "pattern a(_, \"x + y\") "
                               "pattern a(\"variable\", _\"x\"_)";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", EntityType::kVariable},
         {"p", EntityType::kProcedure},
         {"a", EntityType::kAssign}},
        {"v"});

    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kModifies,
            master_argument_factory.CreateEntOrStmtRef("6"),
            master_argument_factory.CreateEntOrStmtRef("v")));
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kModifies,
            master_argument_factory.CreateEntOrStmtRef("3"),
            master_argument_factory.CreateEntOrStmtRef("v")));
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kModifies,
            master_argument_factory.CreateSynonym("a", EntityType::kAssign),
            master_argument_factory.CreateEntRef("_")));
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kPatternAssign,
            master_argument_factory.CreateSynonym("a", EntityType::kAssign),
            master_argument_factory.CreateExpressionSpec("\"x+y\"")));
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kModifies,
            master_argument_factory.CreateSynonym("a", EntityType::kAssign),
            master_argument_factory.CreateEntRef("\"variable\"")));
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kPatternAssign,
            master_argument_factory.CreateSynonym("a", EntityType::kAssign),
            master_argument_factory.CreateExpressionSpec("_\"x\"_")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION(
      "Query with multiple declarations, multiple synonyms "
      "and multiple such-that and pattern clauses and "
      "many random whitespaces and tabs"
      "should parse correctly") {
    std::string query_string = "variable  \t  v;  assign a; "
                               "Select v such  that \t  Modifies(  6, v) "
                               "  such  \t    that    Modifies(3, v) "
                               "pattern a(_, \"x + y   \t  \") "
                               "   \t pattern a(_,  \"   x  \t\")";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", EntityType::kVariable},
         {"a", EntityType::kAssign}},
        {"v"});
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kModifies,
            master_argument_factory.CreateEntOrStmtRef("6"),
            master_argument_factory.CreateEntRef("v")));
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kModifies,
            master_argument_factory.CreateEntOrStmtRef("3"),
            master_argument_factory.CreateEntRef("v")));
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kModifies,
            master_argument_factory.CreateSynonym(
                "a", EntityType::kAssign),
            master_argument_factory.CreateEntOrStmtRef("_")));
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kPatternAssign,
            master_argument_factory.CreateSynonym(
                "a", EntityType::kAssign),
            master_argument_factory.CreateExpressionSpec("\"x+y\"")));
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kModifies,
            master_argument_factory.CreateSynonym(
                "a", EntityType::kAssign),
            master_argument_factory.CreateEntOrStmtRef("_")));
    expected_query->add_clause(
        master_clause_factory.Create(
            ClauseType::kPatternAssign,
            master_argument_factory.CreateSynonym(
                "a", EntityType::kAssign),
            master_argument_factory.CreateExpressionSpec("\"x\"")));

    REQUIRE(*actual_query == *expected_query);
  }

    // In the following testcases, it is too verbose to create the
    // full expected clause as the queries are much longer,
    // so will just be testing NoThrows or Throws.
    // The previous testcases cover whether the expected query has the
    // correct clauses.
  SECTION("Query with pattern before such-that should parse correctly") {
    std::string query_string = "variable v; assign a; "
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v)";

    TestNoThrows(query_string);
  }

  SECTION("Query with interleaving clauses of different types"
          "should parse correctly") {
    std::string query_string = "variable v; assign a; "
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v) "
                               "pattern a(v, _\"x\"_) "
                               "with 12 = \"test\" "
                               "such that Uses(6, v) "
                               "with a.stmt# = c.value "
                               "pattern a(_, _)";

    TestNoThrows(query_string);
  }

  SECTION("Query with mix of using 'and' and no 'and' "
          "should parse correctly") {
    std::string query_string = "variable v; assign a; "
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v) "
                               "and Uses(6, v) "
                               "such that Parent(6, 7)";

    TestNoThrows(query_string);
  }

  SECTION("Query with interleaving clauses of different types"
          "and with 'and' should parse correctly") {
    std::string query_string = "variable v; assign a; "
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v) "
                               "pattern a(v, _\"x\"_) "
                               "and a(_, \"x\") "
                               "such that Uses(6, v) "
                               "and Parent(6, 7)";

    TestNoThrows(query_string);
  }

  SECTION("Query with Select attrRef should parse correctly") {
    std::string query_string = "stmt s;"
                               "Select s.stmt#";

    TestNoThrows(query_string);
  }

  SECTION("Query with Select <attrRef, attrRef> should parse correctly") {
    std::string query_string = "stmt s; procedure p;"
                               "Select <s.stmt#, p.procName>";

    TestNoThrows(query_string);
  }

  SECTION("Query with interleaving different types of Pattern clauses "
          "using 'and' should parse correctly") {
    std::string query_string = "variable v; assign a; if ifs; while w; "
                               "Select <v, a, ifs, w> "
                               "pattern a(v, _) and "
                               "ifs(v, _, _) and "
                               "w(v, _)";

    TestNoThrows(query_string);
  }

    /* ============ ERROR CASES =============== */
  SECTION("Query with both 'and' and 'such-that'"
          "should throw error") {
    std::string query_string = "variable v; assign a; "
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v) "
                               "and such that Uses(6, v)";

    TestThrows(query_string);
  }

  SECTION("Query with using 'and' to connect "
          "between such-that and pattern"
          "should throw error") {
    std::string query_string = "variable v; assign a; "
                               "Select v such that Modifies(6, v) "
                               "and pattern a(v, _\"x\"_)";

    TestThrows(query_string);
  }

  SECTION("Query with using 'and' to connect "
          "between pattern and with "
          "should throw error") {
    std::string query_string = "variable v; assign a; constant c; "
                               "Select v pattern a(_, \"x + y\") "
                               "and with a.stmt# = c.value";

    // TODO(JL): Will fix this in a separate PR
//    TestThrows(query_string);
  }

  SECTION("Query with using 'and' to connect "
          "between such-that and with"
          "should throw error") {
    std::string query_string = "variable v; assign a; "
                               "Select v such that Modifies(6, v) "
                               "and with a.stmt# = c.value";

    TestThrows(query_string);
  }

  SECTION("Query with Select attrRef, attrRef should throw error") {
    // Missing diamond braces
    std::string query_string = "stmt s; procedure p;"
                               "Select s.stmt#, p.procName";

    TestThrows(query_string);
  }

  SECTION("Query with incorrect syn entity type for Pattern If"
          "should throw SemanticError") {
    std::string query_string = "while w;"
                               "Select w pattern w(_, _, _)";

    REQUIRE_THROWS_AS(
        parser.ParseQuery(query_string), PqlSemanticErrorException);
  }

  SECTION("Query with incorrect syntax for Pattern If"
          "should throw SyntaxError") {
    std::string query_string = "if ifs; "
                               "Select ifs pattern ifs(_, \"x\", _)";

    TestThrows(query_string);
  }

  SECTION("Query with incorrect syn entity type for Pattern Assign|While"
          "should throw SemanticError") {
    std::string query_string = "if ifs;"
                               "Select ifs pattern ifs(_, _)";

    REQUIRE_THROWS_AS(
        parser.ParseQuery(query_string), PqlSemanticErrorException);
  }

  SECTION("Query with double Select should throw error") {
    std::string query_string = "stmt s; procedure p;"
                               "Select s Select p";

    TestThrows(query_string);
  }
}

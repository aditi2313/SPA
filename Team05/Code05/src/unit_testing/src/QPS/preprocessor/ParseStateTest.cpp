#include <catch.hpp>

#include "QPS/preprocessor/ParseState.h"
#include "QPS/models/PQL.h"
#include "QPS/factories/MasterClauseFactory.h"
#include "common/exceptions/QPSExceptions.h"

using namespace qps; // NOLINT

// Helper method for testing
void TestErrorCase(ParseState &state, std::vector<std::string> tokens) {
  std::unique_ptr<Query> query = std::make_unique<Query>();
  auto itr = tokens.begin();
  REQUIRE_THROWS_AS(
      state.Parse(tokens, itr, query), PqlSyntaxErrorException);
}

TEST_CASE("Test DeclarationParseState") {
  DeclarationParseState state;

  SECTION("Single declaration should parse correctly") {
    std::vector<std::string> tokens{"variable", "v", ";"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    REQUIRE(query->is_synonym_name_declared("v"));
    REQUIRE(query->get_declared_synonym_entity_name("v")
                == PQL::kVariableEntityName);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Multiple declarations should parse correctly") {
    std::vector<std::string> tokens{
        "variable", "v1", ",", "v2", ",", "v3", ";"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    REQUIRE(query->is_synonym_name_declared("v1"));
    REQUIRE(query->get_declared_synonym_entity_name("v1")
                == PQL::kVariableEntityName);
    REQUIRE(query->is_synonym_name_declared("v2"));
    REQUIRE(query->get_declared_synonym_entity_name("v2")
                == PQL::kVariableEntityName);
    REQUIRE(query->is_synonym_name_declared("v3"));
    REQUIRE(query->get_declared_synonym_entity_name("v3")
                == PQL::kVariableEntityName);

    REQUIRE(itr == tokens.end());
  };


  SECTION("Invalid design entity identifier should "
          "throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"var", "v", ";"});
  }

  SECTION("Empty tokens should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {});
  }

  SECTION("Missing semi-colon should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"variable", "v"});
  }

  SECTION("Invalid ident should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"variable", "01234", ";"});
  }
}

TEST_CASE("Test SelectParseState") {
  SelectParseState state;
  SECTION("Select single synonym should parse correctly") {
    std::vector<std::string> tokens{"Select", "v"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    REQUIRE(query->get_selected_synonyms().at(0) == "v");
    REQUIRE(itr == tokens.end());
  }

  SECTION("Select BOOLEAN should parse correctly") {
    std::vector<std::string> tokens{"Select", "BOOLEAN"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    REQUIRE(query->is_boolean_query());
    REQUIRE(itr == tokens.end());
  }

  SECTION("Select BOOLEAN where BOOLEAN is a synonym "
          "should parse as synonym correctly") {
    std::vector<std::string> tokens{"Select", "BOOLEAN"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    query->declare_synonym("BOOLEAN", PQL::kVariableEntityName);

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    REQUIRE(query->get_selected_synonyms().at(0) == "BOOLEAN");
    REQUIRE(itr == tokens.end());
  }

  SECTION("Select elem should parse correctly") {
    std::vector<std::string> tokens{"Select", "<", "v", ">"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    REQUIRE(query->get_selected_synonyms().at(0) == "v");
    REQUIRE(itr == tokens.end());
  }

  SECTION("Select <elem, elem, elem> should parse correctly") {
    std::vector<std::string> tokens{
        "Select", "<", "v1", ",", "v2", ",", "v3", ">"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    std::vector<SynonymName> expected_selected_synonyms{"v1", "v2", "v3"};
    REQUIRE(query->get_selected_synonyms() == expected_selected_synonyms);
    REQUIRE(itr == tokens.end());
  }

  // TODO(JL): Add some error cases here
}

TEST_CASE("Test TupleParseState") {
  TupleParseState state;
  SECTION("<elem> should parse correctly") {
    std::vector<std::string> tokens{"<", "v", ">"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    REQUIRE(query->get_selected_synonyms().at(0) == "v");
    REQUIRE(itr == tokens.end());
  }

  SECTION("<elem> where elem is attrRef should parse correctly") {
    std::vector<std::string> tokens{"<", "s.stmt#", ">"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    REQUIRE(query->get_selected_elems().at(0) == "s.stmt#");
    REQUIRE(itr == tokens.end());
  }

  SECTION("<elem, elem, elem> should parse correctly") {
    std::vector<std::string> tokens{"<", "v1", ",", "v2", ",", "v3", ">"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    std::vector<SynonymName> expected_selected_synonyms{"v1", "v2", "v3"};
    REQUIRE(query->get_selected_synonyms() == expected_selected_synonyms);
    REQUIRE(itr == tokens.end());
  }

  SECTION("<elem, elem, elem> where elem is attrRef"
          "should parse correctly") {
    std::vector<std::string> tokens{
        "<", "s.stmt#", ",", "v.varName", ",", "p.procName", ">"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    std::vector<SynonymName> expected_selected_elems{
        "s.stmt#", "v.varName", "p.procName"};
    REQUIRE(query->get_selected_elems() == expected_selected_elems);
    REQUIRE(itr == tokens.end());
  }

  SECTION("Missing comma should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"<", "v1", "v2", ",", "v3", ">"});
  }

  SECTION("Extra comma should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"<", "v1", ",", "v2", ",", "v3", ",", ">"});
  }

  SECTION("Zero elements should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"<", ">"});
  }

  SECTION("Missing bracket should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"<", "v1", ",", "v2", ",", "v3"});
  }
}

TEST_CASE("Test SuchThatParseState") {
  SuchThatParseState state;
  MasterClauseFactory master_clause_factory;

  SECTION("Such that clause for Modifies should parse correctly") {
    std::vector<std::string> tokens{
        "such", "that", "Modifies", "(", "6", ",", "v", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        PQL::kModifiesRelName,
        query->CreateArgument("6"),
        query->CreateArgument("v"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for Follows should parse correctly") {
    std::vector<std::string> tokens{
        "such", "that", "Follows", "(", "6", ",", "7", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        PQL::kFollowsRelName,
        query->CreateArgument("6"),
        query->CreateArgument("7"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for FollowsT should parse correctly") {
    std::vector<std::string> tokens{
        "such", "that", "Follows*", "(", "6", ",", "10", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        PQL::kFollowsTRelName,
        query->CreateArgument("6"),
        query->CreateArgument("10"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for Parent should parse correctly") {
    std::vector<std::string> tokens{"such", "that", "Parent", "(",
                                    "6", ",", "7", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        PQL::kParentRelName,
        query->CreateArgument("6"),
        query->CreateArgument("7"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for ParentT should parse correctly") {
    std::vector<std::string> tokens{"such", "that", "Parent*", "(",
                                    "6", ",", "7", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        PQL::kParentTRelName,
        query->CreateArgument("6"),
        query->CreateArgument("7"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for Uses should parse correctly") {
    std::vector<std::string> tokens{"such", "that", "Uses",
                                    "(", "6", ",", "v", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        PQL::kUsesRelName,
        query->CreateArgument("6"),
        query->CreateArgument("v"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for Calls should parse correctly") {
    std::vector<std::string> tokens{"such", "that", "Calls",
                                    "(", "\"proc1\"", ",", "\"proc2\"", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        PQL::kCallsRelName,
        query->CreateArgument("\"proc1\""),
        query->CreateArgument("\"proc2\""));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for CallsT should parse correctly") {
    std::vector<std::string> tokens{"such", "that", "Calls*",
                                    "(", "\"proc1\"", ",", "\"proc2\"", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        PQL::kCallsTRelName,
        query->CreateArgument("\"proc1\""),
        query->CreateArgument("\"proc2\""));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for Next should parse correctly") {
    std::vector<std::string> tokens{"such", "that", "Next",
                                    "(", "1", ",", "2", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        PQL::kNextRelName,
        query->CreateArgument("1"),
        query->CreateArgument("2"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause with 'and' should parse correctly") {
    std::vector<std::string> tokens{"such", "that",
                                    "Uses", "(", "6", ",", "v", ")",
                                    "and",
                                    "Modifies", "(", "6", ",", "v", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    std::vector<ClausePtr> expected_clauses;
    expected_clauses.push_back(std::make_unique<UsesClause>(
        query->CreateArgument("6"), query->CreateArgument("v")));
    expected_clauses.push_back(std::make_unique<ModifiesClause>(
        query->CreateArgument("6"), query->CreateArgument("v")));

    REQUIRE(util::CompareVectorOfPointers(
        expected_clauses, query->get_clauses()));
    REQUIRE(itr == tokens.end());
  };


  SECTION("Wrong casing should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"such", "that", "MODIFIES", "(", "6", ",", "v", ")"});
  }

  SECTION("Empty tokens should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {});
  }
}

TEST_CASE("Test PatternParseState") {
  PatternParseState state;
  MasterClauseFactory master_clause_factory;

  SECTION("Pattern clause should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "_", ",", "\"x + y\"", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_modifies_clause = master_clause_factory.Create(
        PQL::kModifiesRelName,
        query->CreateArgument("a"),
        query->CreateArgument("_"));
    auto expected_pattern_clause = master_clause_factory.Create(
        PQL::kPatternRelName,
        query->CreateArgument("a"),
        query->CreateArgument("\"x + y\""));

    REQUIRE(*query->get_clauses().at(0) == *expected_modifies_clause);
    REQUIRE(*query->get_clauses().at(1) == *expected_pattern_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Pattern wildcard clause should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "v", ",", "_", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_modifies_clause = master_clause_factory.Create(
        PQL::kModifiesRelName,
        query->CreateArgument("a"),
        query->CreateArgument("v"));
    auto expected_pattern_clause = master_clause_factory.Create(
        PQL::kPatternRelName,
        query->CreateArgument("a"),
        query->CreateArgument("_"));

    REQUIRE(*query->get_clauses().at(0) == *expected_modifies_clause);
    REQUIRE(*query->get_clauses().at(1) == *expected_pattern_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Pattern wildcard clause should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "variable", ",", "_\"x\"_", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_modifies_clause = master_clause_factory.Create(
        PQL::kModifiesRelName,
        query->CreateArgument("a"),
        query->CreateArgument("variable"));
    auto expected_pattern_clause = master_clause_factory.Create(
        PQL::kPatternRelName,
        query->CreateArgument("a"),
        query->CreateArgument("_\"x\"_"));

    REQUIRE(*query->get_clauses().at(0) == *expected_modifies_clause);
    REQUIRE(*query->get_clauses().at(1) == *expected_pattern_clause);
    REQUIRE(itr == tokens.end());
  }

  SECTION("Pattern clause with 'and' should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "_", ",", "\"x + y\"", ")",
        "and",
        "pattern", "a1", "(", "variable", ",", "_\"x\"_", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    std::vector<ClausePtr> expected_clauses;
    expected_clauses.push_back(std::make_unique<ModifiesClause>(
        query->CreateArgument("a"), query->CreateArgument("_")));
    expected_clauses.push_back(std::make_unique<PatternClause>(
        query->CreateArgument("a"), query->CreateArgument("\"x + y\"")));
    expected_clauses.push_back(std::make_unique<ModifiesClause>(
        query->CreateArgument("a1"), query->CreateArgument("variable")));
    expected_clauses.push_back(std::make_unique<PatternClause>(
        query->CreateArgument("a1"), query->CreateArgument("_\"x\"_")));

    REQUIRE(util::CompareVectorOfPointers(
        expected_clauses, query->get_clauses()));
    REQUIRE(itr == tokens.end());
  };

  SECTION("Wrong casing should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"PATTERN", "a", "(", "_", ",", "x + y", ")"});
  };

  SECTION("Empty tokens should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {});
  };

  SECTION("Missing syn-assign should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"pattern", "(", "_", ",", "x + y", ")"});
  };

  SECTION("Missing bracket should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"pattern", "a", "(", "_", ",", "x + y"});
  };

  SECTION("Invalid expression should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"pattern", "a", "(", "_", ",", "_\" +temp\"_"});
  }
}

TEST_CASE("Test WithParseState") {
  WithParseState state;
  SECTION("With clause should parse correctly") {
    std::vector<std::string> tokens{
        "with", "s.stmt#", "=", "c.value"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    // TODO(JL): Add more requires after adding with clause
    REQUIRE(itr == tokens.end());
  };


  SECTION("With clause with 'and' should parse correctly") {
    std::vector<std::string> tokens{
        "with", "s.stmt#", "=", "c.value",
        "and", "v.varName", "=", "p.procName",
        "and", "11", "=", "\"ident\""};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    // TODO(JL): Add more requires after adding with clause
    REQUIRE(itr == tokens.end());
  };
}

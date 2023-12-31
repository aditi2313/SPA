#include <catch.hpp>

#include "QPS/preprocessor/parse_states/Export.h"
#include "QPS/models/PQL.h"
#include "common/exceptions/QPSExceptions.h"

using namespace qps; // NOLINT

// Helper method for testing
void TestErrorCase(ParseState &state, std::vector<std::string> tokens) {
  std::unique_ptr<Query> query = std::make_unique<Query>();
  auto itr = tokens.begin();
  REQUIRE_THROWS_AS(
      state.Parse(tokens, itr, query), PqlSyntaxErrorException);
}

// Helper method for testing
void TestErrorCase(
    ParseState &state,
    QueryPtr &query,
    std::vector<std::string> tokens) {
  auto itr = tokens.begin();
  REQUIRE_THROWS_AS(
      state.Parse(tokens, itr, query), PqlSyntaxErrorException);
}

// Helper method used only in testing
std::unique_ptr<SynonymArg> CreateSynonym(
    SynonymName syn_name, EntityType entity_type) {
  return std::make_unique<SynonymArg>(syn_name, entity_type);
}

// Helper method used only in testing
std::unique_ptr<Wildcard> CreateWildcard() {
  return std::make_unique<Wildcard>();
}

TEST_CASE("Test DeclarationParseState") {
  DeclarationParseState state;

  SECTION("Single declaration should parse correctly") {
    std::vector<std::string> tokens{"variable", "v", ";"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    REQUIRE(query->is_synonym_name_declared("v"));
    REQUIRE(query->get_declared_synonym_entity_type("v")
                == EntityType::kVariable);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Multiple declarations should parse correctly") {
    std::vector<std::string> tokens{
        "variable", "v1", ",", "v2", ",", "v3", ";"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    REQUIRE(query->is_synonym_name_declared("v1"));
    REQUIRE(query->get_declared_synonym_entity_type("v1")
                == EntityType::kVariable);
    REQUIRE(query->is_synonym_name_declared("v2"));
    REQUIRE(query->get_declared_synonym_entity_type("v2")
                == EntityType::kVariable);
    REQUIRE(query->is_synonym_name_declared("v3"));
    REQUIRE(query->get_declared_synonym_entity_type("v3")
                == EntityType::kVariable);

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
    auto &selected_synonyms = query->get_selected_synonyms();

    REQUIRE(selected_synonyms.at(0) == "v");
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
    query->declare_synonym("BOOLEAN", EntityType::kVariable);

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto &selected_synonyms = query->get_selected_synonyms();

    REQUIRE(selected_synonyms.at(0) == "BOOLEAN");
    REQUIRE(itr == tokens.end());
  }

  SECTION("Select <elem> should parse correctly") {
    std::vector<std::string> tokens{"Select", "<", "v", ">"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto &selected_synonyms = query->get_selected_synonyms();

    REQUIRE(selected_synonyms.at(0) == "v");
    REQUIRE(itr == tokens.end());
  }

  SECTION("Select <elem, elem, elem> should parse correctly") {
    std::vector<std::string> tokens{
        "Select", "<", "v1", ",", "v2", ",", "v3", ">"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    std::vector<SynonymName> expected_selected_synonyms{"v1", "v2", "v3"};
    auto &selected_synonyms = query->get_selected_synonyms();

    REQUIRE(selected_synonyms == expected_selected_synonyms);
    REQUIRE(itr == tokens.end());
  }

  SECTION("Select <elem> where elem is attrRef "
          "should parse correctly") {
    std::vector<std::string> tokens{"Select", "<", "s.stmt#", ">"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    REQUIRE(query->get_selected_elems().at(0) == "s.stmt#");
    REQUIRE(itr == tokens.end());
  }

  SECTION("Select <elem, elem, elem> where elem is attrRef"
          "should parse correctly") {
    std::vector<std::string> tokens{
        "Select", "<", "s.stmt#", ",", "v.varName", ",", "p.procName", ">"};
    std::unique_ptr<Query> query = std::make_unique<Query>();

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    std::vector<SynonymName> expected_selected_elems{
        "s.stmt#", "v.varName", "p.procName"};
    REQUIRE(query->get_selected_elems() == expected_selected_elems);
    REQUIRE(itr == tokens.end());
  }

  SECTION("Missing comma should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {
        "Select", "<", "v1", "v2", ",", "v3", ">"});
  }

  SECTION("Extra comma should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {
        "Select", "<", "v1", ",", "v2", ",", "v3", ",", ">"});
  }

  SECTION("Zero elements should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"Select", "<", ">"});
  }

  SECTION("Missing bracket should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {
        "Select", "<", "v1", ",", "v2", ",", "v3"});
  }
}

TEST_CASE("Test SuchThatParseState") {
  SuchThatParseState state;
  MasterArgumentFactory master_argument_factory;
  MasterClauseFactory master_clause_factory;

  SECTION("Such that clause for Affects should parse correctly") {
    std::vector<std::string> tokens{
        "such", "that", "Affects", "(", "6", ",", "7", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        ClauseType::kAffects,
        master_argument_factory.Create(ArgumentType::kIntegerArg, "6"),
        master_argument_factory.Create(ArgumentType::kIntegerArg, "7"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for Affects should parse correctly") {
    std::vector<std::string> tokens{
        "such", "that", "Affects*", "(", "6", ",", "7", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        ClauseType::kAffectsT,
        master_argument_factory.Create(ArgumentType::kIntegerArg, "6"),
        master_argument_factory.Create(ArgumentType::kIntegerArg, "7"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for Modifies should parse correctly") {
    std::vector<std::string> tokens{
        "such", "that", "Modifies", "(", "6", ",", "v", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        ClauseType::kModifies,
        master_argument_factory.Create(ArgumentType::kIntegerArg, "6"),
        master_argument_factory.Create(ArgumentType::kSynonymArg, "v"));

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
        ClauseType::kFollows,
        master_argument_factory.Create(ArgumentType::kIntegerArg, "6"),
        master_argument_factory.Create(ArgumentType::kIntegerArg, "7"));

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
        ClauseType::kFollowsT,
        master_argument_factory.Create(ArgumentType::kIntegerArg, "6"),
        master_argument_factory.Create(ArgumentType::kIntegerArg, "10"));

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
        ClauseType::kParent,
        master_argument_factory.Create(ArgumentType::kIntegerArg, "6"),
        master_argument_factory.Create(ArgumentType::kIntegerArg, "7"));

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
        ClauseType::kParentT,
        master_argument_factory.Create(ArgumentType::kIntegerArg, "6"),
        master_argument_factory.Create(ArgumentType::kIntegerArg, "7"));

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
        ClauseType::kUses,
        master_argument_factory.Create(ArgumentType::kIntegerArg, "6"),
        master_argument_factory.Create(ArgumentType::kSynonymArg, "v"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for Calls should parse correctly") {
    std::vector<std::string> tokens{"such", "that", "Calls",
                                    "(", "\"", "proc1", "\"", ",",
                                    "\"", "proc2", "\"", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        ClauseType::kCalls,
        master_argument_factory.Create(ArgumentType::kIdentArg, "proc1"),
        master_argument_factory.Create(ArgumentType::kIdentArg, "proc2"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for CallsT should parse correctly") {
    std::vector<std::string> tokens{"such", "that", "Calls*",
                                    "(", "\"", "proc1", "\"", ",",
                                    "\"", "proc2", "\"", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        ClauseType::kCallsT,
        master_argument_factory.Create(ArgumentType::kIdentArg, "proc1"),
        master_argument_factory.Create(ArgumentType::kIdentArg, "proc2"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };


  SECTION("Such that clause for Next should parse correctly") {
    std::vector<std::string> tokens{"such", "that", "Next", "(",
                                    "1", ",", "2", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        ClauseType::kNext,
        master_argument_factory.Create(ArgumentType::kIntegerArg, "1"),
        master_argument_factory.Create(ArgumentType::kIntegerArg, "2"));

    REQUIRE(*query->get_clauses().at(0) == *expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for Next* should parse correctly") {
    std::vector<std::string> tokens{"such", "that", "Next*", "(",
                                    "1", ",", "2", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_clause = master_clause_factory.Create(
        ClauseType::kNextT,
        master_argument_factory.Create(ArgumentType::kIntegerArg, "1"),
        master_argument_factory.Create(ArgumentType::kIntegerArg, "2"));

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
        master_argument_factory.Create(ArgumentType::kIntegerArg, "6"),
        master_argument_factory.Create(ArgumentType::kSynonymArg, "v")));
    expected_clauses.push_back(std::make_unique<ModifiesClause>(
        master_argument_factory.Create(ArgumentType::kIntegerArg, "6"),
        master_argument_factory.Create(ArgumentType::kSynonymArg, "v")));

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
  MasterArgumentFactory master_argument_factory;
  MasterClauseFactory master_clause_factory;

  SECTION("Pattern Assign clause should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "_", ",", "\"", "x + y", "\"", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    query->declare_synonym("a", EntityType::kAssign);
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_modifies_clause = master_clause_factory.Create(
        ClauseType::kModifies,
        CreateSynonym(
            "a", EntityType::kAssign),
        CreateWildcard());
    auto expected_pattern_clause = master_clause_factory.Create(
        ClauseType::kPatternAssign,
        CreateSynonym(
            "a", EntityType::kAssign),
        master_argument_factory.Create(
            ArgumentType::kExactExprArg, "x + y"));

    REQUIRE(*query->get_clauses().at(0) == *expected_modifies_clause);
    REQUIRE(*query->get_clauses().at(1) == *expected_pattern_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Pattern While clause should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "w", "(", "_", ",", "_", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    query->declare_synonym("w", EntityType::kWhile);
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_pattern_clause = master_clause_factory.Create(
        ClauseType::kPatternWhile,
        CreateSynonym(
            "w", EntityType::kWhile),
        CreateWildcard());

    REQUIRE(*query->get_clauses().at(0) == *expected_pattern_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Pattern If clause should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "if", "(", "_", ",", "_", ",", "_", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    query->declare_synonym("if", EntityType::kIf);
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_pattern_clause = master_clause_factory.Create(
        ClauseType::kPatternIf,
        CreateSynonym(
            "if", EntityType::kIf),
        CreateWildcard());

    REQUIRE(*query->get_clauses().at(0) == *expected_pattern_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Pattern wildcard clause should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "v", ",", "_", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    query->declare_synonym("a", EntityType::kAssign);
    query->declare_synonym("v", EntityType::kVariable);
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_modifies_clause = master_clause_factory.Create(
        ClauseType::kModifies,
        CreateSynonym(
            "a", EntityType::kAssign),
        master_argument_factory.Create(ArgumentType::kSynonymArg, "v"));
    auto expected_pattern_clause = master_clause_factory.Create(
        ClauseType::kPatternAssign,
        CreateSynonym(
            "a", EntityType::kAssign),
        CreateWildcard());

    REQUIRE(*query->get_clauses().at(0) == *expected_modifies_clause);
    REQUIRE(*query->get_clauses().at(1) == *expected_pattern_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Pattern wildcard clause should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "variable", ",",
        "_", "\"", "x", "\"", "_", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    query->declare_synonym("a", EntityType::kAssign);
    query->declare_synonym("variable", EntityType::kVariable);
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    auto expected_modifies_clause = master_clause_factory.Create(
        ClauseType::kModifies,
        CreateSynonym(
            "a", EntityType::kAssign),
        master_argument_factory.Create(ArgumentType::kSynonymArg, "variable"));
    auto expected_pattern_clause = master_clause_factory.Create(
        ClauseType::kPatternAssign,
        CreateSynonym("a", EntityType::kAssign),
        master_argument_factory.Create(
            ArgumentType::kWildcardExprArg, "x"));

    REQUIRE(*query->get_clauses().at(0) == *expected_modifies_clause);
    REQUIRE(*query->get_clauses().at(1) == *expected_pattern_clause);
    REQUIRE(itr == tokens.end());
  }

  SECTION("Pattern clause with 'and' should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "_", ",", "\"", "x + y", "\"", ")",
        "and",
        "a1", "(", "variable", ",", "_", "\"", "x", "\"", "_", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    query->declare_synonym("a", EntityType::kAssign);
    query->declare_synonym("a1", EntityType::kAssign);
    query->declare_synonym("variable", EntityType::kVariable);

    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);

    std::vector<ClausePtr> expected_clauses;
    expected_clauses.push_back(std::make_unique<ModifiesClause>(
        CreateSynonym(
            "a", EntityType::kAssign),
        CreateWildcard()));

    expected_clauses.push_back(std::make_unique<PatternAssignClause>(
        CreateSynonym(
            "a", EntityType::kAssign),
        master_argument_factory.Create(
            ArgumentType::kExactExprArg, "x + y")));

    expected_clauses.push_back(std::make_unique<ModifiesClause>(
        CreateSynonym(
            "a1", EntityType::kAssign),
        master_argument_factory.Create(ArgumentType::kSynonymArg, "variable")));

    expected_clauses.push_back(std::make_unique<PatternAssignClause>(
        CreateSynonym(
            "a1", EntityType::kAssign),
        master_argument_factory.Create(
            ArgumentType::kWildcardExprArg, "x")));

    REQUIRE(util::CompareVectorOfPointers(
        expected_clauses, query->get_clauses()));
    REQUIRE(itr == tokens.end());
  };

  SECTION("Wrong casing should throw PqlSyntaxErrorException") {
    std::unique_ptr<Query> query = std::make_unique<Query>();
    query->declare_synonym("a", EntityType::kAssign);
    TestErrorCase(state, query, {"PATTERN", "a", "(", "_", ",", "x + y", ")"});
  };

  SECTION("Empty tokens should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {});
  };

  SECTION("Missing syn-assign should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"pattern", "(", "_", ",", "x + y", ")"});
  };

  SECTION("Missing bracket should throw PqlSyntaxErrorException") {
    std::unique_ptr<Query> query = std::make_unique<Query>();
    query->declare_synonym("a", EntityType::kAssign);
    TestErrorCase(state, query, {"pattern", "a", "(", "_", ",", "x + y"});
  };

  SECTION("Invalid expression should throw PqlSyntaxErrorException") {
    std::unique_ptr<Query> query = std::make_unique<Query>();
    query->declare_synonym("a", EntityType::kAssign);
    TestErrorCase(
        state, query, {"pattern", "a", "(", "_", ",", "_\" +temp\"_"});
  }
}

TEST_CASE("Test WithParseState") {
  WithParseState state;
  SECTION("With clause should parse correctly") {
    std::vector<std::string> tokens{
        "with", "s", ".", "stmt#", "=", "c", ".", "value"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    // TODO(JL): Add more requires after adding with clause
    REQUIRE(itr == tokens.end());
  };


  SECTION("With clause with 'and' should parse correctly") {
    std::vector<std::string> tokens{
        "with", "s", ".", "stmt#", "=", "c", ".", "value",
        "and", "v", ".", "varName", "=", "p", ".", "procName",
        "and", "11", "=", "\"", "ident", "\""};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.Parse(tokens, itr, query);
    // TODO(JL): Add more requires after adding with clause
    REQUIRE(itr == tokens.end());
  };
}

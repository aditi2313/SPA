#include "TestWrapper.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../../spa/src/QPS/QPS.h"
#include "../../spa/src/SP/SourceProcessor.h"
#include "SP/validators/ProgramValidator.h"
#include "SP/visitors/AssignVisitor.h"
#include "SP/visitors/DataVisitor.h"
#include "SP/visitors/ModifiesVisitor.h"
#include "SP/visitors/ParentVisitor.h"
#include "SP/validators/ProgramValidator.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper *WrapperFactory::wrapper = 0;
AbstractWrapper *WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
  pkb_relation_ = std::make_unique<pkb::PKBRelationTable>();
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
  // call your parser to do the parsing
  // ...rest of your code...

  // Read source program from file
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "Unable to open file";
    return;
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string program = buffer.str();
  file.close();

  // Parse and generate AST
  sp::SourceProcessor source_processor;
  auto root = source_processor.ParseProgram(program);

  // Validate AST
  auto validator = sp::ProgramValidator(root);
  if (!validator.Validate()) {
    // TODO(aizatazhar) use custom exception and at the validator level
    throw std::runtime_error("Program is not semantically valid");
  }

  auto writer = std::make_unique<pkb::PKBWrite>(std::move(pkb_relation_));

  sp::AssignVisitor av(std::move(writer));
  root->AcceptVisitor(&av);
  writer = av.EndVisit();

  sp::DataVisitor dv(std::move(writer));
  root->AcceptVisitor(&dv);
  writer = dv.EndVisit();

  sp::ModifiesVisitor mv(std::move(writer));
  root->AcceptVisitor(&mv);
  writer = mv.EndVisit();

  sp::ParentVisitor pv(std::move(writer));
  root->AcceptVisitor(&pv);
  writer = pv.EndVisit();

  pkb_relation_ = writer->EndWrite();
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string> &results) {
  qps::QPS qps;
  auto reader = std::make_unique<pkb::PKBRead>(std::move(pkb_relation_));
  pkb_relation_ = qps.evaluate(query, results, reader)->EndRead();
}

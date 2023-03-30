#include "TestWrapper.h"

#include <iostream>
#include <sstream>
#include <filesystem>

#include "QPS/QPS.h"
#include "SP/SourceProcessor.h"
#include "common/logging/OutputRedirector.h"

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
  pkb_cache_ = std::make_unique<pkb::PKBCache>();
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

  // Redirect cout logs
  // autotester_path_mac = ../Code05/cmake-build-debug/src/autotester
  // autotester_path_windows = ../Code05/out/build/x64-Debug/src/autotester
  std::string logger_path;
  #ifdef _WIN32
    logger_path = "../../../../src/spa/src/common/logging/logging_output.txt";
  #else
    logger_path = "../../../src/spa/src/common/logging/logging_output.txt";
  #endif
  std::filesystem::path cwd = std::filesystem::current_path();
  std::filesystem::path output_path = cwd / logger_path;
  logging::OutputRedirector redirector(std::cout, output_path.c_str());

  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, pkb_relation_);
  pkb_cache_->clear();  // Important: reset cache between programs
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string> &results) {
  qps::QPS qps;
  auto reader = std::make_unique<pkb::PKBRead>(
      std::move(pkb_relation_), std::move(pkb_cache_));
  qps.evaluate(query, results, reader);
  pkb_cache_ = reader->RetrieveCache();
  pkb_relation_ = reader->EndRead();
}

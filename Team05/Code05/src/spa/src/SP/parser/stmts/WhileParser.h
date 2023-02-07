#pragma once

#include <memory>
#include <utility>

#include "SP/parser/Parser.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class WhileParser : public Parser<ast::WhileNode>{};
}  // namespace sp

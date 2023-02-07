#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class IfParser : public Parser<ast::IfNode>{};
}  // namespace sp
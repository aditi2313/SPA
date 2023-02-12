#pragma once

#include <memory>
#include <utility>

#include "SP/parser/Parser.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class IfParser : public SelectClParser<ast::IfNode> {};
}  // namespace sp

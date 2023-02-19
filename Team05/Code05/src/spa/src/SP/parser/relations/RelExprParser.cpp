#include "RelExprParser.h"

#include <memory>
#include <utility>

#include "common/exceptions/SPExceptions.h"
#include "models/AST/Token.h"

namespace sp {

std::unique_ptr<ast::RelExprNode> RelExprParser::parse(Lexer& lxr) {
  auto left_factor = rel_parser_.parse(lxr);
  auto middle = lxr.get_tok();

  lxr.Increment();
  auto right_factor = rel_parser_.parse(lxr);

  if (middle == Token::kTokLess) {
    return std::make_unique<ast::LessThanNode>(std::move(left_factor),
                                               std::move(right_factor));
  }
  if (middle == Token::kTokLessEqual) {
    return std::make_unique<ast::LessThanEqualNode>(std::move(left_factor),
                                                    std::move(right_factor));
  }
  if (middle == Token::kTokGreater) {
    return std::make_unique<ast::MoreThanNode>(std::move(left_factor),
                                               std::move(right_factor));
  }
  if (middle == Token::kTokGreaterEqual) {
    return std::make_unique<ast::MoreThanEqualNode>(std::move(left_factor),
                                                    std::move(right_factor));
  }

  if (middle == Token::kTokEquiv) {
    return std::make_unique<ast::EqualNode>(std::move(left_factor),
                                            std::move(right_factor));
  }

  if (middle == Token::kTokNotEqual) {
    return std::make_unique<ast::NotEqualNode>(std::move(left_factor),
                                               std::move(right_factor));
  }

  throw ParseRelationSyntaxException(
      "Missing relation in relational expression");
}
}  // namespace sp

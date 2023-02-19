import random

## Script for generating random source

variables = ["a", "b", "c", "d"]
constants = ["10", "1000", "0", "-1"]
conditions = ["||", "&&"]
operators = ["+", "-", "*", "/"]
read_print = ["read", "print"]

def grab_rand(ls):
  return ls[random.randint(0, len(ls) - 1)]


class ExpressionGenerator:
  def __init__(self):
    pass

  def generate(self, depth):
    s = random.randint(0, 10)    
    result = ""
    for _ in range(s):
      result += grab_rand(variables)
      result += grab_rand(operators)
    result += grab_rand(variables)
    return result

class AssignmentGenerator:
  def __init__(self):
    pass
  def generate(self, depth):
    s = random.randint(0, 10)
    result = ""
    result += grab_rand(variables)
    result += "="
    for _ in range(s):
      result += grab_rand(variables)
      result += grab_rand(operators)
    result += grab_rand(variables)
    result += ";"
    return result

class ReadPrintGenerator:
  def __init__(self):
    pass
  def generate(self, depth):
    return grab_rand(read_print) + " " + grab_rand(variables) + ";"

class CodeBlockGenerator:
  def __init__(self):
    self.stmt_gen = StatementGenerator()    
  def generate(self, depth):
    num_of_lines = random.randint(1, 10)
    result = "{\n"
    for _ in range(num_of_lines):
      result += self.stmt_gen.generate(depth)
    result += "}\n"
    return result

class ConditionGenerator:
  def __init__(self):
    pass
  def generate(self, depth):
    cond = ""
    expr_gen = ExpressionGenerator()
    cond += "("
    cond += expr_gen.generate(depth)
    
    cond += "<"
    cond += expr_gen.generate(depth)
    cond += ")"
    cond += grab_rand(conditions)
    cond += "("
    cond += expr_gen.generate(depth)
    
    cond += ">="
    cond += expr_gen.generate(depth)
    cond += ")"
    return cond

class IfBlockGenerator:
  def __init__(self):
    self.c_block = CodeBlockGenerator()
    self.c_gen = ConditionGenerator()
  def generate(self, depth):
    result = "if ("
    
    result += self.c_gen.generate(depth) + ")"
    result += "then "
    result += self.c_block.generate(depth + 1)
    result += "else "
    result += self.c_block.generate(depth + 1)
    return result

class WhileBlockGenerator:
  def __init__(self):
    self.c_gen = ConditionGenerator()
    self.c_block = CodeBlockGenerator()
  def generate(self, depth):
    result = "while ("
    result += self.c_gen.generate(depth)
    result += ")"
    result += self.c_block.generate(depth + 1)
    return result



class StatementGenerator:  
  def __init__(self):
    pass
  def generate(self, depth):
    if depth >= 5:
      return grab_rand(alt_stmt_gens).generate(depth) + "\n"
    return grab_rand(stmt_gens).generate(depth) + "\n"
stmt_gens = [
    WhileBlockGenerator(),
    IfBlockGenerator(),    
    ReadPrintGenerator(),
    AssignmentGenerator()
  ]

alt_stmt_gens = [
  ReadPrintGenerator(),
    AssignmentGenerator()
  ]

def procedure_gen(name):
  result = "procedure " + name
  result += CodeBlockGenerator().generate(0)
  return result

## Generating a valid source
if __name__ == "__main__":
  print(procedure_gen("name"))

import random

## Script for generating random source

variables = ["a", "b", "c", "d", "varx", "v1", "v2", "v3",\
  "someString", "someVariable", "constants",\
  "variables", "procedure", "if", "ils", "rapid"]
             
constants = ["10", "1000", "0", "-1", "100"]
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
    s = random.randint(0, 1000)
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
  def generate(self, depth, num_of_lines = 10):
    
    result = "{\n"
    for _ in range(num_of_lines):
      r = self.stmt_gen.generate(depth)
      if not r:
        return False
      result += r
    result += "}"
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
    inner_one = self.c_gen.generate(depth+1)
    if not inner_one:
      return False
    inner_two =self.c_block.generate(depth + 1)
    if not inner_two:
      return False
    result += inner_one
    result += "else "
    result += inner_two    
    return result

class WhileBlockGenerator:
  def __init__(self):
    self.c_gen = ConditionGenerator()
    self.c_block = CodeBlockGenerator()
  def generate(self, depth):
    internal_stmts = self.c_block.generate(depth + 1)
    if not internal_stmts:
      return False
    result = "while ("
    result += self.c_gen.generate(depth)
    result += ")"
    result += internal_stmts    
    return result



class StatementGenerator:
  max_stmt = 500
  curr_stmt = 0
  def __init__(self):
    pass
  def generate(self, depth):
    if StatementGenerator.curr_stmt == StatementGenerator.max_stmt:
      return False
    if depth >= 5:
      result = grab_rand(alt_stmt_gens).generate(depth)
    else: 
      result = grab_rand(stmt_gens).generate(depth)
    if not result:
      return False
    StatementGenerator.curr_stmt += 1
    return result + "\n"
    
stmt_gens = [
    #WhileBlockGenerator(),
    #IfBlockGenerator(),    
    #ReadPrintGenerator(),
    AssignmentGenerator()
  ]

alt_stmt_gens = [
  #ReadPrintGenerator(),
    AssignmentGenerator()
  ]

def procedure_gen(name):
  result = "procedure " + name
  r = ""
  while True:
    r = CodeBlockGenerator().generate(4, 5)
    if r:
      break
  result += r
  return result

def deep_while_generator(depth = 500):  
  if depth == 0:
    return "read x;"
  next = deep_while_generator(depth-1)
  return "while (x  < 0) {" + next + "}"
    

def deep_if_generator(depth = 500):
  if depth <= 2:
    result = ""
    for _ in range(depth):
      result += "read x;"
    return result
  result = "if (x >= 100) then {"
  total = depth - 1
  f1 = random.randint(1, total - 1)
  f2 = total - f1
  result += deep_if_generator(f1)
  result += "} else {"
  result += deep_if_generator(f2)
  result += "}"
  return result




def generate_rand_proc():
  curr = 0
  name = "p"
  ctr = 1
  while curr < 500:    
    StatementGenerator.max_stmt = 100
    print(procedure_gen(name + str(ctr)))
    ctr += 1
    curr += StatementGenerator.curr_stmt
    StatementGenerator.curr_stmt = 0
    
## Generating a valid source
if __name__ == "__main__":
  
  generate_rand_proc()
  #print(StatementGenerator.curr_stmt)
  #print(deep_while_generator())
  #print(deep_if_generator())
  #for i in range(1, 500):
  #  print(i, ",", end="")
  

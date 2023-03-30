import random
from enum import Enum

# Python script for generating random queries


# VARIABLE - SET ACCORDING TO YOUR PROGRAM #
num_stmts = 40
variables = ["x", "y", "z"]
procedures = ["proc1", "proc2"]

# CONSTANTS - DO NOT CHANGE #
declarations = "stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;"
int_attrname = ["c.value", "s.stmt#", "r.stmt#", 
                 "pn.stmt#", "call.stmt#", "w.stmt#", 
                 "ifs.stmt#", "a.stmt#"]
ident_attrname = ["p.procName", "call.procName", "v.varName",
                   "read.varName", "pn.varName"]

get_wildcard = lambda : "_"

# INTEGER | synonym | wildcard
stmt_ref = [
   lambda : str(random.randint(1, num_stmts+1)), 
   lambda : "s", 
   get_wildcard]
var_ent_ref = [
   lambda : "\"" + random.choice(variables) + "\"", 
   lambda : "v",
   get_wildcard]
proc_ent_ref = [
   lambda : "\"" + random.choice(procedures) + "\"", 
   lambda : "p",
   get_wildcard]
modifies_uses_lhs = stmt_ref + [lambda : "p"]
int_attr_ref = [lambda str=str: str for str in int_attrname]
ident_attr_ref = [lambda str=str: str for str in ident_attrname]
# exact expr, wildcard expr, wildcard
expr_spec = [lambda : random.choice(variables),
             lambda : "_\"" + random.choice(variables) + "\"_", 
             get_wildcard]


class GeneratorType(Enum):
  SUCH_THAT = 1
  WITH = 2
  PATTERN_ASSIGN = 3
  PATTERN_WHILE = 4
  PATTERN_IF = 5

class OneArgGenerator:  
  def __init__(self, params, generator_type):
    self.__generator_type = generator_type
    self.__params = params
  def generate(self):
    result = []
    for param in self.__params:
      if self.__generator_type == GeneratorType.PATTERN_IF:
            result.append(f"pattern ifs({param()}, _, _)")
      elif self.__generator_type == GeneratorType.PATTERN_WHILE:
            result.append(f"pattern w({param()}, _)")
    return result
  
  def generate_random(self):
      param = random.choice(self.__params)()
      if self.__generator_type == GeneratorType.PATTERN_IF:
          return f"pattern ifs({param}, _, _)"
      elif self.__generator_type == GeneratorType.PATTERN_WHILE:
          return f"pattern w({param}, _)"
      
## Generator for clauses with two arguments
## To generate permutations of clauses
class TwoArgGenerator:  
  def __init__(self, clause, left_params, right_params, generator_type = GeneratorType.SUCH_THAT):
    self.__generator_type = generator_type
    self.__clause = clause
    self.__left_params = left_params
    self.__right_params = right_params
  def generate(self):
    result = []
    for left in self.__left_params:
      for right in self.__right_params:
        if self.__generator_type == GeneratorType.SUCH_THAT:
            result.append(f"such that {self.__clause}({left()}, {right()})")
        elif self.__generator_type == GeneratorType.WITH:
            result.append(f"with {left()} = {right()}")
        elif self.__generator_type == GeneratorType.PATTERN_ASSIGN:
           result.append(f"pattern a ({left()}, {right()})")
    return result
  
  def generate_random(self):
     lhs = random.choice(self.__left_params)()
     rhs = random.choice(self.__right_params)()
     if self.__generator_type == GeneratorType.SUCH_THAT:
          return f"such that {self.__clause}({lhs}, {rhs})"
     elif self.__generator_type == GeneratorType.WITH:
          return f"with {lhs} = {rhs}"
     elif self.__generator_type == GeneratorType.PATTERN_ASSIGN:
        return f"pattern a({lhs}, {rhs})"

def create_generators():
  generators = [
    TwoArgGenerator("Modifies", modifies_uses_lhs, var_ent_ref),
    TwoArgGenerator("Uses", modifies_uses_lhs, var_ent_ref),
    TwoArgGenerator("Parent", stmt_ref, stmt_ref),
    TwoArgGenerator("Parent*", stmt_ref, stmt_ref),
    TwoArgGenerator("Follows", stmt_ref, stmt_ref),
    TwoArgGenerator("Follows*", stmt_ref, stmt_ref),
    TwoArgGenerator("Next", stmt_ref, stmt_ref),
    TwoArgGenerator("Next*", stmt_ref, stmt_ref),
    TwoArgGenerator("Affects", stmt_ref, stmt_ref),
    TwoArgGenerator("Affects*", stmt_ref, stmt_ref),
    TwoArgGenerator("Calls", proc_ent_ref, proc_ent_ref),
    TwoArgGenerator("Calls*", proc_ent_ref, proc_ent_ref),
    TwoArgGenerator("with", int_attr_ref, int_attr_ref, GeneratorType.WITH),
    TwoArgGenerator("with", ident_attr_ref, ident_attr_ref, GeneratorType.WITH),
    OneArgGenerator(var_ent_ref, GeneratorType.PATTERN_IF),
    OneArgGenerator(var_ent_ref, GeneratorType.PATTERN_WHILE),
    TwoArgGenerator("pattern a", var_ent_ref, expr_spec, GeneratorType.PATTERN_ASSIGN),
  ]
  return generators


def CreateSingleSuchThatQueries():
  entities = ["s", "v", "r", "BOOLEAN"]
  generators = create_generators()
  ctr = 1
  for generator in generators:
    clauses = generator.generate()
    for clause in clauses:
      for entity in entities:
        print(ctr, "-", "comment")
        ctr += 1
        print(declarations)
        print("Select", entity, "such that", clause)
        print("none")
        print(5000)


def CreateMultiClauseQuery(num_clauses, num_queries):
  selected_elem = ["BOOLEAN"]
  generators = create_generators()
  for ctr in range(1, num_queries+1):
    print(ctr, "-", "comment")
    print(declarations)
    print("Select BOOLEAN", end=" ")
    # Choose num_clauses random clauses
    rand_gens = random.sample(generators, num_clauses)
    for gen in rand_gens:
       print(gen.generate_random(), end=" ")
    print("") # newline
    print("none")
    print(5000)
    


if __name__ == "__main__":
  # CreateSingleSuchThatQueries()
  CreateMultiClauseQuery(7, 100)
  








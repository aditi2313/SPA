import random
from enum import Enum
import sys

# Python script for generating random queries
# INTENDED USAGE:
# First set the following three variables below according to
# the variables/procedures/number of statements in your own
# source program
# Then run python3 query_generator.py `num_clauses` `num_queries`
# Example: python3 query_generator.py 7 100
# will generate 100 random queries with 7 clauses each

# VARIABLE - SET ACCORDING TO YOUR PROGRAM #
num_stmts = 18
variables = ["x", "y", "z", "i", "v",]
procedures = ["First", "Second", "Third"]

# CONSTANTS - DO NOT CHANGE #
declarations = "stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;"
stmt_syns = ["s", "r", "pn", "call", "w", "ifs", "a"]
int_attrname = ["c.value"] + [syn + ".stmt#" for syn in stmt_syns]
ident_attrname = ["p.procName", "call.procName", "v.varName",
                   "r.varName", "pn.varName"]
get_wildcard = lambda : "_"
get_rand_stmt = lambda : str(random.randint(1, num_stmts))
get_rand_proc = lambda : f"\"{random.choice(procedures)}\""
get_rand_var = lambda : f"\"{random.choice(variables)}\""
get_rand_symt_syn = lambda : random.choice(stmt_syns)
var_syn = "v"
proc_syn = "p"

# INTEGER | synonym | wildcard
stmt_ref = [get_rand_stmt, 
            get_rand_symt_syn,
            get_wildcard]
assign_stmt_ref = [get_rand_stmt, 
                  lambda : "a",
                  get_wildcard]
var_ent_ref = [get_rand_var, 
              lambda : var_syn,
              get_wildcard]
proc_ent_ref = [get_rand_proc, 
                lambda : proc_syn,
                get_wildcard]
modifies_uses_lhs = [get_rand_symt_syn, 
                      lambda : proc_syn,
                      get_rand_stmt,
                      get_rand_proc]
int_attr_ref = [lambda str=str: str for str in int_attrname]
ident_attr_ref = [lambda str=str: str for str in ident_attrname]
# exact expr, wildcard expr, wildcard
expr_spec = [get_rand_var,
             lambda : f"_\"{random.choice(variables)}\"_", 
             get_wildcard]

def is_synonym(arg):
   if not arg[0].isalpha():
      return False
   for c in arg:
      if not c.isalnum():
         return False
   return True
    
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

  def generate_exhaustive(self):
    result = []
    for param in self.__params:
      if self.__generator_type == GeneratorType.PATTERN_IF:
            result.append(f"pattern ifs({param()}, _, _)")
      elif self.__generator_type == GeneratorType.PATTERN_WHILE:
            result.append(f"pattern w({param()}, _)")
    return result
  
  def generate_random(self):
      param = random.choice(self.__params)()
      used_synonyms = []
      if is_synonym(param):
         used_synonyms.append(param)
      query_str = ""
      if self.__generator_type == GeneratorType.PATTERN_IF:
          query_str = f"pattern ifs({param}, _, _)"
      elif self.__generator_type == GeneratorType.PATTERN_WHILE:
          query_str = f"pattern w({param}, _)"
      return query_str, used_synonyms
      
## Generator for clauses with two arguments
## To generate permutations of clauses
class TwoArgGenerator:  
  def __init__(self, clause, left_params, right_params, generator_type = GeneratorType.SUCH_THAT):
    self.__generator_type = generator_type
    self.__clause = clause
    self.__left_params = left_params
    self.__right_params = right_params

  def generate_exhaustive(self):
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
     used_synonyms = []
     if is_synonym(lhs):
      used_synonyms.append(lhs)

     if is_synonym(rhs):
       used_synonyms.append(rhs)
     query_str = ""
     if self.__generator_type == GeneratorType.SUCH_THAT:
        query_str = f"such that {self.__clause}({lhs}, {rhs})"
     elif self.__generator_type == GeneratorType.WITH:
        query_str = f"with {lhs} = {rhs}"
     elif self.__generator_type == GeneratorType.PATTERN_ASSIGN:
        query_str = f"pattern a({lhs}, {rhs})"
     return query_str, used_synonyms

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
    TwoArgGenerator("Affects", assign_stmt_ref, assign_stmt_ref),
    TwoArgGenerator("Affects*", assign_stmt_ref, assign_stmt_ref),
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
    clauses = generator.generate_exhaustive()
    for clause in clauses:
      for entity in entities:
        print(ctr, "-", "comment")
        ctr += 1
        print(declarations)
        print("Select", entity, "such that", clause)
        print("none")
        print(5000)


def CreateMultiClauseQuery(num_clauses, num_queries):
  generators = create_generators()
  for ctr in range(1, num_queries+1):
    clauses = []
    used_synonyms = set()
     # Choose num_clauses random clauses
    rand_gens = random.sample(generators, num_clauses)
    for gen in rand_gens:
       clause, synonyms_in_clause = gen.generate_random()
       clauses.append(clause)
       used_synonyms.update(synonyms_in_clause)

    used_synonyms = list(used_synonyms)
    selected_elem = "BOOLEAN" \
            if len(used_synonyms) == 0 \
            else random.choice(used_synonyms)
    # Print query
    print(ctr, "-", f"{num_clauses}-clause query")
    print(declarations)
    print("Select", selected_elem, end=" ")
    for clause in clauses:
       print(clause, end=" ")
    print("") # newline
    print("none")
    print(5000)
    


if __name__ == "__main__":
  # CreateSingleSuchThatQueries()
  if len(sys.argv) < 3:
     raise Exception(f"Intended usage: python3 query_generator.py num_clauses num_queries")
  
  CreateMultiClauseQuery(int(sys.argv[1]), int(sys.argv[2]))
  








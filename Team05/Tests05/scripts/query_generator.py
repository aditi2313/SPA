## Python script for generating random queries


## Generator for such-that clauses
## To generate permutations of clauses
class Generator:  
  def __init__(self, clause, left_params, right_params):
    self.__left_params = left_params
    self.__right_params = right_params
    self.__clause = clause
  def generate(self):
    result = []
    for left in self.__left_params:
      for right in self.__right_params:
        result.append(self.__clause + "(" + left + "," + right + ")")
    return result
  

modify_lefts = ["x", "10", "100", "procedure", "read", "_"]
modify_rights = ["l", "m", "x", "100", "rock", "_"]
uses_lefts = modify_lefts
uses_rights = modify_rights
parent_lefts = ["1", "2", "10", "_", "s", "s2"]
parent_rights = ["2", "3", "4", "_", "s", "s2"]
follows_lefts = parent_lefts
follows_rights = parent_rights

def create_generators():
  generators = [
    Generator("Modifies", modify_lefts, modify_rights),
    Generator("Uses", uses_lefts, uses_rights),
    Generator("Parent", parent_lefts, parent_rights),
    Generator("Follows", follows_lefts, follows_rights)
  ]
  return generators

declarations = "variable v; stmt s; assign a;"

def CreateSingleSuchThatQueries():
  entities = ["s", "v", "r", "random", "none"]
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


    


if __name__ == "__main__":
  CreateSingleSuchThatQueries()
  








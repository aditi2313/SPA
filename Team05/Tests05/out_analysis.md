### Global
#### Maximum
- Current run: 3.334 (↑ 3.334)
- Current query: Uses - variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.215 (↑ 1.215)
- Previous run: 0
----

### Affects
#### Maximum
- Current run: 1.761 (↑ 1.761)
- Current query: assign a; Select a such that Affects(a, 8)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.055 (↑ 1.055)
- Previous run: 0
----

### AffectsT
#### Maximum
- Current run: 2.772 (↑ 2.772)
- Current query: assign a; Select a such that Affects*(a, 10)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.067 (↑ 1.067)
- Previous run: 0
----

### AffectsT_2
#### Maximum
- Current run: 2.344 (↑ 2.344)
- Current query: assign a; Select a such that Affects*(3, a)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.186 (↑ 1.186)
- Previous run: 0
----

### Basic
#### Maximum
- Current run: 1.524 (↑ 1.524)
- Current query: assign a;  Select a pattern a(_, "a + b")
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.079 (↑ 1.079)
- Previous run: 0
----

### Boolean
#### Maximum
- Current run: 1.597 (↑ 1.597)
- Current query: stmt s; Select BOOLEAN such that Uses(s, _)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.17 (↑ 1.17)
- Previous run: 0
----

### Calls
#### Maximum
- Current run: 2.244 (↑ 2.244)
- Current query: procedure p; procedure q; Select p such that Calls(q, p)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.392 (↑ 1.392)
- Previous run: 0
----

### condexpr1
#### Maximum
- Current run: 1.491 (↑ 1.491)
- Current query: stmt s;  Select s
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.491 (↑ 1.491)
- Previous run: 0
----

### Follows
#### Maximum
- Current run: 1.411 (↑ 1.411)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 0.961 (↑ 0.961)
- Previous run: 0
----

### Follows2
#### Maximum
- Current run: 1.67 (↑ 1.67)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.22 (↑ 1.22)
- Previous run: 0
----

### Milestone_1
#### Maximum
- Current run: 1.796 (↑ 1.796)
- Current query: assign a;  Select a pattern a(_, "a + b")
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.422 (↑ 1.422)
- Previous run: 0
----

### Modifies
#### Maximum
- Current run: 1.489 (↑ 1.489)
- Current query: variable v; stmt s; Select v such that Modifies(s, v)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.016 (↑ 1.016)
- Previous run: 0
----

### ModifiesP
#### Maximum
- Current run: 1.361 (↑ 1.361)
- Current query: variable v; Select v such that Modifies("modifies3", v)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.057 (↑ 1.057)
- Previous run: 0
----

### ModifiesP_2
#### Maximum
- Current run: 2.479 (↑ 2.479)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.24 (↑ 1.24)
- Previous run: 0
----

### Multi-clause
#### Maximum
- Current run: 1.64 (↑ 1.64)
- Current query: assign a; Select a such that Modifies (a, "b") and Parent* (1,a) and Next(3,a)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.171 (↑ 1.171)
- Previous run: 0
----

### Next
#### Maximum
- Current run: 1.751 (↑ 1.751)
- Current query: stmt s; Select s such that Next(s, 11)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.266 (↑ 1.266)
- Previous run: 0
----

### Next_2
#### Maximum
- Current run: 1.746 (↑ 1.746)
- Current query: stmt s1, s2, s3; Select s1 such that Next* (s1, s2) and Next*(s2, s3)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.604 (↑ 1.604)
- Previous run: 0
----

### Parent
#### Maximum
- Current run: 1.888 (↑ 1.888)
- Current query: if if; stmt s; Select s such that Parent(s, if)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.187 (↑ 1.187)
- Previous run: 0
----

### Parent_2
#### Maximum
- Current run: 1.449 (↑ 1.449)
- Current query: stmt s; Select s such that Parent(s,2)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 0.991 (↑ 0.991)
- Previous run: 0
----

### Parentt
#### Maximum
- Current run: 1.471 (↑ 1.471)
- Current query: stmt s; while w; Select s such that Parent*(s, w)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.226 (↑ 1.226)
- Previous run: 0
----

### Pattern
#### Maximum
- Current run: 2.803 (↑ 2.803)
- Current query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.605 (↑ 1.605)
- Previous run: 0
----

### PatternIf
#### Maximum
- Current run: 2.25 (↑ 2.25)
- Current query: if ifs; Select ifs pattern ifs(_,_,_)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.765 (↑ 1.765)
- Previous run: 0
----

### PatternWhile
#### Maximum
- Current run: 1.496 (↑ 1.496)
- Current query: while w; Select w pattern w(_,_)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.232 (↑ 1.232)
- Previous run: 0
----

### Tuple_clause
#### Maximum
- Current run: 2.712 (↑ 2.712)
- Current query: variable v1, v2; stmt s; Select<v1, v2, s> such that Modifies(s, v1) and Modifies(s, v2) and Parent(s, 1)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.723 (↑ 1.723)
- Previous run: 0
----

### Uses
#### Maximum
- Current run: 3.334 (↑ 3.334)
- Current query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.445 (↑ 1.445)
- Previous run: 0
----

### UsesP
#### Maximum
- Current run: 1.524 (↑ 1.524)
- Current query: variable v; Select v such that Uses("uses1", v)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.157 (↑ 1.157)
- Previous run: 0
----

### With
#### Maximum
- Current run: 2.512 (↑ 2.512)
- Current query: stmt s; constant c; Select s with s.stmt# = c.value
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.062 (↑ 1.062)
- Previous run: 0
----


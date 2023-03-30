### Global
#### Overall statistics
- Total time 606.888 (previously 324.064)
- 224 queries, (previously 215)

#### Maximum
- Current run: 97.144 (↑ 89.32)
- Current query: 500_deep_calls - procedure p; Select p such that Calls*(p, "p1")
- Previous run: 7.824
- Previous query: Basic - variable v; Select v such that Modifies(2, v)

#### Average
- Current run: 2.709 (↑ 1.202)
- Previous run: 1.507
----

### 500_basic
#### Overall statistics
- Total time 1.548 (previously 0)
- 1 queries, (previously 0)

#### Maximum
- Current run: 1.548 (↑ 1.548)
- Current query: stmt s; Select s such that Follows*(6, s)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.548 (↑ 1.548)
- Previous run: 0
----

### 500_deep_calls
#### Overall statistics
- Total time 174.214 (previously 0)
- 3 queries, (previously 0)

#### Maximum
- Current run: 97.144 (↑ 97.144)
- Current query: procedure p; Select p such that Calls*(p, "p1")
- Previous run: 0
- Previous query: 

#### Average
- Current run: 58.071 (↑ 58.071)
- Previous run: 0
----

### 500_deep_if
#### Overall statistics
- Total time 4.095 (previously 0)
- 1 queries, (previously 0)

#### Maximum
- Current run: 4.095 (↑ 4.095)
- Current query: stmt s; Select s such that Parent*(1, s)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 4.095 (↑ 4.095)
- Previous run: 0
----

### 500_deep_while
#### Overall statistics
- Total time 126.553 (previously 0)
- 2 queries, (previously 0)

#### Maximum
- Current run: 74.124 (↑ 74.124)
- Current query: stmt s; Select s such that Parent*(s, 500)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 63.276 (↑ 63.276)
- Previous run: 0
----

### 500_large_assignment
#### Overall statistics
- Total time 1.515 (previously 0)
- 1 queries, (previously 0)

#### Maximum
- Current run: 1.515 (↑ 1.515)
- Current query: variable v; Select v such that Uses(1, v)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.515 (↑ 1.515)
- Previous run: 0
----

### 500_multiple_proc
#### Overall statistics
- Total time 1.588 (previously 0)
- 1 queries, (previously 0)

#### Maximum
- Current run: 1.588 (↑ 1.588)
- Current query: stmt s; Select s such that Follows(6, s)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.588 (↑ 1.588)
- Previous run: 0
----

### Affects
#### Overall statistics
- Total time 15.777 (previously 16.438)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.714 (↓ -1.301)
- Current query: assign a; Select a such that Affects(a, 22)
- Previous run: 3.015
- Previous query: assign a; Select a such that Affects(a, 8)

#### Average
- Current run: 1.434 (↓ -0.06)
- Previous run: 1.494
----

### AffectsT
#### Overall statistics
- Total time 15.923 (previously 14.697)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.671 (↓ -0.042)
- Current query: assign a; Select a such that Affects*(a, 6)
- Previous run: 1.713
- Previous query: assign a; Select a such that Affects*(a, 10)

#### Average
- Current run: 1.448 (↑ 0.112)
- Previous run: 1.336
----

### AffectsT_2
#### Overall statistics
- Total time 19.494 (previously 21.113)
- 15 queries, (previously 15)

#### Maximum
- Current run: 1.688 (↓ -0.088)
- Current query: assign a; Select a such that Affects*(1, a)
- Previous run: 1.776
- Previous query: assign a; Select a such that Affects*(15, a)

#### Average
- Current run: 1.3 (↓ -0.108)
- Previous run: 1.408
----

### Basic
#### Overall statistics
- Total time 16.645 (previously 31.343)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.541 (↓ -6.283)
- Current query: assign a;  Select a pattern a(_, "a + b")
- Previous run: 7.824
- Previous query: variable v; Select v such that Modifies(2, v)

#### Average
- Current run: 1.387 (↓ -1.225)
- Previous run: 2.612
----

### Boolean
#### Overall statistics
- Total time 14.552 (previously 14.793)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.776 (↑ 0.273)
- Current query: stmt s; Select BOOLEAN such that Follows(s, _)
- Previous run: 1.503
- Previous query: stmt s; Select BOOLEAN such that Follows(s, _)

#### Average
- Current run: 1.323 (↓ -0.022)
- Previous run: 1.345
----

### Calls
#### Overall statistics
- Total time 10.498 (previously 10.74)
- 8 queries, (previously 8)

#### Maximum
- Current run: 1.495 (↑ 0.001)
- Current query: procedure p; procedure q; Select p such that Calls(q, p)
- Previous run: 1.494
- Previous query: procedure p; procedure q; Select p such that Calls(q, p)

#### Average
- Current run: 1.312 (↓ -0.031)
- Previous run: 1.343
----

### condexpr1
#### Overall statistics
- Total time 1.42 (previously 1.575)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.42 (↓ -0.155)
- Current query: stmt s;  Select s
- Previous run: 1.575
- Previous query: stmt s;  Select s

#### Average
- Current run: 1.42 (↓ -0.155)
- Previous run: 1.575
----

### Follows
#### Overall statistics
- Total time 11.776 (previously 13.216)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.534 (↓ -0.038)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.572
- Previous query: stmt s;  Select s such that Follows*(s, 7)

#### Average
- Current run: 1.308 (↓ -0.16)
- Previous run: 1.468
----

### Follows2
#### Overall statistics
- Total time 6.307 (previously 8.219)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.432 (↓ -0.516)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.948
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.261 (↓ -0.383)
- Previous run: 1.644
----

### Milestone_1
#### Overall statistics
- Total time 12.999 (previously 12.434)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.542 (↑ 0.03)
- Current query: stmt s; Select s such that Parent*(s, 8)
- Previous run: 1.512
- Previous query: stmt s; Select s such that Parent(s, 9)

#### Average
- Current run: 1.444 (↑ 0.062)
- Previous run: 1.382
----

### Modifies
#### Overall statistics
- Total time 6.37 (previously 7.646)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.401 (↓ -0.407)
- Current query: variable v; stmt s; Select v such that Modifies(s, v)
- Previous run: 1.808
- Previous query: variable v; stmt s; Select v such that Modifies(s, v)

#### Average
- Current run: 1.274 (↓ -0.255)
- Previous run: 1.529
----

### ModifiesP
#### Overall statistics
- Total time 5.41 (previously 5.54)
- 4 queries, (previously 4)

#### Maximum
- Current run: 1.403 (↓ -0.093)
- Current query: variable v; Select v such that Modifies("modifies3", v)
- Previous run: 1.496
- Previous query: variable v; Select v such that Modifies("modifies3", v)

#### Average
- Current run: 1.353 (↓ -0.032)
- Previous run: 1.385
----

### ModifiesP_2
#### Overall statistics
- Total time 6.798 (previously 6.7)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.514 (↑ 0.006)
- Current query: variable v; Select v such that Modifies(2, v)
- Previous run: 1.508
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 1.36 (↑ 0.02)
- Previous run: 1.34
----

### Multi-clause
#### Overall statistics
- Total time 18.178 (previously 16.77)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.727 (↓ -0.02)
- Current query: assign a; Select a such that Modifies(a, "b") such that Parent* (1,a) pattern a("b", _)
- Previous run: 1.747
- Previous query: assign a; Select a such that Modifies (a, "b") and Parent* (1,a) and Next(3,a)

#### Average
- Current run: 1.515 (↑ 0.118)
- Previous run: 1.397
----

### Next
#### Overall statistics
- Total time 15.36 (previously 14.8)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.524 (↑ 0.015)
- Current query: stmt stmt; Select stmt such that Next*(stmt, 2)
- Previous run: 1.509
- Previous query: stmt stmt; Select stmt such that Next(18, stmt)

#### Average
- Current run: 1.396 (↑ 0.051)
- Previous run: 1.345
----

### Next_2
#### Overall statistics
- Total time 8.198 (previously 8.234)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.523 (↓ -0.008)
- Current query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)
- Previous run: 1.531
- Previous query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)

#### Average
- Current run: 1.366 (↓ -0.006)
- Previous run: 1.372
----

### Parent
#### Overall statistics
- Total time 8.638 (previously 8.622)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.637 (↓ -0.011)
- Current query: if if; stmt s; Select s such that Parent(s, if)
- Previous run: 1.648
- Previous query: if if; stmt s; Select s such that Parent(s, if)

#### Average
- Current run: 1.44 (↑ 0.003)
- Previous run: 1.437
----

### Parent_2
#### Overall statistics
- Total time 14.419 (previously 16.309)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.535 (↓ -0.12)
- Current query: stmt s; Select s such that Parent(3,s)
- Previous run: 1.655
- Previous query: stmt s; Select s such that Parent(s,2)

#### Average
- Current run: 1.311 (↓ -0.172)
- Previous run: 1.483
----

### Parentt
#### Overall statistics
- Total time 4.146 (previously 4.366)
- 3 queries, (previously 3)

#### Maximum
- Current run: 1.582 (↑ 0.009)
- Current query: stmt s; while w; Select s such that Parent*(s, w)
- Previous run: 1.573
- Previous query: stmt s; while w; Select s such that Parent*(s, w)

#### Average
- Current run: 1.382 (↓ -0.073)
- Previous run: 1.455
----

### Pattern
#### Overall statistics
- Total time 9.948 (previously 12.312)
- 7 queries, (previously 7)

#### Maximum
- Current run: 1.793 (↓ -0.701)
- Current query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")
- Previous run: 2.494
- Previous query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")

#### Average
- Current run: 1.421 (↓ -0.338)
- Previous run: 1.759
----

### PatternIf
#### Overall statistics
- Total time 3.02 (previously 2.792)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.633 (↑ 0.189)
- Current query: if ifs; Select ifs pattern ifs(_,_,_)
- Previous run: 1.444
- Previous query: if ifs; Select ifs pattern ifs(_,_,_)

#### Average
- Current run: 1.51 (↑ 0.114)
- Previous run: 1.396
----

### PatternWhile
#### Overall statistics
- Total time 3.126 (previously 3.768)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.786 (↓ -0.299)
- Current query: while w; Select w pattern w(_,_)
- Previous run: 2.085
- Previous query: while w; Select w pattern w(_,_)

#### Average
- Current run: 1.563 (↓ -0.321)
- Previous run: 1.884
----

### Tuple_clause
#### Overall statistics
- Total time 12.685 (previously 15.412)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.517 (↓ -1.242)
- Current query: assign a; variable v; Select <a, v> such that Modifies(a, v)
- Previous run: 2.759
- Previous query: variable v; procedure p, q, r; assign a; Select <p, q, r, v> such that Calls(p, q) and Calls(q, r) pattern a(v, _"x"_)

#### Average
- Current run: 1.409 (↓ -0.303)
- Previous run: 1.712
----

### Uses
#### Overall statistics
- Total time 12.665 (previously 14.213)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.638 (↓ -0.19)
- Current query: stmt s; Select s such that Uses(s, "i")
- Previous run: 1.828
- Previous query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)

#### Average
- Current run: 1.407 (↓ -0.172)
- Previous run: 1.579
----

### UsesP
#### Overall statistics
- Total time 7.913 (previously 8.61)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.503 (↓ -0.005)
- Current query: variable v; Select v such that Uses("uses3", v)
- Previous run: 1.508
- Previous query: variable v; Select v such that Uses("uses2", v)

#### Average
- Current run: 1.319 (↓ -0.116)
- Previous run: 1.435
----

### With
#### Overall statistics
- Total time 35.11 (previously 33.402)
- 25 queries, (previously 25)

#### Maximum
- Current run: 1.712 (↑ 0.062)
- Current query: procedure p; call c; while w; Select p such that Calls ("Second", p) and Parent (w, c) with c.procName = p.procName
- Previous run: 1.65
- Previous query: stmt s; constant c; Select s with s.stmt# = c.value

#### Average
- Current run: 1.404 (↑ 0.068)
- Previous run: 1.336
----


### Global
#### Overall statistics
- Total time 374.04 (previously 324.064)
- 224 queries, (previously 215)

#### Maximum
- Current run: 33.505 (↑ 25.681)
- Current query: 500_deep_calls - procedure p; Select p such that Calls*(p, "p1")
- Previous run: 7.824
- Previous query: Basic - variable v; Select v such that Modifies(2, v)

#### Average
- Current run: 1.67 (↑ 0.163)
- Previous run: 1.507
----

### 500_basic
#### Overall statistics
- Total time 2.048 (previously 0)
- 1 queries, (previously 0)

#### Maximum
- Current run: 2.048 (↑ 2.048)
- Current query: stmt s; Select s such that Follows*(6, s)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 2.048 (↑ 2.048)
- Previous run: 0
----

### 500_deep_calls
#### Overall statistics
- Total time 36.689 (previously 0)
- 3 queries, (previously 0)

#### Maximum
- Current run: 33.505 (↑ 33.505)
- Current query: procedure p; Select p such that Calls*(p, "p1")
- Previous run: 0
- Previous query: 

#### Average
- Current run: 12.23 (↑ 12.23)
- Previous run: 0
----

### 500_deep_if
#### Overall statistics
- Total time 3.013 (previously 0)
- 1 queries, (previously 0)

#### Maximum
- Current run: 3.013 (↑ 3.013)
- Current query: stmt s; Select s such that Parent*(1, s)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 3.013 (↑ 3.013)
- Previous run: 0
----

### 500_deep_while
#### Overall statistics
- Total time 24.979 (previously 0)
- 2 queries, (previously 0)

#### Maximum
- Current run: 23.46 (↑ 23.46)
- Current query: stmt s; Select s such that Parent*(s, 500)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 12.489 (↑ 12.489)
- Previous run: 0
----

### 500_large_assignment
#### Overall statistics
- Total time 1.532 (previously 0)
- 1 queries, (previously 0)

#### Maximum
- Current run: 1.532 (↑ 1.532)
- Current query: variable v; Select v such that Uses(1, v)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.532 (↑ 1.532)
- Previous run: 0
----

### 500_multiple_proc
#### Overall statistics
- Total time 1.713 (previously 0)
- 1 queries, (previously 0)

#### Maximum
- Current run: 1.713 (↑ 1.713)
- Current query: stmt s; Select s such that Follows(6, s)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 1.713 (↑ 1.713)
- Previous run: 0
----

### Affects
#### Overall statistics
- Total time 15.11 (previously 16.438)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.644 (↓ -1.371)
- Current query: assign a; Select a such that Affects(a, 8)
- Previous run: 3.015
- Previous query: assign a; Select a such that Affects(a, 8)

#### Average
- Current run: 1.374 (↓ -0.12)
- Previous run: 1.494
----

### AffectsT
#### Overall statistics
- Total time 16.715 (previously 14.697)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.883 (↑ 0.17)
- Current query: assign a; Select a such that Affects*(a, 30)
- Previous run: 1.713
- Previous query: assign a; Select a such that Affects*(a, 10)

#### Average
- Current run: 1.52 (↑ 0.184)
- Previous run: 1.336
----

### AffectsT_2
#### Overall statistics
- Total time 20.517 (previously 21.113)
- 15 queries, (previously 15)

#### Maximum
- Current run: 1.562 (↓ -0.214)
- Current query: assign a; Select a such that Affects*(1, a)
- Previous run: 1.776
- Previous query: assign a; Select a such that Affects*(15, a)

#### Average
- Current run: 1.368 (↓ -0.04)
- Previous run: 1.408
----

### Basic
#### Overall statistics
- Total time 17.554 (previously 31.343)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.72 (↓ -6.104)
- Current query: while while; if f; Select while such that Parent(while, f)
- Previous run: 7.824
- Previous query: variable v; Select v such that Modifies(2, v)

#### Average
- Current run: 1.463 (↓ -1.149)
- Previous run: 2.612
----

### Boolean
#### Overall statistics
- Total time 15.731 (previously 14.793)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.645 (↑ 0.142)
- Current query: stmt s; variable v; Select BOOLEAN such that Modifies(s, v)
- Previous run: 1.503
- Previous query: stmt s; Select BOOLEAN such that Follows(s, _)

#### Average
- Current run: 1.43 (↑ 0.085)
- Previous run: 1.345
----

### Calls
#### Overall statistics
- Total time 11.112 (previously 10.74)
- 8 queries, (previously 8)

#### Maximum
- Current run: 1.516 (↑ 0.022)
- Current query: procedure p; procedure q; Select p such that Calls(q, p)
- Previous run: 1.494
- Previous query: procedure p; procedure q; Select p such that Calls(q, p)

#### Average
- Current run: 1.389 (↑ 0.046)
- Previous run: 1.343
----

### condexpr1
#### Overall statistics
- Total time 1.315 (previously 1.575)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.315 (↓ -0.26)
- Current query: stmt s;  Select s
- Previous run: 1.575
- Previous query: stmt s;  Select s

#### Average
- Current run: 1.315 (↓ -0.26)
- Previous run: 1.575
----

### Follows
#### Overall statistics
- Total time 12.725 (previously 13.216)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.697 (↑ 0.125)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.572
- Previous query: stmt s;  Select s such that Follows*(s, 7)

#### Average
- Current run: 1.414 (↓ -0.054)
- Previous run: 1.468
----

### Follows2
#### Overall statistics
- Total time 7.47 (previously 8.219)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.847 (↓ -0.101)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.948
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.494 (↓ -0.15)
- Previous run: 1.644
----

### Milestone_1
#### Overall statistics
- Total time 12.571 (previously 12.434)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.577 (↑ 0.065)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.512
- Previous query: stmt s; Select s such that Parent(s, 9)

#### Average
- Current run: 1.397 (↑ 0.015)
- Previous run: 1.382
----

### Modifies
#### Overall statistics
- Total time 6.81 (previously 7.646)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.587 (↓ -0.221)
- Current query: variable v; stmt s; Select v such that Modifies(s, v)
- Previous run: 1.808
- Previous query: variable v; stmt s; Select v such that Modifies(s, v)

#### Average
- Current run: 1.362 (↓ -0.167)
- Previous run: 1.529
----

### ModifiesP
#### Overall statistics
- Total time 6.057 (previously 5.54)
- 4 queries, (previously 4)

#### Maximum
- Current run: 1.699 (↑ 0.203)
- Current query: variable v; Select v such that Modifies("modifies3", v)
- Previous run: 1.496
- Previous query: variable v; Select v such that Modifies("modifies3", v)

#### Average
- Current run: 1.514 (↑ 0.129)
- Previous run: 1.385
----

### ModifiesP_2
#### Overall statistics
- Total time 7.24 (previously 6.7)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.463 (↓ -0.045)
- Current query: stmt s; Select s such that Modifies(s, "v3")
- Previous run: 1.508
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 1.448 (↑ 0.108)
- Previous run: 1.34
----

### Multi-clause
#### Overall statistics
- Total time 16.353 (previously 16.77)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.561 (↓ -0.186)
- Current query: assign a; Select a such that Modifies(a, "b") such that Parent* (1,a) pattern a("b", _)
- Previous run: 1.747
- Previous query: assign a; Select a such that Modifies (a, "b") and Parent* (1,a) and Next(3,a)

#### Average
- Current run: 1.363 (↓ -0.034)
- Previous run: 1.397
----

### Next
#### Overall statistics
- Total time 16.148 (previously 14.8)
- 11 queries, (previously 11)

#### Maximum
- Current run: 2.032 (↑ 0.523)
- Current query: stmt s; Select s such that Next(2, s)
- Previous run: 1.509
- Previous query: stmt stmt; Select stmt such that Next(18, stmt)

#### Average
- Current run: 1.468 (↑ 0.123)
- Previous run: 1.345
----

### Next_2
#### Overall statistics
- Total time 9.781 (previously 8.234)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.832 (↑ 0.301)
- Current query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)
- Previous run: 1.531
- Previous query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)

#### Average
- Current run: 1.63 (↑ 0.258)
- Previous run: 1.372
----

### Parent
#### Overall statistics
- Total time 7.979 (previously 8.622)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.513 (↓ -0.135)
- Current query: if if; stmt s; Select s such that Parent(s, if)
- Previous run: 1.648
- Previous query: if if; stmt s; Select s such that Parent(s, if)

#### Average
- Current run: 1.33 (↓ -0.107)
- Previous run: 1.437
----

### Parent_2
#### Overall statistics
- Total time 15.023 (previously 16.309)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.53 (↓ -0.125)
- Current query: stmt s; Select s such that Parent(s,2)
- Previous run: 1.655
- Previous query: stmt s; Select s such that Parent(s,2)

#### Average
- Current run: 1.366 (↓ -0.117)
- Previous run: 1.483
----

### Parentt
#### Overall statistics
- Total time 4.377 (previously 4.366)
- 3 queries, (previously 3)

#### Maximum
- Current run: 1.583 (↑ 0.01)
- Current query: stmt s; while w; Select s such that Parent*(s, w)
- Previous run: 1.573
- Previous query: stmt s; while w; Select s such that Parent*(s, w)

#### Average
- Current run: 1.459 (↑ 0.004)
- Previous run: 1.455
----

### Pattern
#### Overall statistics
- Total time 10.227 (previously 12.312)
- 7 queries, (previously 7)

#### Maximum
- Current run: 1.684 (↓ -0.81)
- Current query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")
- Previous run: 2.494
- Previous query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")

#### Average
- Current run: 1.461 (↓ -0.298)
- Previous run: 1.759
----

### PatternIf
#### Overall statistics
- Total time 2.812 (previously 2.792)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.483 (↑ 0.039)
- Current query: if ifs; Select ifs pattern ifs(_,_,_)
- Previous run: 1.444
- Previous query: if ifs; Select ifs pattern ifs(_,_,_)

#### Average
- Current run: 1.406 (↑ 0.01)
- Previous run: 1.396
----

### PatternWhile
#### Overall statistics
- Total time 2.928 (previously 3.768)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.573 (↓ -0.512)
- Current query: while w; Select w pattern w(_,_)
- Previous run: 2.085
- Previous query: while w; Select w pattern w(_,_)

#### Average
- Current run: 1.464 (↓ -0.42)
- Previous run: 1.884
----

### Tuple_clause
#### Overall statistics
- Total time 13.04 (previously 15.412)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.566 (↓ -1.193)
- Current query: assign a; variable v; Select <a, v> such that Modifies(a, v)
- Previous run: 2.759
- Previous query: variable v; procedure p, q, r; assign a; Select <p, q, r, v> such that Calls(p, q) and Calls(q, r) pattern a(v, _"x"_)

#### Average
- Current run: 1.449 (↓ -0.263)
- Previous run: 1.712
----

### Uses
#### Overall statistics
- Total time 12.244 (previously 14.213)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.563 (↓ -0.265)
- Current query: stmt s; Select s such that Uses(s, "i")
- Previous run: 1.828
- Previous query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)

#### Average
- Current run: 1.36 (↓ -0.219)
- Previous run: 1.579
----

### UsesP
#### Overall statistics
- Total time 8.2 (previously 8.61)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.543 (↑ 0.035)
- Current query: variable v; Select v such that Uses("uses3", v)
- Previous run: 1.508
- Previous query: variable v; Select v such that Uses("uses2", v)

#### Average
- Current run: 1.367 (↓ -0.068)
- Previous run: 1.435
----

### With
#### Overall statistics
- Total time 34.027 (previously 33.402)
- 25 queries, (previously 25)

#### Maximum
- Current run: 1.702 (↑ 0.052)
- Current query: procedure p; Select p with p.procName = "First"
- Previous run: 1.65
- Previous query: stmt s; constant c; Select s with s.stmt# = c.value

#### Average
- Current run: 1.361 (↑ 0.025)
- Previous run: 1.336
----


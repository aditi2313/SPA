### Global
#### Overall statistics
- Total time 536.396 (previously 459.655)
- 313 queries, (previously 313)

#### Maximum
- Current run: 4.185 (↓ -0.167)
- Current query: 500_deep_if - stmt s; Select s such that Parent*(1, s)
- Previous run: 4.352
- Previous query: 500_deep_if - stmt s; Select s such that Parent*(1, s)

#### Average
- Current run: 1.714 (↑ 0.245)
- Previous run: 1.469

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_basic
#### Overall statistics
- Total time 1.959 (previously 1.641)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.959 (↑ 0.318)
- Current query: stmt s; Select s such that Follows*(6, s)
- Previous run: 1.641
- Previous query: stmt s; Select s such that Follows*(6, s)

#### Average
- Current run: 1.959 (↑ 0.318)
- Previous run: 1.641

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_deep_calls
#### Overall statistics
- Total time 7.943 (previously 9.414)
- 3 queries, (previously 3)

#### Maximum
- Current run: 4.177 (↑ 0.113)
- Current query: procedure p; Select p such that Calls*(p, "p1")
- Previous run: 4.064
- Previous query: procedure p; Select p such that Calls(p, "p1")

#### Average
- Current run: 2.648 (↓ -0.49)
- Previous run: 3.138

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_deep_if
#### Overall statistics
- Total time 4.185 (previously 4.352)
- 1 queries, (previously 1)

#### Maximum
- Current run: 4.185 (↓ -0.167)
- Current query: stmt s; Select s such that Parent*(1, s)
- Previous run: 4.352
- Previous query: stmt s; Select s such that Parent*(1, s)

#### Average
- Current run: 4.185 (↓ -0.167)
- Previous run: 4.352

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_deep_while
#### Overall statistics
- Total time 6.252 (previously 5.189)
- 2 queries, (previously 2)

#### Maximum
- Current run: 4.142 (↑ 0.678)
- Current query: stmt s; Select s such that Parent*(s, 500)
- Previous run: 3.464
- Previous query: stmt s; Select s such that Parent*(s, 500)

#### Average
- Current run: 3.126 <mark style='background-color: lightpink'>(↑ 0.531)</mark>
- Previous run: 2.595

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_follows
#### Overall statistics
- Total time 3.508 (previously 3.183)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.888 (↑ 0.157)
- Current query: stmt s; Select s such that Follows(s, 255)
- Previous run: 1.731
- Previous query: stmt s; Select s such that Follows(s, 255)

#### Average
- Current run: 1.754 (↑ 0.163)
- Previous run: 1.591

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_large_assignment
#### Overall statistics
- Total time 1.923 (previously 1.556)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.923 (↑ 0.367)
- Current query: variable v; Select v such that Uses(1, v)
- Previous run: 1.556
- Previous query: variable v; Select v such that Uses(1, v)

#### Average
- Current run: 1.923 (↑ 0.367)
- Previous run: 1.556

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_multiple_proc
#### Overall statistics
- Total time 1.968 (previously 2.81)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.968 (↓ -0.842)
- Current query: stmt s; Select s such that Follows(6, s)
- Previous run: 2.81
- Previous query: stmt s; Select s such that Follows(6, s)

#### Average
- Current run: 1.968 <mark style='background-color: lightgreen'>(↓ -0.842)</mark>
- Previous run: 2.81

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Affects
#### Overall statistics
- Total time 15.531 (previously 14.796)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.542 (↓ -0.037)
- Current query: assign a; Select a such that Affects(a, 23)
- Previous run: 1.579
- Previous query: assign a; Select a such that Affects(a, 8)

#### Average
- Current run: 1.412 (↑ 0.067)
- Previous run: 1.345

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### AffectsT
#### Overall statistics
- Total time 19.137 (previously 16.32)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.877 (↑ 0.235)
- Current query: assign a; Select a such that Affects*(a, 10)
- Previous run: 1.642
- Previous query: assign a; Select a such that Affects*(a, 28)

#### Average
- Current run: 1.74 (↑ 0.256)
- Previous run: 1.484

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### AffectsT_2
#### Overall statistics
- Total time 23.844 (previously 19.917)
- 15 queries, (previously 15)

#### Maximum
- Current run: 1.838 (↑ 0.259)
- Current query: assign a; Select a such that Affects*(1, a)
- Previous run: 1.579
- Previous query: assign a; Select a such that Affects*(1, a)

#### Average
- Current run: 1.59 (↑ 0.262)
- Previous run: 1.328

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Basic
#### Overall statistics
- Total time 18.985 (previously 15.769)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.812 (↑ 0.298)
- Current query: assign a;  Select a pattern a(_, "a + b")
- Previous run: 1.514
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 1.582 (↑ 0.268)
- Previous run: 1.314

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Boolean
#### Overall statistics
- Total time 18.293 (previously 14.874)
- 11 queries, (previously 11)

#### Maximum
- Current run: 2.095 (↑ 0.609)
- Current query: stmt s; variable v; Select BOOLEAN such that Modifies(s, v)
- Previous run: 1.486
- Previous query: stmt s; Select BOOLEAN such that Follows(s, _)

#### Average
- Current run: 1.663 (↑ 0.311)
- Previous run: 1.352

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Calls
#### Overall statistics
- Total time 12.644 (previously 10.685)
- 8 queries, (previously 8)

#### Maximum
- Current run: 1.705 (↑ 0.103)
- Current query: procedure p; procedure q; Select p such that Calls(q, p)
- Previous run: 1.602
- Previous query: procedure p; procedure q; Select p such that Calls(q, p)

#### Average
- Current run: 1.581 (↑ 0.245)
- Previous run: 1.336

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### condexpr1
#### Overall statistics
- Total time 1.561 (previously 1.306)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.561 (↑ 0.255)
- Current query: stmt s;  Select s
- Previous run: 1.306
- Previous query: stmt s;  Select s

#### Average
- Current run: 1.561 (↑ 0.255)
- Previous run: 1.306

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Follows
#### Overall statistics
- Total time 13.372 (previously 11.689)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.692 (↑ 0.201)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.491
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.486 (↑ 0.187)
- Previous run: 1.299

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Follows2
#### Overall statistics
- Total time 7.85 (previously 6.791)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.628 (↑ 0.061)
- Current query: stmt s;  Select s such that Follows*(s,2)
- Previous run: 1.567
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.57 (↑ 0.212)
- Previous run: 1.358

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Milestone_1
#### Overall statistics
- Total time 13.532 (previously 12.215)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.651 (↑ 0.212)
- Current query: assign a;  Select a pattern a(_, "a - b")
- Previous run: 1.439
- Previous query: variable v; Select v such that Modifies(2, v)

#### Average
- Current run: 1.504 (↑ 0.147)
- Previous run: 1.357

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Modifies
#### Overall statistics
- Total time 7.774 (previously 6.55)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.73 (↑ 0.313)
- Current query: variable v; stmt s; Select v such that Modifies(s, v)
- Previous run: 1.417
- Previous query: variable v; stmt s; Select v such that Modifies(s, v)

#### Average
- Current run: 1.555 (↑ 0.245)
- Previous run: 1.31

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### ModifiesP
#### Overall statistics
- Total time 6.503 (previously 5.59)
- 4 queries, (previously 4)

#### Maximum
- Current run: 1.751 (↑ 0.24)
- Current query: variable v; Select v such that Modifies("modifies3", v)
- Previous run: 1.511
- Previous query: variable v; Select v such that Modifies("modifies3", v)

#### Average
- Current run: 1.626 (↑ 0.229)
- Previous run: 1.397

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### ModifiesP_2
#### Overall statistics
- Total time 7.976 (previously 6.613)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.925 (↑ 0.466)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.459
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 1.595 (↑ 0.272)
- Previous run: 1.323

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi-clause
#### Overall statistics
- Total time 17.973 (previously 15.704)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.727 (↑ 0.255)
- Current query: assign a; Select a such that Modifies(a, "b") such that Parent* (1,a) pattern a("b", _)
- Previous run: 1.472
- Previous query: assign a; Select a such that Modifies(a, "b") such that Parent* (1,a) pattern a("b", _)

#### Average
- Current run: 1.498 (↑ 0.189)
- Previous run: 1.309

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_10
#### Overall statistics
- Total time 2.55 (previously 2.017)
- 1 queries, (previously 1)

#### Maximum
- Current run: 2.55 (↑ 0.533)
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Affects*(_, _) pattern a(_, "y") such that Calls*(_, "pain") with ifs.stmt# = call.stmt# with r.varName = pn.varName such that Modifies("pain", "b") pattern ifs("c", _, _) such that Uses("third", _) such that Next(_, 4) such that Next*(_, _)
- Previous run: 2.017
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Affects*(_, _) pattern a(_, "y") such that Calls*(_, "pain") with ifs.stmt# = call.stmt# with r.varName = pn.varName such that Modifies("pain", "b") pattern ifs("c", _, _) such that Uses("third", _) such that Next(_, 4) such that Next*(_, _)

#### Average
- Current run: 2.55 <mark style='background-color: lightpink'>(↑ 0.533)</mark>
- Previous run: 2.017

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_7
#### Overall statistics
- Total time 114.504 (previously 96.696)
- 57 queries, (previously 57)

#### Maximum
- Current run: 3.951 (↑ 0.441)
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select pn pattern a(v, _) such that Parent*(_, _) such that Follows*(_, 18) pattern w(_, _) such that Parent(_, pn) with r.varName = r.varName with s.stmt# = a.stmt#
- Previous run: 3.51
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select pn pattern a(v, _) such that Parent*(_, _) such that Follows*(_, 18) pattern w(_, _) such that Parent(_, pn) with r.varName = r.varName with s.stmt# = a.stmt#

#### Average
- Current run: 2.009 (↑ 0.313)
- Previous run: 1.696

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_8
#### Overall statistics
- Total time 42.774 (previously 35.236)
- 24 queries, (previously 24)

#### Maximum
- Current run: 2.21 (↑ 0.39)
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN with ifs.stmt# = s.stmt# such that Calls*(_, _) such that Next(2, _) such that Parent*(7, 18) pattern ifs(_, _, _) such that Parent(17, 2) such that Calls("pain", _) such that Affects*(_, _)
- Previous run: 1.82
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN with ifs.stmt# = s.stmt# such that Calls*(_, _) such that Next(2, _) such that Parent*(7, 18) pattern ifs(_, _, _) such that Parent(17, 2) such that Calls("pain", _) such that Affects*(_, _)

#### Average
- Current run: 1.782 (↑ 0.314)
- Previous run: 1.468

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_9
#### Overall statistics
- Total time 9.551 (previously 8.557)
- 5 queries, (previously 5)

#### Maximum
- Current run: 2.228 (↑ 0.321)
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Next(_, _) pattern a(_, _"y"_) such that Calls(_, "third") such that Follows(17, 6) such that Next*(12, _) such that Parent*(1, 8) with r.varName = r.varName pattern ifs("d", _, _) such that Follows*(_, _)
- Previous run: 1.907
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Next(_, _) pattern a(_, _"y"_) such that Calls(_, "third") such that Follows(17, 6) such that Next*(12, _) such that Parent*(1, 8) with r.varName = r.varName pattern ifs("d", _, _) such that Follows*(_, _)

#### Average
- Current run: 1.91 (↑ 0.199)
- Previous run: 1.711

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Next
#### Overall statistics
- Total time 15.83 (previously 14.547)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.603 (↑ 0.133)
- Current query: stmt s; Select s such that Next(4, s)
- Previous run: 1.47
- Previous query: stmt s; Select s such that Next(4, s)

#### Average
- Current run: 1.439 (↑ 0.117)
- Previous run: 1.322

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Next_2
#### Overall statistics
- Total time 9.695 (previously 8.524)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.719 (↑ 0.25)
- Current query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)
- Previous run: 1.469
- Previous query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)

#### Average
- Current run: 1.616 (↑ 0.195)
- Previous run: 1.421

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Parent
#### Overall statistics
- Total time 9.348 (previously 7.968)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.726 (↑ 0.272)
- Current query: if if; stmt s; Select s such that Parent(s, if)
- Previous run: 1.454
- Previous query: if if; stmt s; Select s such that Parent(s, if)

#### Average
- Current run: 1.558 (↑ 0.23)
- Previous run: 1.328

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Parent_2
#### Overall statistics
- Total time 16.855 (previously 14.332)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.739 (↑ 0.281)
- Current query: stmt s; Select s such that Parent(3,_)
- Previous run: 1.458
- Previous query: stmt s; Select s such that Parent(s,2)

#### Average
- Current run: 1.532 (↑ 0.229)
- Previous run: 1.303

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Parentt
#### Overall statistics
- Total time 4.645 (previously 3.921)
- 3 queries, (previously 3)

#### Maximum
- Current run: 1.687 (↑ 0.244)
- Current query: stmt s; while w; Select s such that Parent*(s, w)
- Previous run: 1.443
- Previous query: stmt s; while w; Select s such that Parent*(s, w)

#### Average
- Current run: 1.548 (↑ 0.241)
- Previous run: 1.307

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Pattern
#### Overall statistics
- Total time 11.649 (previously 9.65)
- 7 queries, (previously 7)

#### Maximum
- Current run: 1.918 (↑ 0.264)
- Current query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")
- Previous run: 1.654
- Previous query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")

#### Average
- Current run: 1.664 (↑ 0.285)
- Previous run: 1.379

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### PatternIf
#### Overall statistics
- Total time 3.207 (previously 2.78)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.713 (↑ 0.278)
- Current query: if ifs; Select ifs pattern ifs(_,_,_)
- Previous run: 1.435
- Previous query: if ifs; Select ifs pattern ifs(_,_,_)

#### Average
- Current run: 1.603 (↑ 0.213)
- Previous run: 1.39

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### PatternWhile
#### Overall statistics
- Total time 3.672 (previously 2.84)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.935 (↑ 0.372)
- Current query: while w; Select w pattern w(_,_)
- Previous run: 1.563
- Previous query: while w; Select w pattern w(_,_)

#### Average
- Current run: 1.836 (↑ 0.416)
- Previous run: 1.42

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Tuple_clause
#### Overall statistics
- Total time 14.978 (previously 12.421)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.804 (↑ 0.283)
- Current query: assign a; print pn; procedure p, q; variable v; Select<p, pn> such that Calls(p, q) and Uses (pn, v) 
- Previous run: 1.521
- Previous query: assign a; variable v; Select <a, v> such that Modifies(a, v)

#### Average
- Current run: 1.664 (↑ 0.284)
- Previous run: 1.38

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Uses
#### Overall statistics
- Total time 14.672 (previously 11.988)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.936 (↑ 0.378)
- Current query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)
- Previous run: 1.558
- Previous query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)

#### Average
- Current run: 1.63 (↑ 0.298)
- Previous run: 1.332

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### UsesP
#### Overall statistics
- Total time 9.292 (previously 8.234)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.766 (↑ 0.205)
- Current query: variable v; Select v such that Uses("uses3", v)
- Previous run: 1.561
- Previous query: variable v; Select v such that Uses("uses3", v)

#### Average
- Current run: 1.549 (↑ 0.177)
- Previous run: 1.372

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### With
#### Overall statistics
- Total time 40.461 (previously 32.98)
- 25 queries, (previously 25)

#### Maximum
- Current run: 1.917 (↑ 0.373)
- Current query: procedure p; call c; while w; Select p such that Calls ("Second", p) and Parent (w, c) with c.procName = p.procName
- Previous run: 1.544
- Previous query: procedure p; call c; while w; Select p such that Calls ("Second", p) and Parent (w, c) with c.procName = p.procName

#### Average
- Current run: 1.618 (↑ 0.299)
- Previous run: 1.319

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----


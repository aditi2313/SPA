### Global
#### Overall statistics
- Total time 459.655 (previously 692.852)
- 313 queries, (previously 313)

#### Maximum
- Current run: 4.352 <mark style='background-color: lightgreen'>(↓ -129.046)</mark>
- Current query: 500_deep_if - stmt s; Select s such that Parent*(1, s)
- Previous run: 133.398
- Previous query: Multi_clause_7 - stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select pn such that Calls(_, _) such that Calls*(_, p) pattern a(_, _) such that Parent*(_, s) with v.varName = pn.varName such that Follows(_, pn) pattern w(v, _)

#### Average
- Current run: 1.469 <mark style='background-color: lightgreen'>(↓ -0.745)</mark>
- Previous run: 2.214

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_basic
#### Overall statistics
- Total time 1.641 (previously 2.582)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.641 (↓ -0.941)
- Current query: stmt s; Select s such that Follows*(6, s)
- Previous run: 2.582
- Previous query: stmt s; Select s such that Follows*(6, s)

#### Average
- Current run: 1.641 <mark style='background-color: lightgreen'>(↓ -0.941)</mark>
- Previous run: 2.582

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_deep_calls
#### Overall statistics
- Total time 9.414 (previously 6.805)
- 3 queries, (previously 3)

#### Maximum
- Current run: 4.064 (↑ 0.764)
- Current query: procedure p; Select p such that Calls(p, "p1")
- Previous run: 3.3
- Previous query: procedure p; Select p such that Calls*(p, "p1")

#### Average
- Current run: 3.138 <mark style='background-color: lightpink'>(↑ 0.87)</mark>
- Previous run: 2.268

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_deep_if
#### Overall statistics
- Total time 4.352 (previously 3.266)
- 1 queries, (previously 1)

#### Maximum
- Current run: 4.352 <mark style='background-color: lightpink'>(↑ 1.086)</mark>
- Current query: stmt s; Select s such that Parent*(1, s)
- Previous run: 3.266
- Previous query: stmt s; Select s such that Parent*(1, s)

#### Average
- Current run: 4.352 <mark style='background-color: lightpink'>(↑ 1.086)</mark>
- Previous run: 3.266

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_deep_while
#### Overall statistics
- Total time 5.189 (previously 5.047)
- 2 queries, (previously 2)

#### Maximum
- Current run: 3.464 (↑ 0.133)
- Current query: stmt s; Select s such that Parent*(s, 500)
- Previous run: 3.331
- Previous query: stmt s; Select s such that Parent*(s, 500)

#### Average
- Current run: 2.595 (↑ 0.072)
- Previous run: 2.523

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_follows
#### Overall statistics
- Total time 3.183 (previously 3.367)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.731 (↓ -0.082)
- Current query: stmt s; Select s such that Follows(s, 255)
- Previous run: 1.813
- Previous query: stmt s; Select s such that Follows(s, 255)

#### Average
- Current run: 1.591 (↓ -0.092)
- Previous run: 1.683

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_large_assignment
#### Overall statistics
- Total time 1.556 (previously 2.177)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.556 (↓ -0.621)
- Current query: variable v; Select v such that Uses(1, v)
- Previous run: 2.177
- Previous query: variable v; Select v such that Uses(1, v)

#### Average
- Current run: 1.556 <mark style='background-color: lightgreen'>(↓ -0.621)</mark>
- Previous run: 2.177

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_multiple_proc
#### Overall statistics
- Total time 2.81 (previously 1.786)
- 1 queries, (previously 1)

#### Maximum
- Current run: 2.81 <mark style='background-color: lightpink'>(↑ 1.024)</mark>
- Current query: stmt s; Select s such that Follows(6, s)
- Previous run: 1.786
- Previous query: stmt s; Select s such that Follows(6, s)

#### Average
- Current run: 2.81 <mark style='background-color: lightpink'>(↑ 1.024)</mark>
- Previous run: 1.786

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Affects
#### Overall statistics
- Total time 14.796 (previously 16.845)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.579 (↓ -0.276)
- Current query: assign a; Select a such that Affects(a, 8)
- Previous run: 1.855
- Previous query: assign a; Select a such that Affects(a, 8)

#### Average
- Current run: 1.345 (↓ -0.186)
- Previous run: 1.531

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### AffectsT
#### Overall statistics
- Total time 16.32 (previously 17.808)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.642 (↓ -0.171)
- Current query: assign a; Select a such that Affects*(a, 28)
- Previous run: 1.813
- Previous query: assign a; Select a such that Affects*(a, 10)

#### Average
- Current run: 1.484 (↓ -0.135)
- Previous run: 1.619

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### AffectsT_2
#### Overall statistics
- Total time 19.917 (previously 23.139)
- 15 queries, (previously 15)

#### Maximum
- Current run: 1.579 (↓ -0.554)
- Current query: assign a; Select a such that Affects*(1, a)
- Previous run: 2.133
- Previous query: assign a; Select a such that Affects*(2, a)

#### Average
- Current run: 1.328 (↓ -0.215)
- Previous run: 1.543

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Basic
#### Overall statistics
- Total time 15.769 (previously 18.753)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.514 (↓ -0.249)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.763
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 1.314 (↓ -0.249)
- Previous run: 1.563

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Boolean
#### Overall statistics
- Total time 14.874 (previously 16.363)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.486 (↓ -0.072)
- Current query: stmt s; Select BOOLEAN such that Follows(s, _)
- Previous run: 1.558
- Previous query: stmt s; Select BOOLEAN such that Follows(s, _)

#### Average
- Current run: 1.352 (↓ -0.136)
- Previous run: 1.488

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Calls
#### Overall statistics
- Total time 10.685 (previously 12.079)
- 8 queries, (previously 8)

#### Maximum
- Current run: 1.602 (↑ 0.002)
- Current query: procedure p; procedure q; Select p such that Calls(q, p)
- Previous run: 1.6
- Previous query: procedure p; procedure q; Select p such that Calls(q, p)

#### Average
- Current run: 1.336 (↓ -0.174)
- Previous run: 1.51

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### condexpr1
#### Overall statistics
- Total time 1.306 (previously 1.508)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.306 (↓ -0.202)
- Current query: stmt s;  Select s
- Previous run: 1.508
- Previous query: stmt s;  Select s

#### Average
- Current run: 1.306 (↓ -0.202)
- Previous run: 1.508

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Follows
#### Overall statistics
- Total time 11.689 (previously 13.866)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.491 (↓ -0.268)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.759
- Previous query: stmt s;  Select s such that Follows*(3,4)

#### Average
- Current run: 1.299 (↓ -0.242)
- Previous run: 1.541

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Follows2
#### Overall statistics
- Total time 6.791 (previously 7.24)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.567 (↓ -0.027)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.594
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.358 (↓ -0.09)
- Previous run: 1.448

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Milestone_1
#### Overall statistics
- Total time 12.215 (previously 13.378)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.439 (↓ -0.162)
- Current query: variable v; Select v such that Modifies(2, v)
- Previous run: 1.601
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 1.357 (↓ -0.129)
- Previous run: 1.486

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Modifies
#### Overall statistics
- Total time 6.55 (previously 7.499)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.417 (↓ -0.29)
- Current query: variable v; stmt s; Select v such that Modifies(s, v)
- Previous run: 1.707
- Previous query: variable v; stmt s; Select v such that Modifies(s, v)

#### Average
- Current run: 1.31 (↓ -0.19)
- Previous run: 1.5

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### ModifiesP
#### Overall statistics
- Total time 5.59 (previously 6.191)
- 4 queries, (previously 4)

#### Maximum
- Current run: 1.511 (↓ -0.132)
- Current query: variable v; Select v such that Modifies("modifies3", v)
- Previous run: 1.643
- Previous query: variable v; Select v such that Modifies("modifies3", v)

#### Average
- Current run: 1.397 (↓ -0.151)
- Previous run: 1.548

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### ModifiesP_2
#### Overall statistics
- Total time 6.613 (previously 7.356)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.459 (↓ -0.088)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.547
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 1.323 (↓ -0.148)
- Previous run: 1.471

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi-clause
#### Overall statistics
- Total time 15.704 (previously 18.038)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.472 (↓ -0.2)
- Current query: assign a; Select a such that Modifies(a, "b") such that Parent* (1,a) pattern a("b", _)
- Previous run: 1.672
- Previous query: assign a; Select a such that Modifies (a, "b") and Parent* (1,a) and Next(3,a)

#### Average
- Current run: 1.309 (↓ -0.194)
- Previous run: 1.503

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_10
#### Overall statistics
- Total time 2.017 (previously 2.395)
- 1 queries, (previously 1)

#### Maximum
- Current run: 2.017 (↓ -0.378)
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Affects*(_, _) pattern a(_, "y") such that Calls*(_, "pain") with ifs.stmt# = call.stmt# with r.varName = pn.varName such that Modifies("pain", "b") pattern ifs("c", _, _) such that Uses("third", _) such that Next(_, 4) such that Next*(_, _)
- Previous run: 2.395
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Affects*(_, _) pattern a(_, "y") such that Calls*(_, "pain") with ifs.stmt# = call.stmt# with r.varName = pn.varName such that Modifies("pain", "b") pattern ifs("c", _, _) such that Uses("third", _) such that Next(_, 4) such that Next*(_, _)

#### Average
- Current run: 2.017 (↓ -0.378)
- Previous run: 2.395

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_7
#### Overall statistics
- Total time 96.696 (previously 284.458)
- 57 queries, (previously 57)

#### Maximum
- Current run: 3.51 <mark style='background-color: lightgreen'>(↓ -129.888)</mark>
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select pn pattern a(v, _) such that Parent*(_, _) such that Follows*(_, 18) pattern w(_, _) such that Parent(_, pn) with r.varName = r.varName with s.stmt# = a.stmt#
- Previous run: 133.398
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select pn such that Calls(_, _) such that Calls*(_, p) pattern a(_, _) such that Parent*(_, s) with v.varName = pn.varName such that Follows(_, pn) pattern w(v, _)

#### Average
- Current run: 1.696 <mark style='background-color: lightgreen'>(↓ -3.294)</mark>
- Previous run: 4.99

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_8
#### Overall statistics
- Total time 35.236 (previously 40.9)
- 24 queries, (previously 24)

#### Maximum
- Current run: 1.82 (↓ -0.406)
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN with ifs.stmt# = s.stmt# such that Calls*(_, _) such that Next(2, _) such that Parent*(7, 18) pattern ifs(_, _, _) such that Parent(17, 2) such that Calls("pain", _) such that Affects*(_, _)
- Previous run: 2.226
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN pattern ifs("ganesh", _, _) such that Calls*(_, _) with v.varName = p.procName such that Follows*(_, 5) such that Affects(_, _) such that Follows(_, _) pattern a("kmn", _"c"_) such that Next*(5, 16)

#### Average
- Current run: 1.468 (↓ -0.236)
- Previous run: 1.704

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_9
#### Overall statistics
- Total time 8.557 (previously 10.308)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.907 (↓ -0.956)
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Next(_, _) pattern a(_, _"y"_) such that Calls(_, "third") such that Follows(17, 6) such that Next*(12, _) such that Parent*(1, 8) with r.varName = r.varName pattern ifs("d", _, _) such that Follows*(_, _)
- Previous run: 2.863
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Calls*(_, _) pattern ifs(_, _, _) with v.varName = r.varName such that Next*(20, _) pattern w(_, _) such that Uses(1, _) such that Affects*(21, _) such that Calls(_, _) such that Follows(17, 17)

#### Average
- Current run: 1.711 (↓ -0.351)
- Previous run: 2.062

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Next
#### Overall statistics
- Total time 14.547 (previously 16.057)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.47 (↓ -0.164)
- Current query: stmt s; Select s such that Next(4, s)
- Previous run: 1.634
- Previous query: stmt s; Select s such that Next(4, s)

#### Average
- Current run: 1.322 (↓ -0.138)
- Previous run: 1.46

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Next_2
#### Overall statistics
- Total time 8.524 (previously 9.625)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.469 (↓ -0.341)
- Current query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)
- Previous run: 1.81
- Previous query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)

#### Average
- Current run: 1.421 (↓ -0.183)
- Previous run: 1.604

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Parent
#### Overall statistics
- Total time 7.968 (previously 9.139)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.454 (↓ -0.234)
- Current query: if if; stmt s; Select s such that Parent(s, if)
- Previous run: 1.688
- Previous query: if if; stmt s; Select s such that Parent(s, if)

#### Average
- Current run: 1.328 (↓ -0.195)
- Previous run: 1.523

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Parent_2
#### Overall statistics
- Total time 14.332 (previously 17.485)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.458 (↓ -0.471)
- Current query: stmt s; Select s such that Parent(s,2)
- Previous run: 1.929
- Previous query: stmt s; Select s such that Parent*(1,s)

#### Average
- Current run: 1.303 (↓ -0.287)
- Previous run: 1.59

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Parentt
#### Overall statistics
- Total time 3.921 (previously 4.421)
- 3 queries, (previously 3)

#### Maximum
- Current run: 1.443 (↓ -0.248)
- Current query: stmt s; while w; Select s such that Parent*(s, w)
- Previous run: 1.691
- Previous query: stmt s; while w; Select s such that Parent*(s, w)

#### Average
- Current run: 1.307 (↓ -0.167)
- Previous run: 1.474

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Pattern
#### Overall statistics
- Total time 9.65 (previously 11.275)
- 7 queries, (previously 7)

#### Maximum
- Current run: 1.654 (↓ -0.194)
- Current query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")
- Previous run: 1.848
- Previous query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")

#### Average
- Current run: 1.379 (↓ -0.232)
- Previous run: 1.611

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### PatternIf
#### Overall statistics
- Total time 2.78 (previously 3.079)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.435 (↓ -0.186)
- Current query: if ifs; Select ifs pattern ifs(_,_,_)
- Previous run: 1.621
- Previous query: if ifs; Select ifs pattern ifs(_,_,_)

#### Average
- Current run: 1.39 (↓ -0.149)
- Previous run: 1.539

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### PatternWhile
#### Overall statistics
- Total time 2.84 (previously 3.649)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.563 (↓ -0.414)
- Current query: while w; Select w pattern w(_,_)
- Previous run: 1.977
- Previous query: while w; Select w pattern w(_,_)

#### Average
- Current run: 1.42 (↓ -0.405)
- Previous run: 1.825

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Tuple_clause
#### Overall statistics
- Total time 12.421 (previously 13.807)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.521 (↓ -0.214)
- Current query: assign a; variable v; Select <a, v> such that Modifies(a, v)
- Previous run: 1.735
- Previous query: variable v1, v2; stmt s; Select<v1, v2, s> such that Modifies(s, v1) and Modifies(s, v2) and Parent(s, 1)

#### Average
- Current run: 1.38 (↓ -0.154)
- Previous run: 1.534

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Uses
#### Overall statistics
- Total time 11.988 (previously 14.067)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.558 (↓ -0.369)
- Current query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)
- Previous run: 1.927
- Previous query: stmt s; Select s such that Uses(s, "i")

#### Average
- Current run: 1.332 (↓ -0.231)
- Previous run: 1.563

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### UsesP
#### Overall statistics
- Total time 8.234 (previously 8.822)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.561 (↓ -0.024)
- Current query: variable v; Select v such that Uses("uses3", v)
- Previous run: 1.585
- Previous query: variable v; Select v such that Uses("uses3", v)

#### Average
- Current run: 1.372 (↓ -0.098)
- Previous run: 1.47

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### With
#### Overall statistics
- Total time 32.98 (previously 38.272)
- 25 queries, (previously 25)

#### Maximum
- Current run: 1.544 (↓ -0.152)
- Current query: procedure p; call c; while w; Select p such that Calls ("Second", p) and Parent (w, c) with c.procName = p.procName
- Previous run: 1.696
- Previous query: stmt s; constant c; Select s with s.stmt# = c.value

#### Average
- Current run: 1.319 (↓ -0.212)
- Previous run: 1.531

#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----


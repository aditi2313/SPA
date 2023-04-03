### Global
#### Overall statistics
- Total time 692.852 (previously 2134.275)
- 313 queries, (previously 311)

#### Maximum
- Current run: 133.398 <mark style='background-color: lightgreen'>(↓ -1133.917)</mark>
- Current query: Multi_clause_7 - stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select pn such that Calls(_, _) such that Calls*(_, p) pattern a(_, _) such that Parent*(_, s) with v.varName = pn.varName such that Follows(_, pn) pattern w(v, _)
- Previous run: 1267.315
- Previous query: Multi_clause_7 - stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select pn such that Calls(_, _) such that Calls*(_, p) pattern a(_, _) such that Parent*(_, s) with v.varName = pn.varName such that Follows(_, pn) pattern w(v, _)

#### Average
- Current run: 2.214 <mark style='background-color: lightgreen'>(↓ -4.649)</mark>
- Previous run: 6.863
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_basic
#### Overall statistics
- Total time 2.582 (previously 2.682)
- 1 queries, (previously 1)

#### Maximum
- Current run: 2.582 (↓ -0.1)
- Current query: stmt s; Select s such that Follows*(6, s)
- Previous run: 2.682
- Previous query: stmt s; Select s such that Follows*(6, s)

#### Average
- Current run: 2.582 (↓ -0.1)
- Previous run: 2.682
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_deep_calls
#### Overall statistics
- Total time 6.805 (previously 0)
- 3 queries, (previously 0)

#### Maximum
- Current run: 3.3 <mark style='background-color: lightpink'>(↑ 3.3)</mark>
- Current query: procedure p; Select p such that Calls*(p, "p1")
- Previous run: 0
- Previous query: 

#### Average
- Current run: 2.268 <mark style='background-color: lightpink'>(↑ 2.268)</mark>
- Previous run: 0
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_deep_if
#### Overall statistics
- Total time 3.266 (previously 9.91)
- 1 queries, (previously 1)

#### Maximum
- Current run: 3.266 <mark style='background-color: lightgreen'>(↓ -6.644)</mark>
- Current query: stmt s; Select s such that Parent*(1, s)
- Previous run: 9.91
- Previous query: stmt s; Select s such that Parent*(1, s)

#### Average
- Current run: 3.266 <mark style='background-color: lightgreen'>(↓ -6.644)</mark>
- Previous run: 9.91
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_deep_while
#### Overall statistics
- Total time 5.047 (previously 11.316)
- 2 queries, (previously 2)

#### Maximum
- Current run: 3.331 <mark style='background-color: lightgreen'>(↓ -5.801)</mark>
- Current query: stmt s; Select s such that Parent*(s, 500)
- Previous run: 9.132
- Previous query: stmt s; Select s such that Parent*(s, 500)

#### Average
- Current run: 2.523 <mark style='background-color: lightgreen'>(↓ -3.135)</mark>
- Previous run: 5.658
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_follows
#### Overall statistics
- Total time 3.367 (previously 3.962)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.813 (↓ -0.558)
- Current query: stmt s; Select s such that Follows(s, 255)
- Previous run: 2.371
- Previous query: stmt s; Select s such that Follows(s, 255)

#### Average
- Current run: 1.683 (↓ -0.298)
- Previous run: 1.981
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_large_assignment
#### Overall statistics
- Total time 2.177 (previously 2.293)
- 1 queries, (previously 1)

#### Maximum
- Current run: 2.177 (↓ -0.116)
- Current query: variable v; Select v such that Uses(1, v)
- Previous run: 2.293
- Previous query: variable v; Select v such that Uses(1, v)

#### Average
- Current run: 2.177 (↓ -0.116)
- Previous run: 2.293
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### 500_multiple_proc
#### Overall statistics
- Total time 1.786 (previously 2.059)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.786 (↓ -0.273)
- Current query: stmt s; Select s such that Follows(6, s)
- Previous run: 2.059
- Previous query: stmt s; Select s such that Follows(6, s)

#### Average
- Current run: 1.786 (↓ -0.273)
- Previous run: 2.059
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Affects
#### Overall statistics
- Total time 16.845 (previously 15.357)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.855 (↓ -0.89)
- Current query: assign a; Select a such that Affects(a, 8)
- Previous run: 2.745
- Previous query: assign a; Select a such that Affects(a, 8)

#### Average
- Current run: 1.531 (↑ 0.135)
- Previous run: 1.396
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### AffectsT
#### Overall statistics
- Total time 17.808 (previously 20.079)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.813 (↓ -0.723)
- Current query: assign a; Select a such that Affects*(a, 10)
- Previous run: 2.536
- Previous query: assign a; Select a such that Affects*(a, 10)

#### Average
- Current run: 1.619 (↓ -0.206)
- Previous run: 1.825
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### AffectsT_2
#### Overall statistics
- Total time 23.139 (previously 16.586)
- 15 queries, (previously 15)

#### Maximum
- Current run: 2.133 (↑ 0.446)
- Current query: assign a; Select a such that Affects*(2, a)
- Previous run: 1.687
- Previous query: assign a; Select a such that Affects*(1, a)

#### Average
- Current run: 1.543 (↑ 0.437)
- Previous run: 1.106
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Basic
#### Overall statistics
- Total time 18.753 (previously 12.37)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.763 (↑ 0.286)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.477
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 1.563 <mark style='background-color: lightpink'>(↑ 0.532)</mark>
- Previous run: 1.031
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Boolean
#### Overall statistics
- Total time 16.363 (previously 11.869)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.558 (↓ -0.079)
- Current query: stmt s; Select BOOLEAN such that Follows(s, _)
- Previous run: 1.637
- Previous query: stmt s; variable v; Select BOOLEAN such that Modifies(s, v)

#### Average
- Current run: 1.488 (↑ 0.409)
- Previous run: 1.079
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Calls
#### Overall statistics
- Total time 12.079 (previously 8.769)
- 8 queries, (previously 8)

#### Maximum
- Current run: 1.6 (↓ -0.01)
- Current query: procedure p; procedure q; Select p such that Calls(q, p)
- Previous run: 1.61
- Previous query: procedure p; procedure q; Select p such that Calls(q, p)

#### Average
- Current run: 1.51 (↑ 0.414)
- Previous run: 1.096
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### condexpr1
#### Overall statistics
- Total time 1.508 (previously 1.076)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.508 (↑ 0.432)
- Current query: stmt s;  Select s
- Previous run: 1.076
- Previous query: stmt s;  Select s

#### Average
- Current run: 1.508 (↑ 0.432)
- Previous run: 1.076
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Follows
#### Overall statistics
- Total time 13.866 (previously 10.278)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.759 (↓ -0.042)
- Current query: stmt s;  Select s such that Follows*(3,4)
- Previous run: 1.801
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.541 (↑ 0.399)
- Previous run: 1.142
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Follows2
#### Overall statistics
- Total time 7.24 (previously 5.468)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.594 (↑ 0.297)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.297
- Previous query: stmt s;  Select s        such that Follows*(s, 2147483647)

#### Average
- Current run: 1.448 (↑ 0.354)
- Previous run: 1.094
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Milestone_1
#### Overall statistics
- Total time 13.378 (previously 10.791)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.601 (↓ -0.24)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.841
- Previous query: variable v; Select v such that Modifies(2, v)

#### Average
- Current run: 1.486 (↑ 0.287)
- Previous run: 1.199
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Modifies
#### Overall statistics
- Total time 7.499 (previously 5.224)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.707 (↑ 0.141)
- Current query: variable v; stmt s; Select v such that Modifies(s, v)
- Previous run: 1.566
- Previous query: variable v; stmt s; Select v such that Modifies(s, v)

#### Average
- Current run: 1.5 (↑ 0.455)
- Previous run: 1.045
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### ModifiesP
#### Overall statistics
- Total time 6.191 (previously 4.444)
- 4 queries, (previously 4)

#### Maximum
- Current run: 1.643 (↑ 0.283)
- Current query: variable v; Select v such that Modifies("modifies3", v)
- Previous run: 1.36
- Previous query: variable v; Select v such that Modifies("modifies3", v)

#### Average
- Current run: 1.548 (↑ 0.437)
- Previous run: 1.111
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### ModifiesP_2
#### Overall statistics
- Total time 7.356 (previously 4.768)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.547 (↑ 0.266)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.281
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 1.471 <mark style='background-color: lightpink'>(↑ 0.517)</mark>
- Previous run: 0.954
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi-clause
#### Overall statistics
- Total time 18.038 (previously 14.662)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.672 (↓ -0.596)
- Current query: assign a; Select a such that Modifies (a, "b") and Parent* (1,a) and Next(3,a)
- Previous run: 2.268
- Previous query: assign a; Select a such that Modifies (a, "b") and Parent* (1,a) and Next(3,a)

#### Average
- Current run: 1.503 (↑ 0.281)
- Previous run: 1.222
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_10
#### Overall statistics
- Total time 2.395 (previously 6.494)
- 1 queries, (previously 1)

#### Maximum
- Current run: 2.395 <mark style='background-color: lightgreen'>(↓ -4.099)</mark>
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Affects*(_, _) pattern a(_, "y") such that Calls*(_, "pain") with ifs.stmt# = call.stmt# with r.varName = pn.varName such that Modifies("pain", "b") pattern ifs("c", _, _) such that Uses("third", _) such that Next(_, 4) such that Next*(_, _)
- Previous run: 6.494
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Affects*(_, _) pattern a(_, "y") such that Calls*(_, "pain") with ifs.stmt# = call.stmt# with r.varName = pn.varName such that Modifies("pain", "b") pattern ifs("c", _, _) such that Uses("third", _) such that Next(_, 4) such that Next*(_, _)

#### Average
- Current run: 2.395 <mark style='background-color: lightgreen'>(↓ -4.099)</mark>
- Previous run: 6.494
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_7
#### Overall statistics
- Total time 284.458 (previously 1734.037)
- 57 queries, (previously 57)

#### Maximum
- Current run: 133.398 <mark style='background-color: lightgreen'>(↓ -1133.917)</mark>
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select pn such that Calls(_, _) such that Calls*(_, p) pattern a(_, _) such that Parent*(_, s) with v.varName = pn.varName such that Follows(_, pn) pattern w(v, _)
- Previous run: 1267.315
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select pn such that Calls(_, _) such that Calls*(_, p) pattern a(_, _) such that Parent*(_, s) with v.varName = pn.varName such that Follows(_, pn) pattern w(v, _)

#### Average
- Current run: 4.99 <mark style='background-color: lightgreen'>(↓ -25.432)</mark>
- Previous run: 30.422
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_8
#### Overall statistics
- Total time 40.9 (previously 64.526)
- 24 queries, (previously 24)

#### Maximum
- Current run: 2.226 <mark style='background-color: lightgreen'>(↓ -4.62)</mark>
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN pattern ifs("ganesh", _, _) such that Calls*(_, _) with v.varName = p.procName such that Follows*(_, 5) such that Affects(_, _) such that Follows(_, _) pattern a("kmn", _"c"_) such that Next*(5, 16)
- Previous run: 6.846
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN pattern ifs("ganesh", _, _) such that Calls*(_, _) with v.varName = p.procName such that Follows*(_, 5) such that Affects(_, _) such that Follows(_, _) pattern a("kmn", _"c"_) such that Next*(5, 16)

#### Average
- Current run: 1.704 <mark style='background-color: lightgreen'>(↓ -0.985)</mark>
- Previous run: 2.689
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Multi_clause_9
#### Overall statistics
- Total time 10.308 (previously 29.924)
- 5 queries, (previously 5)

#### Maximum
- Current run: 2.863 <mark style='background-color: lightgreen'>(↓ -10.995)</mark>
- Current query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Calls*(_, _) pattern ifs(_, _, _) with v.varName = r.varName such that Next*(20, _) pattern w(_, _) such that Uses(1, _) such that Affects*(21, _) such that Calls(_, _) such that Follows(17, 17)
- Previous run: 13.858
- Previous query: stmt s; read r; print pn; call call; while w; if ifs; assign a; variable v; constant c; procedure p;  Select BOOLEAN such that Calls*(_, _) pattern ifs(_, _, _) with v.varName = r.varName such that Next*(20, _) pattern w(_, _) such that Uses(1, _) such that Affects*(21, _) such that Calls(_, _) such that Follows(17, 17)

#### Average
- Current run: 2.062 <mark style='background-color: lightgreen'>(↓ -3.923)</mark>
- Previous run: 5.985
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Next
#### Overall statistics
- Total time 16.057 (previously 10.783)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.634 (↑ 0.218)
- Current query: stmt s; Select s such that Next(4, s)
- Previous run: 1.416
- Previous query: stmt s; Select s such that Next(4, s)

#### Average
- Current run: 1.46 (↑ 0.48)
- Previous run: 0.98
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Next_2
#### Overall statistics
- Total time 9.625 (previously 9.847)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.81 (↓ -0.37)
- Current query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)
- Previous run: 2.18
- Previous query: stmt s1, s2, s3, s4; Select s4 such that Next(s1, s2) and Next(s2, s3) such that Next(s3, s4)

#### Average
- Current run: 1.604 (↓ -0.037)
- Previous run: 1.641
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Parent
#### Overall statistics
- Total time 9.139 (previously 7.441)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.688 (↑ 0.135)
- Current query: if if; stmt s; Select s such that Parent(s, if)
- Previous run: 1.553
- Previous query: if if, if2; Select if such that Parent (if, if2)

#### Average
- Current run: 1.523 (↑ 0.283)
- Previous run: 1.24
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Parent_2
#### Overall statistics
- Total time 17.485 (previously 10.098)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.929 (↑ 0.746)
- Current query: stmt s; Select s such that Parent*(1,s)
- Previous run: 1.183
- Previous query: stmt s; Select s such that Parent(s,2)

#### Average
- Current run: 1.59 <mark style='background-color: lightpink'>(↑ 0.672)</mark>
- Previous run: 0.918
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Parentt
#### Overall statistics
- Total time 4.421 (previously 3.463)
- 3 queries, (previously 3)

#### Maximum
- Current run: 1.691 (↑ 0.189)
- Current query: stmt s; while w; Select s such that Parent*(s, w)
- Previous run: 1.502
- Previous query: stmt s; while w; Select s such that Parent*(s, w)

#### Average
- Current run: 1.474 (↑ 0.32)
- Previous run: 1.154
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Pattern
#### Overall statistics
- Total time 11.275 (previously 10.494)
- 7 queries, (previously 7)

#### Maximum
- Current run: 1.848 (↓ -0.711)
- Current query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")
- Previous run: 2.559
- Previous query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")

#### Average
- Current run: 1.611 (↑ 0.112)
- Previous run: 1.499
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### PatternIf
#### Overall statistics
- Total time 3.079 (previously 2.245)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.621 (↑ 0.317)
- Current query: if ifs; Select ifs pattern ifs(_,_,_)
- Previous run: 1.304
- Previous query: if ifs; Select ifs pattern ifs(_,_,_)

#### Average
- Current run: 1.539 (↑ 0.416)
- Previous run: 1.123
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### PatternWhile
#### Overall statistics
- Total time 3.649 (previously 2.184)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.977 (↑ 0.691)
- Current query: while w; Select w pattern w(_,_)
- Previous run: 1.286
- Previous query: while w; Select w pattern w(_,_)

#### Average
- Current run: 1.825 <mark style='background-color: lightpink'>(↑ 0.733)</mark>
- Previous run: 1.092
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Tuple_clause
#### Overall statistics
- Total time 13.807 (previously 11.865)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.735 (↓ -0.293)
- Current query: variable v1, v2; stmt s; Select<v1, v2, s> such that Modifies(s, v1) and Modifies(s, v2) and Parent(s, 1)
- Previous run: 2.028
- Previous query: variable v1, v2; stmt s; Select<v1, v2, s> such that Modifies(s, v1) and Modifies(s, v2) and Parent(s, 1)

#### Average
- Current run: 1.534 (↑ 0.216)
- Previous run: 1.318
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### Uses
#### Overall statistics
- Total time 14.067 (previously 10.68)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.927 (↓ -0.317)
- Current query: stmt s; Select s such that Uses(s, "i")
- Previous run: 2.244
- Previous query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)

#### Average
- Current run: 1.563 (↑ 0.376)
- Previous run: 1.187
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### UsesP
#### Overall statistics
- Total time 8.822 (previously 8.99)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.585 (↓ -0.78)
- Current query: variable v; Select v such that Uses("uses3", v)
- Previous run: 2.365
- Previous query: variable v; Select v such that Uses("uses3", v)

#### Average
- Current run: 1.47 (↓ -0.028)
- Previous run: 1.498
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----

### With
#### Overall statistics
- Total time 38.272 (previously 29.457)
- 25 queries, (previously 25)

#### Maximum
- Current run: 1.696 <mark style='background-color: lightgreen'>(↓ -1.141)</mark>
- Current query: stmt s; constant c; Select s with s.stmt# = c.value
- Previous run: 2.837
- Previous query: stmt s; constant c; Select s with s.stmt# = c.value

#### Average
- Current run: 1.531 (↑ 0.353)
- Previous run: 1.178
#### Timeout
- Number of queries that timed out: 0 (↓ 0)

----


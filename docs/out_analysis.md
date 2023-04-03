### Global
#### Overall statistics
- Total time 274.26 (previously 326.802)
- 222 queries, (previously 226)

#### Maximum
- Current run: 32.081 <mark style='background-color: lightpink'>(↑ 27.841)</mark>
- Current query: 500_deep_while - stmt s; Select s such that Parent*(s, 500)
- Previous run: 4.24
- Previous query: 500_deep_while - stmt s; Select s such that Parent*(s, 500)

#### Average
- Current run: 1.235 (↓ -0.211)
- Previous run: 1.446
----

### 500_basic
#### Overall statistics
- Total time 3.856 (previously 2.853)
- 1 queries, (previously 1)

#### Maximum
- Current run: 3.856 <mark style='background-color: lightpink'>(↑ 1.003)</mark>
- Current query: stmt s; Select s such that Follows*(6, s)
- Previous run: 2.853
- Previous query: stmt s; Select s such that Follows*(6, s)

#### Average
- Current run: 3.856 <mark style='background-color: lightpink'>(↑ 1.003)</mark>
- Previous run: 2.853
----

### 500_deep_if
#### Overall statistics
- Total time 5.901 (previously 2.99)
- 1 queries, (previously 1)

#### Maximum
- Current run: 5.901 <mark style='background-color: lightpink'>(↑ 2.911)</mark>
- Current query: stmt s; Select s such that Parent*(1, s)
- Previous run: 2.99
- Previous query: stmt s; Select s such that Parent*(1, s)

#### Average
- Current run: 5.901 <mark style='background-color: lightpink'>(↑ 2.911)</mark>
- Previous run: 2.99
----

### 500_deep_while
#### Overall statistics
- Total time 34.383 (previously 5.85)
- 2 queries, (previously 2)

#### Maximum
- Current run: 32.081 <mark style='background-color: lightpink'>(↑ 27.841)</mark>
- Current query: stmt s; Select s such that Parent*(s, 500)
- Previous run: 4.24
- Previous query: stmt s; Select s such that Parent*(s, 500)

#### Average
- Current run: 17.192 <mark style='background-color: lightpink'>(↑ 14.267)</mark>
- Previous run: 2.925
----

### 500_follows
#### Overall statistics
- Total time 4.29 (previously 3.927)
- 2 queries, (previously 2)

#### Maximum
- Current run: 2.601 (↑ 0.216)
- Current query: stmt s; Select s such that Follows(s, 255)
- Previous run: 2.385
- Previous query: stmt s; Select s such that Follows(s, 255)

#### Average
- Current run: 2.145 (↑ 0.182)
- Previous run: 1.963
----

### 500_multiple_proc
#### Overall statistics
- Total time 2.138 (previously 1.54)
- 1 queries, (previously 1)

#### Maximum
- Current run: 2.138 (↑ 0.598)
- Current query: stmt s; Select s such that Follows(6, s)
- Previous run: 1.54
- Previous query: stmt s; Select s such that Follows(6, s)

#### Average
- Current run: 2.138 <mark style='background-color: lightpink'>(↑ 0.598)</mark>
- Previous run: 1.54
----

### Affects
#### Overall statistics
- Total time 10.411 (previously 14.953)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.278 (↓ -0.257)
- Current query: assign a; Select a such that Affects(a, 8)
- Previous run: 1.535
- Previous query: assign a; Select a such that Affects(a, 8)

#### Average
- Current run: 0.946 (↓ -0.413)
- Previous run: 1.359
----

### AffectsT
#### Overall statistics
- Total time 14.93 (previously 16.215)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.99 (↑ 0.29)
- Current query: assign a; Select a such that Affects*(a, 10)
- Previous run: 1.7
- Previous query: assign a; Select a such that Affects*(a, 10)

#### Average
- Current run: 1.357 (↓ -0.117)
- Previous run: 1.474
----

### AffectsT_2
#### Overall statistics
- Total time 14.327 (previously 22.583)
- 15 queries, (previously 15)

#### Maximum
- Current run: 1.326 (↓ -0.627)
- Current query: assign a; Select a such that Affects*(1, a)
- Previous run: 1.953
- Previous query: assign a; Select a such that Affects*(13, a)

#### Average
- Current run: 0.955 <mark style='background-color: lightgreen'>(↓ -0.551)</mark>
- Previous run: 1.506
----

### Basic
#### Overall statistics
- Total time 15.061 (previously 17.458)
- 12 queries, (previously 12)

#### Maximum
- Current run: 2.3 (↑ 0.362)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.938
- Previous query: assign a;  Select a pattern a(_, "a - b")

#### Average
- Current run: 1.255 (↓ -0.2)
- Previous run: 1.455
----

### Boolean
#### Overall statistics
- Total time 10.808 (previously 14.944)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.404 (↓ -0.121)
- Current query: stmt s; Select BOOLEAN such that Follows(s, _)
- Previous run: 1.525
- Previous query: stmt s; Select BOOLEAN such that Follows(s, 2)

#### Average
- Current run: 0.983 (↓ -0.376)
- Previous run: 1.359
----

### Calls
#### Overall statistics
- Total time 6.831 (previously 10.952)
- 8 queries, (previously 8)

#### Maximum
- Current run: 1.304 (↓ -0.303)
- Current query: procedure p; procedure q; Select p such that Calls(q, p)
- Previous run: 1.607
- Previous query: procedure p; procedure q; Select p such that Calls(q, p)

#### Average
- Current run: 0.854 <mark style='background-color: lightgreen'>(↓ -0.515)</mark>
- Previous run: 1.369
----

### condexpr1
#### Overall statistics
- Total time 1.389 (previously 1.413)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.389 (↓ -0.024)
- Current query: stmt s;  Select s
- Previous run: 1.413
- Previous query: stmt s;  Select s

#### Average
- Current run: 1.389 (↓ -0.024)
- Previous run: 1.413
----

### Follows
#### Overall statistics
- Total time 8.859 (previously 12.142)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.177 (↓ -0.331)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.508
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 0.984 (↓ -0.365)
- Previous run: 1.349
----

### Follows2
#### Overall statistics
- Total time 5.971 (previously 6.882)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.606 (↑ 0.118)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.488
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.194 (↓ -0.182)
- Previous run: 1.376
----

### Milestone_1
#### Overall statistics
- Total time 9.56 (previously 12.213)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.81 (↑ 0.395)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.415
- Previous query: assign a;  Select a pattern a(_, "a + b")

#### Average
- Current run: 1.062 (↓ -0.295)
- Previous run: 1.357
----

### Modifies
#### Overall statistics
- Total time 5.041 (previously 6.996)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.459 (↓ -0.194)
- Current query: variable v; stmt s; Select v such that Modifies(s, v)
- Previous run: 1.653
- Previous query: variable v; stmt s; Select v such that Modifies(s, v)

#### Average
- Current run: 1.008 (↓ -0.391)
- Previous run: 1.399
----

### ModifiesP
#### Overall statistics
- Total time 3.997 (previously 5.611)
- 4 queries, (previously 4)

#### Maximum
- Current run: 1.488 (↓ -0.039)
- Current query: variable v; Select v such that Modifies("modifies3", v)
- Previous run: 1.527
- Previous query: variable v; Select v such that Modifies("modifies3", v)

#### Average
- Current run: 0.999 (↓ -0.404)
- Previous run: 1.403
----

### ModifiesP_2
#### Overall statistics
- Total time 4.758 (previously 7.416)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.432 (↓ -0.167)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.599
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 0.952 <mark style='background-color: lightgreen'>(↓ -0.531)</mark>
- Previous run: 1.483
----

### Multi-clause
#### Overall statistics
- Total time 12.849 (previously 16.252)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.562 (↑ 0.057)
- Current query: assign a; Select a such that Modifies (a, "b") and Parent* (1,a) and Next(3,a)
- Previous run: 1.505
- Previous query: assign a; Select a such that Modifies(a, "b") such that Parent* (1,a) pattern a("b", _)

#### Average
- Current run: 1.071 (↓ -0.283)
- Previous run: 1.354
----

### Next
#### Overall statistics
- Total time 11.339 (previously 15.04)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.706 (↑ 0.219)
- Current query: stmt s; Select s such that Next(s, 6)
- Previous run: 1.487
- Previous query: stmt s; Select s such that Next(2, s)

#### Average
- Current run: 1.031 (↓ -0.336)
- Previous run: 1.367
----

### Next_2
#### Overall statistics
- Total time 8.894 (previously 8.666)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.736 (↑ 0.194)
- Current query: stmt s1, s2, s3; Select s1 such that Next* (s1, s2) and Next*(s2, s3)
- Previous run: 1.542
- Previous query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)

#### Average
- Current run: 1.482 (↑ 0.038)
- Previous run: 1.444
----

### Parent
#### Overall statistics
- Total time 5.476 (previously 8.161)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.433 (↓ -0.094)
- Current query: if if; stmt s; Select s such that Parent(s, if)
- Previous run: 1.527
- Previous query: if if; stmt s; Select s such that Parent(s, if)

#### Average
- Current run: 0.913 (↓ -0.447)
- Previous run: 1.36
----

### Parent_2
#### Overall statistics
- Total time 11.253 (previously 15.052)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.378 (↓ -0.158)
- Current query: stmt s; Select s such that Parent(3,s)
- Previous run: 1.536
- Previous query: stmt s; Select s such that Parent(s,2)

#### Average
- Current run: 1.023 (↓ -0.345)
- Previous run: 1.368
----

### Parentt
#### Overall statistics
- Total time 3.766 (previously 4.145)
- 3 queries, (previously 3)

#### Maximum
- Current run: 1.384 (↓ -0.181)
- Current query: procedure p; Select s such that Parent*(p, 4)
- Previous run: 1.565
- Previous query: stmt s; while w; Select s such that Parent*(s, w)

#### Average
- Current run: 1.255 (↓ -0.127)
- Previous run: 1.382
----

### Pattern
#### Overall statistics
- Total time 6.028 (previously 10.204)
- 7 queries, (previously 7)

#### Maximum
- Current run: 1.129 (↓ -0.685)
- Current query: assign a; variable v; Select a such that pattern a(v, "x + y * z")
- Previous run: 1.814
- Previous query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")

#### Average
- Current run: 0.861 <mark style='background-color: lightgreen'>(↓ -0.597)</mark>
- Previous run: 1.458
----

### PatternIf
#### Overall statistics
- Total time 1.85 (previously 2.986)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.033 (↓ -0.524)
- Current query: if ifs; Select ifs pattern ifs(_,_,_)
- Previous run: 1.557
- Previous query: if ifs; Select ifs pattern ifs(_,_,_)

#### Average
- Current run: 0.925 <mark style='background-color: lightgreen'>(↓ -0.568)</mark>
- Previous run: 1.493
----

### PatternWhile
#### Overall statistics
- Total time 3.449 (previously 2.988)
- 2 queries, (previously 2)

#### Maximum
- Current run: 2.51 (↑ 0.96)
- Current query: while w; Select w pattern w(_,_)
- Previous run: 1.55
- Previous query: while w; Select w pattern w(_,_)

#### Average
- Current run: 1.724 (↑ 0.23)
- Previous run: 1.494
----

### Tuple_clause
#### Overall statistics
- Total time 10.261 (previously 12.625)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.41 (↓ -0.175)
- Current query: assign a; variable v; Select <a, v> such that Modifies(a, v)
- Previous run: 1.585
- Previous query: assign a; variable v; Select <a, v> such that Modifies(a, v)

#### Average
- Current run: 1.14 (↓ -0.263)
- Previous run: 1.403
----

### Uses
#### Overall statistics
- Total time 9.167 (previously 12.878)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.568 (↓ -0.132)
- Current query: stmt s; Select s such that Uses(s, "i")
- Previous run: 1.7
- Previous query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)

#### Average
- Current run: 1.019 (↓ -0.412)
- Previous run: 1.431
----

### UsesP
#### Overall statistics
- Total time 6.227 (previously 8.426)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.53 (↓ -0.04)
- Current query: variable v; Select v such that Uses("uses3", v)
- Previous run: 1.57
- Previous query: variable v; Select v such that Uses("uses3", v)

#### Average
- Current run: 1.038 (↓ -0.366)
- Previous run: 1.404
----

### With
#### Overall statistics
- Total time 21.19 (previously 34.712)
- 25 queries, (previously 25)

#### Maximum
- Current run: 1.488 (↓ -0.108)
- Current query: procedure p; Select p with p.procName = "First"
- Previous run: 1.596
- Previous query: procedure p; Select p with p.procName = "First"

#### Average
- Current run: 0.848 <mark style='background-color: lightgreen'>(↓ -0.54)</mark>
- Previous run: 1.388
----


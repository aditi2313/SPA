### Global
#### Overall statistics
- Total time 404.238 (previously 374.04)
- 226 queries, (previously 224)

#### Maximum
- Current run: 25.892 (↓ -7.613)
- Current query: 500_deep_while - stmt s; Select s such that Parent*(s, 500)
- Previous run: 33.505
- Previous query: 500_deep_calls - procedure p; Select p such that Calls*(p, "p1")

#### Average
- Current run: 1.789 (↑ 0.119)
- Previous run: 1.67
----

### 500_basic
#### Overall statistics
- Total time 1.93 (previously 2.048)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.93 (↓ -0.118)
- Current query: stmt s; Select s such that Follows*(6, s)
- Previous run: 2.048
- Previous query: stmt s; Select s such that Follows*(6, s)

#### Average
- Current run: 1.93 (↓ -0.118)
- Previous run: 2.048
----

### 500_deep_calls
#### Overall statistics
- Total time 7.723 (previously 36.689)
- 3 queries, (previously 3)

#### Maximum
- Current run: 3.553 (↓ -29.952)
- Current query: procedure p; Select p such that Calls*(p, "p1")
- Previous run: 33.505
- Previous query: procedure p; Select p such that Calls*(p, "p1")

#### Average
- Current run: 2.574 (↓ -9.656)
- Previous run: 12.23
----

### 500_deep_if
#### Overall statistics
- Total time 3.399 (previously 3.013)
- 1 queries, (previously 1)

#### Maximum
- Current run: 3.399 (↑ 0.386)
- Current query: stmt s; Select s such that Parent*(1, s)
- Previous run: 3.013
- Previous query: stmt s; Select s such that Parent*(1, s)

#### Average
- Current run: 3.399 (↑ 0.386)
- Previous run: 3.013
----

### 500_deep_while
#### Overall statistics
- Total time 27.788 (previously 24.979)
- 2 queries, (previously 2)

#### Maximum
- Current run: 25.892 (↑ 2.432)
- Current query: stmt s; Select s such that Parent*(s, 500)
- Previous run: 23.46
- Previous query: stmt s; Select s such that Parent*(s, 500)

#### Average
- Current run: 13.894 (↑ 1.405)
- Previous run: 12.489
----

### 500_follows
#### Overall statistics
- Total time 9.479 (previously 0)
- 2 queries, (previously 0)

#### Maximum
- Current run: 7.503 (↑ 7.503)
- Current query: stmt s; Select s such that Follows(254, s)
- Previous run: 0
- Previous query: 

#### Average
- Current run: 4.739 (↑ 4.739)
- Previous run: 0
----

### 500_large_assignment
#### Overall statistics
- Total time 1.795 (previously 1.532)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.795 (↑ 0.263)
- Current query: variable v; Select v such that Uses(1, v)
- Previous run: 1.532
- Previous query: variable v; Select v such that Uses(1, v)

#### Average
- Current run: 1.795 (↑ 0.263)
- Previous run: 1.532
----

### 500_multiple_proc
#### Overall statistics
- Total time 1.997 (previously 1.713)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.997 (↑ 0.284)
- Current query: stmt s; Select s such that Follows(6, s)
- Previous run: 1.713
- Previous query: stmt s; Select s such that Follows(6, s)

#### Average
- Current run: 1.997 (↑ 0.284)
- Previous run: 1.713
----

### Affects
#### Overall statistics
- Total time 17.821 (previously 15.11)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.822 (↑ 0.178)
- Current query: assign a; Select a such that Affects(a, 8)
- Previous run: 1.644
- Previous query: assign a; Select a such that Affects(a, 8)

#### Average
- Current run: 1.62 (↑ 0.246)
- Previous run: 1.374
----

### AffectsT
#### Overall statistics
- Total time 17.864 (previously 16.715)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.871 (↓ -0.012)
- Current query: assign a; Select a such that Affects*(a, 10)
- Previous run: 1.883
- Previous query: assign a; Select a such that Affects*(a, 30)

#### Average
- Current run: 1.624 (↑ 0.104)
- Previous run: 1.52
----

### AffectsT_2
#### Overall statistics
- Total time 25.61 (previously 20.517)
- 15 queries, (previously 15)

#### Maximum
- Current run: 1.888 (↑ 0.326)
- Current query: assign a; Select a such that Affects*(1, a)
- Previous run: 1.562
- Previous query: assign a; Select a such that Affects*(1, a)

#### Average
- Current run: 1.707 (↑ 0.339)
- Previous run: 1.368
----

### Basic
#### Overall statistics
- Total time 19.825 (previously 17.554)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.861 (↑ 0.141)
- Current query: variable var123; Select var123 such that Uses(5, var123)
- Previous run: 1.72
- Previous query: while while; if f; Select while such that Parent(while, f)

#### Average
- Current run: 1.652 (↑ 0.189)
- Previous run: 1.463
----

### Boolean
#### Overall statistics
- Total time 17.909 (previously 15.731)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.796 (↑ 0.151)
- Current query: stmt s; variable v; Select BOOLEAN such that Modifies(s, v)
- Previous run: 1.645
- Previous query: stmt s; variable v; Select BOOLEAN such that Modifies(s, v)

#### Average
- Current run: 1.628 (↑ 0.198)
- Previous run: 1.43
----

### Calls
#### Overall statistics
- Total time 12.732 (previously 11.112)
- 8 queries, (previously 8)

#### Maximum
- Current run: 1.716 (↑ 0.2)
- Current query: procedure p; procedure q; Select p such that Calls(q, p)
- Previous run: 1.516
- Previous query: procedure p; procedure q; Select p such that Calls(q, p)

#### Average
- Current run: 1.591 (↑ 0.202)
- Previous run: 1.389
----

### condexpr1
#### Overall statistics
- Total time 1.424 (previously 1.315)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.424 (↑ 0.109)
- Current query: stmt s;  Select s
- Previous run: 1.315
- Previous query: stmt s;  Select s

#### Average
- Current run: 1.424 (↑ 0.109)
- Previous run: 1.315
----

### Follows
#### Overall statistics
- Total time 13.936 (previously 12.725)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.688 (↓ -0.009)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.697
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.548 (↑ 0.134)
- Previous run: 1.414
----

### Follows2
#### Overall statistics
- Total time 8.022 (previously 7.47)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.824 (↓ -0.023)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.847
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.604 (↑ 0.11)
- Previous run: 1.494
----

### Milestone_1
#### Overall statistics
- Total time 14.23 (previously 12.571)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.721 (↑ 0.144)
- Current query: variable v; Select v such that Modifies(2, v)
- Previous run: 1.577
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 1.581 (↑ 0.184)
- Previous run: 1.397
----

### Modifies
#### Overall statistics
- Total time 8.261 (previously 6.81)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.734 (↑ 0.147)
- Current query: variable v; Select v such that Modifies(3, v)
- Previous run: 1.587
- Previous query: variable v; stmt s; Select v such that Modifies(s, v)

#### Average
- Current run: 1.652 (↑ 0.29)
- Previous run: 1.362
----

### ModifiesP
#### Overall statistics
- Total time 6.536 (previously 6.057)
- 4 queries, (previously 4)

#### Maximum
- Current run: 1.725 (↑ 0.026)
- Current query: variable v; Select v such that Modifies("modifies3", v)
- Previous run: 1.699
- Previous query: variable v; Select v such that Modifies("modifies3", v)

#### Average
- Current run: 1.634 (↑ 0.12)
- Previous run: 1.514
----

### ModifiesP_2
#### Overall statistics
- Total time 7.964 (previously 7.24)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.755 (↑ 0.292)
- Current query: variable v; Select v such that Modifies(2, v)
- Previous run: 1.463
- Previous query: stmt s; Select s such that Modifies(s, "v3")

#### Average
- Current run: 1.593 (↑ 0.145)
- Previous run: 1.448
----

### Multi-clause
#### Overall statistics
- Total time 20.544 (previously 16.353)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.978 (↑ 0.417)
- Current query: assign a; Select a such that Modifies(a, "b") and Parent* (1,a) pattern a("b", _)
- Previous run: 1.561
- Previous query: assign a; Select a such that Modifies(a, "b") such that Parent* (1,a) pattern a("b", _)

#### Average
- Current run: 1.712 (↑ 0.349)
- Previous run: 1.363
----

### Next
#### Overall statistics
- Total time 17.996 (previously 16.148)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.91 (↓ -0.122)
- Current query: stmt s; Select s such that Next(4, s)
- Previous run: 2.032
- Previous query: stmt s; Select s such that Next(2, s)

#### Average
- Current run: 1.636 (↑ 0.168)
- Previous run: 1.468
----

### Next_2
#### Overall statistics
- Total time 10.103 (previously 9.781)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.801 (↓ -0.031)
- Current query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)
- Previous run: 1.832
- Previous query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)

#### Average
- Current run: 1.684 (↑ 0.054)
- Previous run: 1.63
----

### Parent
#### Overall statistics
- Total time 9.34 (previously 7.979)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.695 (↑ 0.182)
- Current query: if if; stmt s; Select s such that Parent(s, if)
- Previous run: 1.513
- Previous query: if if; stmt s; Select s such that Parent(s, if)

#### Average
- Current run: 1.557 (↑ 0.227)
- Previous run: 1.33
----

### Parent_2
#### Overall statistics
- Total time 17.312 (previously 15.023)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.743 (↑ 0.213)
- Current query: stmt s; Select s such that Parent(s,2)
- Previous run: 1.53
- Previous query: stmt s; Select s such that Parent(s,2)

#### Average
- Current run: 1.574 (↑ 0.208)
- Previous run: 1.366
----

### Parentt
#### Overall statistics
- Total time 4.655 (previously 4.377)
- 3 queries, (previously 3)

#### Maximum
- Current run: 1.759 (↑ 0.176)
- Current query: stmt s; while w; Select s such that Parent*(s, w)
- Previous run: 1.583
- Previous query: stmt s; while w; Select s such that Parent*(s, w)

#### Average
- Current run: 1.552 (↑ 0.093)
- Previous run: 1.459
----

### Pattern
#### Overall statistics
- Total time 11.635 (previously 10.227)
- 7 queries, (previously 7)

#### Maximum
- Current run: 2.051 (↑ 0.367)
- Current query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")
- Previous run: 1.684
- Previous query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")

#### Average
- Current run: 1.662 (↑ 0.201)
- Previous run: 1.461
----

### PatternIf
#### Overall statistics
- Total time 3.319 (previously 2.812)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.695 (↑ 0.212)
- Current query: if ifs; Select ifs pattern ifs(_,_,_)
- Previous run: 1.483
- Previous query: if ifs; Select ifs pattern ifs(_,_,_)

#### Average
- Current run: 1.659 (↑ 0.253)
- Previous run: 1.406
----

### PatternWhile
#### Overall statistics
- Total time 3.612 (previously 2.928)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.937 (↑ 0.364)
- Current query: while w; Select w pattern w(_,_)
- Previous run: 1.573
- Previous query: while w; Select w pattern w(_,_)

#### Average
- Current run: 1.806 (↑ 0.342)
- Previous run: 1.464
----

### Tuple_clause
#### Overall statistics
- Total time 15.458 (previously 13.04)
- 9 queries, (previously 9)

#### Maximum
- Current run: 2.086 (↑ 0.52)
- Current query: variable v; procedure p, q, r; assign a; Select <p, q, r, v> such that Calls(p, q) and Calls(q, r) pattern a(v, _"x"_)
- Previous run: 1.566
- Previous query: assign a; variable v; Select <a, v> such that Modifies(a, v)

#### Average
- Current run: 1.718 (↑ 0.269)
- Previous run: 1.449
----

### Uses
#### Overall statistics
- Total time 14.161 (previously 12.244)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.834 (↑ 0.271)
- Current query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)
- Previous run: 1.563
- Previous query: stmt s; Select s such that Uses(s, "i")

#### Average
- Current run: 1.573 (↑ 0.213)
- Previous run: 1.36
----

### UsesP
#### Overall statistics
- Total time 9.634 (previously 8.2)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.785 (↑ 0.242)
- Current query: variable v; Select v such that Uses("uses3", v)
- Previous run: 1.543
- Previous query: variable v; Select v such that Uses("uses3", v)

#### Average
- Current run: 1.606 (↑ 0.239)
- Previous run: 1.367
----

### With
#### Overall statistics
- Total time 40.224 (previously 34.027)
- 25 queries, (previously 25)

#### Maximum
- Current run: 1.775 (↑ 0.073)
- Current query:  Select BOOLEAN with 12 = 12
- Previous run: 1.702
- Previous query: procedure p; Select p with p.procName = "First"

#### Average
- Current run: 1.609 (↑ 0.248)
- Previous run: 1.361
----


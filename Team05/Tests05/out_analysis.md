### Global
#### Overall statistics
- Total time 326.802 (previously 404.238)
- 226 queries, (previously 226)

#### Maximum
- Current run: 4.24 (↓ -21.652)
- Current query: 500_deep_while - stmt s; Select s such that Parent*(s, 500)
- Previous run: 25.892
- Previous query: 500_deep_while - stmt s; Select s such that Parent*(s, 500)

#### Average
- Current run: 1.446 (↓ -0.343)
- Previous run: 1.789
----

### 500_basic
#### Overall statistics
- Total time 2.853 (previously 1.93)
- 1 queries, (previously 1)

#### Maximum
- Current run: 2.853 (↑ 0.923)
- Current query: stmt s; Select s such that Follows*(6, s)
- Previous run: 1.93
- Previous query: stmt s; Select s such that Follows*(6, s)

#### Average
- Current run: 2.853 (↑ 0.923)
- Previous run: 1.93
----

### 500_deep_calls
#### Overall statistics
- Total time 6.176 (previously 7.723)
- 3 queries, (previously 3)

#### Maximum
- Current run: 2.951 (↓ -0.602)
- Current query: procedure p; Select p such that Calls*(p, "p1")
- Previous run: 3.553
- Previous query: procedure p; Select p such that Calls*(p, "p1")

#### Average
- Current run: 2.059 (↓ -0.515)
- Previous run: 2.574
----

### 500_deep_if
#### Overall statistics
- Total time 2.99 (previously 3.399)
- 1 queries, (previously 1)

#### Maximum
- Current run: 2.99 (↓ -0.409)
- Current query: stmt s; Select s such that Parent*(1, s)
- Previous run: 3.399
- Previous query: stmt s; Select s such that Parent*(1, s)

#### Average
- Current run: 2.99 (↓ -0.409)
- Previous run: 3.399
----

### 500_deep_while
#### Overall statistics
- Total time 5.85 (previously 27.788)
- 2 queries, (previously 2)

#### Maximum
- Current run: 4.24 (↓ -21.652)
- Current query: stmt s; Select s such that Parent*(s, 500)
- Previous run: 25.892
- Previous query: stmt s; Select s such that Parent*(s, 500)

#### Average
- Current run: 2.925 (↓ -10.969)
- Previous run: 13.894
----

### 500_follows
#### Overall statistics
- Total time 3.927 (previously 9.479)
- 2 queries, (previously 2)

#### Maximum
- Current run: 2.385 (↓ -5.118)
- Current query: stmt s; Select s such that Follows(s, 255)
- Previous run: 7.503
- Previous query: stmt s; Select s such that Follows(254, s)

#### Average
- Current run: 1.963 (↓ -2.776)
- Previous run: 4.739
----

### 500_large_assignment
#### Overall statistics
- Total time 1.553 (previously 1.795)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.553 (↓ -0.242)
- Current query: variable v; Select v such that Uses(1, v)
- Previous run: 1.795
- Previous query: variable v; Select v such that Uses(1, v)

#### Average
- Current run: 1.553 (↓ -0.242)
- Previous run: 1.795
----

### 500_multiple_proc
#### Overall statistics
- Total time 1.54 (previously 1.997)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.54 (↓ -0.457)
- Current query: stmt s; Select s such that Follows(6, s)
- Previous run: 1.997
- Previous query: stmt s; Select s such that Follows(6, s)

#### Average
- Current run: 1.54 (↓ -0.457)
- Previous run: 1.997
----

### Affects
#### Overall statistics
- Total time 14.953 (previously 17.821)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.535 (↓ -0.287)
- Current query: assign a; Select a such that Affects(a, 8)
- Previous run: 1.822
- Previous query: assign a; Select a such that Affects(a, 8)

#### Average
- Current run: 1.359 (↓ -0.261)
- Previous run: 1.62
----

### AffectsT
#### Overall statistics
- Total time 16.215 (previously 17.864)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.7 (↓ -0.171)
- Current query: assign a; Select a such that Affects*(a, 10)
- Previous run: 1.871
- Previous query: assign a; Select a such that Affects*(a, 10)

#### Average
- Current run: 1.474 (↓ -0.15)
- Previous run: 1.624
----

### AffectsT_2
#### Overall statistics
- Total time 22.583 (previously 25.61)
- 15 queries, (previously 15)

#### Maximum
- Current run: 1.953 (↑ 0.065)
- Current query: assign a; Select a such that Affects*(13, a)
- Previous run: 1.888
- Previous query: assign a; Select a such that Affects*(1, a)

#### Average
- Current run: 1.506 (↓ -0.201)
- Previous run: 1.707
----

### Basic
#### Overall statistics
- Total time 17.458 (previously 19.825)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.938 (↑ 0.077)
- Current query: assign a;  Select a pattern a(_, "a - b")
- Previous run: 1.861
- Previous query: variable var123; Select var123 such that Uses(5, var123)

#### Average
- Current run: 1.455 (↓ -0.197)
- Previous run: 1.652
----

### Boolean
#### Overall statistics
- Total time 14.944 (previously 17.909)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.525 (↓ -0.271)
- Current query: stmt s; Select BOOLEAN such that Follows(s, 2)
- Previous run: 1.796
- Previous query: stmt s; variable v; Select BOOLEAN such that Modifies(s, v)

#### Average
- Current run: 1.359 (↓ -0.269)
- Previous run: 1.628
----

### Calls
#### Overall statistics
- Total time 10.952 (previously 12.732)
- 8 queries, (previously 8)

#### Maximum
- Current run: 1.607 (↓ -0.109)
- Current query: procedure p; procedure q; Select p such that Calls(q, p)
- Previous run: 1.716
- Previous query: procedure p; procedure q; Select p such that Calls(q, p)

#### Average
- Current run: 1.369 (↓ -0.222)
- Previous run: 1.591
----

### condexpr1
#### Overall statistics
- Total time 1.413 (previously 1.424)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.413 (↓ -0.011)
- Current query: stmt s;  Select s
- Previous run: 1.424
- Previous query: stmt s;  Select s

#### Average
- Current run: 1.413 (↓ -0.011)
- Previous run: 1.424
----

### Follows
#### Overall statistics
- Total time 12.142 (previously 13.936)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.508 (↓ -0.18)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.688
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.349 (↓ -0.199)
- Previous run: 1.548
----

### Follows2
#### Overall statistics
- Total time 6.882 (previously 8.022)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.488 (↓ -0.336)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.824
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.376 (↓ -0.228)
- Previous run: 1.604
----

### Milestone_1
#### Overall statistics
- Total time 12.213 (previously 14.23)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.415 (↓ -0.306)
- Current query: assign a;  Select a pattern a(_, "a + b")
- Previous run: 1.721
- Previous query: variable v; Select v such that Modifies(2, v)

#### Average
- Current run: 1.357 (↓ -0.224)
- Previous run: 1.581
----

### Modifies
#### Overall statistics
- Total time 6.996 (previously 8.261)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.653 (↓ -0.081)
- Current query: variable v; stmt s; Select v such that Modifies(s, v)
- Previous run: 1.734
- Previous query: variable v; Select v such that Modifies(3, v)

#### Average
- Current run: 1.399 (↓ -0.253)
- Previous run: 1.652
----

### ModifiesP
#### Overall statistics
- Total time 5.611 (previously 6.536)
- 4 queries, (previously 4)

#### Maximum
- Current run: 1.527 (↓ -0.198)
- Current query: variable v; Select v such that Modifies("modifies3", v)
- Previous run: 1.725
- Previous query: variable v; Select v such that Modifies("modifies3", v)

#### Average
- Current run: 1.403 (↓ -0.231)
- Previous run: 1.634
----

### ModifiesP_2
#### Overall statistics
- Total time 7.416 (previously 7.964)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.599 (↓ -0.156)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.755
- Previous query: variable v; Select v such that Modifies(2, v)

#### Average
- Current run: 1.483 (↓ -0.11)
- Previous run: 1.593
----

### Multi-clause
#### Overall statistics
- Total time 16.252 (previously 20.544)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.505 (↓ -0.473)
- Current query: assign a; Select a such that Modifies(a, "b") such that Parent* (1,a) pattern a("b", _)
- Previous run: 1.978
- Previous query: assign a; Select a such that Modifies(a, "b") and Parent* (1,a) pattern a("b", _)

#### Average
- Current run: 1.354 (↓ -0.358)
- Previous run: 1.712
----

### Next
#### Overall statistics
- Total time 15.04 (previously 17.996)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.487 (↓ -0.423)
- Current query: stmt s; Select s such that Next(2, s)
- Previous run: 1.91
- Previous query: stmt s; Select s such that Next(4, s)

#### Average
- Current run: 1.367 (↓ -0.269)
- Previous run: 1.636
----

### Next_2
#### Overall statistics
- Total time 8.666 (previously 10.103)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.542 (↓ -0.259)
- Current query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)
- Previous run: 1.801
- Previous query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)

#### Average
- Current run: 1.444 (↓ -0.24)
- Previous run: 1.684
----

### Parent
#### Overall statistics
- Total time 8.161 (previously 9.34)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.527 (↓ -0.168)
- Current query: if if; stmt s; Select s such that Parent(s, if)
- Previous run: 1.695
- Previous query: if if; stmt s; Select s such that Parent(s, if)

#### Average
- Current run: 1.36 (↓ -0.197)
- Previous run: 1.557
----

### Parent_2
#### Overall statistics
- Total time 15.052 (previously 17.312)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.536 (↓ -0.207)
- Current query: stmt s; Select s such that Parent(s,2)
- Previous run: 1.743
- Previous query: stmt s; Select s such that Parent(s,2)

#### Average
- Current run: 1.368 (↓ -0.206)
- Previous run: 1.574
----

### Parentt
#### Overall statistics
- Total time 4.145 (previously 4.655)
- 3 queries, (previously 3)

#### Maximum
- Current run: 1.565 (↓ -0.194)
- Current query: stmt s; while w; Select s such that Parent*(s, w)
- Previous run: 1.759
- Previous query: stmt s; while w; Select s such that Parent*(s, w)

#### Average
- Current run: 1.382 (↓ -0.17)
- Previous run: 1.552
----

### Pattern
#### Overall statistics
- Total time 10.204 (previously 11.635)
- 7 queries, (previously 7)

#### Maximum
- Current run: 1.814 (↓ -0.237)
- Current query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")
- Previous run: 2.051
- Previous query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")

#### Average
- Current run: 1.458 (↓ -0.204)
- Previous run: 1.662
----

### PatternIf
#### Overall statistics
- Total time 2.986 (previously 3.319)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.557 (↓ -0.138)
- Current query: if ifs; Select ifs pattern ifs(_,_,_)
- Previous run: 1.695
- Previous query: if ifs; Select ifs pattern ifs(_,_,_)

#### Average
- Current run: 1.493 (↓ -0.166)
- Previous run: 1.659
----

### PatternWhile
#### Overall statistics
- Total time 2.988 (previously 3.612)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.55 (↓ -0.387)
- Current query: while w; Select w pattern w(_,_)
- Previous run: 1.937
- Previous query: while w; Select w pattern w(_,_)

#### Average
- Current run: 1.494 (↓ -0.312)
- Previous run: 1.806
----

### Tuple_clause
#### Overall statistics
- Total time 12.625 (previously 15.458)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.585 (↓ -0.501)
- Current query: assign a; variable v; Select <a, v> such that Modifies(a, v)
- Previous run: 2.086
- Previous query: variable v; procedure p, q, r; assign a; Select <p, q, r, v> such that Calls(p, q) and Calls(q, r) pattern a(v, _"x"_)

#### Average
- Current run: 1.403 (↓ -0.315)
- Previous run: 1.718
----

### Uses
#### Overall statistics
- Total time 12.878 (previously 14.161)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.7 (↓ -0.134)
- Current query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)
- Previous run: 1.834
- Previous query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)

#### Average
- Current run: 1.431 (↓ -0.142)
- Previous run: 1.573
----

### UsesP
#### Overall statistics
- Total time 8.426 (previously 9.634)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.57 (↓ -0.215)
- Current query: variable v; Select v such that Uses("uses3", v)
- Previous run: 1.785
- Previous query: variable v; Select v such that Uses("uses3", v)

#### Average
- Current run: 1.404 (↓ -0.202)
- Previous run: 1.606
----

### With
#### Overall statistics
- Total time 34.712 (previously 40.224)
- 25 queries, (previously 25)

#### Maximum
- Current run: 1.596 (↓ -0.179)
- Current query: procedure p; Select p with p.procName = "First"
- Previous run: 1.775
- Previous query:  Select BOOLEAN with 12 = 12

#### Average
- Current run: 1.388 (↓ -0.221)
- Previous run: 1.609
----


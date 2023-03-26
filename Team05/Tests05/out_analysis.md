### Global
#### Overall statistics
- Total time 324.064 (previously 252.422)
- 215 queries, (previously 215)

#### Maximum
- Current run: 7.824 (↑ 6.051)
- Current query: Basic - variable v; Select v such that Modifies(2, v)
- Previous run: 1.773
- Previous query: Parent_2 - stmt s; Select s such that Parent*(1,s)

#### Average
- Current run: 1.507 (↑ 0.333)
- Previous run: 1.174
----

### Affects
#### Overall statistics
- Total time 16.438 (previously 12.538)
- 11 queries, (previously 11)

#### Maximum
- Current run: 3.015 (↑ 1.513)
- Current query: assign a; Select a such that Affects(a, 8)
- Previous run: 1.502
- Previous query: assign a; Select a such that Affects(a, 8)

#### Average
- Current run: 1.494 (↑ 0.354)
- Previous run: 1.14
----

### AffectsT
#### Overall statistics
- Total time 14.697 (previously 12.104)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.713 (↑ 0.307)
- Current query: assign a; Select a such that Affects*(a, 10)
- Previous run: 1.406
- Previous query: assign a; Select a such that Affects*(a, 10)

#### Average
- Current run: 1.336 (↑ 0.236)
- Previous run: 1.1
----

### AffectsT_2
#### Overall statistics
- Total time 21.113 (previously 16.253)
- 15 queries, (previously 15)

#### Maximum
- Current run: 1.776 (↑ 0.531)
- Current query: assign a; Select a such that Affects*(15, a)
- Previous run: 1.245
- Previous query: assign a; Select a such that Affects*(1, a)

#### Average
- Current run: 1.408 (↑ 0.324)
- Previous run: 1.084
----

### Basic
#### Overall statistics
- Total time 31.343 (previously 13.905)
- 12 queries, (previously 12)

#### Maximum
- Current run: 7.824 (↑ 6.403)
- Current query: variable v; Select v such that Modifies(2, v)
- Previous run: 1.421
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 2.612 (↑ 1.453)
- Previous run: 1.159
----

### Boolean
#### Overall statistics
- Total time 14.793 (previously 12.38)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.503 (↑ 0.228)
- Current query: stmt s; Select BOOLEAN such that Follows(s, _)
- Previous run: 1.275
- Previous query: stmt s; Select BOOLEAN such that Follows(s, _)

#### Average
- Current run: 1.345 (↑ 0.22)
- Previous run: 1.125
----

### Calls
#### Overall statistics
- Total time 10.74 (previously 9.352)
- 8 queries, (previously 8)

#### Maximum
- Current run: 1.494 (↑ 0.156)
- Current query: procedure p; procedure q; Select p such that Calls(q, p)
- Previous run: 1.338
- Previous query: procedure p; procedure q; Select p such that Calls(q, p)

#### Average
- Current run: 1.343 (↑ 0.174)
- Previous run: 1.169
----

### condexpr1
#### Overall statistics
- Total time 1.575 (previously 1.216)
- 1 queries, (previously 1)

#### Maximum
- Current run: 1.575 (↑ 0.359)
- Current query: stmt s;  Select s
- Previous run: 1.216
- Previous query: stmt s;  Select s

#### Average
- Current run: 1.575 (↑ 0.359)
- Previous run: 1.216
----

### Follows
#### Overall statistics
- Total time 13.216 (previously 10.741)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.572 (↑ 0.134)
- Current query: stmt s;  Select s such that Follows*(s, 7)
- Previous run: 1.438
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.468 (↑ 0.275)
- Previous run: 1.193
----

### Follows2
#### Overall statistics
- Total time 8.219 (previously 5.765)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.948 (↑ 0.675)
- Current query: stmt s;  Select s such that Follows(s,2)
- Previous run: 1.273
- Previous query: stmt s;  Select s such that Follows(s,2)

#### Average
- Current run: 1.644 (↑ 0.491)
- Previous run: 1.153
----

### Milestone_1
#### Overall statistics
- Total time 12.434 (previously 11.11)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.512 (↑ 0.123)
- Current query: stmt s; Select s such that Parent(s, 9)
- Previous run: 1.389
- Previous query: assign a;  Select a pattern a(_, "a + b")

#### Average
- Current run: 1.382 (↑ 0.148)
- Previous run: 1.234
----

### Modifies
#### Overall statistics
- Total time 7.646 (previously 5.575)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.808 (↑ 0.537)
- Current query: variable v; stmt s; Select v such that Modifies(s, v)
- Previous run: 1.271
- Previous query: variable v; stmt s; Select v such that Modifies(s, v)

#### Average
- Current run: 1.529 (↑ 0.414)
- Previous run: 1.115
----

### ModifiesP
#### Overall statistics
- Total time 5.54 (previously 4.59)
- 4 queries, (previously 4)

#### Maximum
- Current run: 1.496 (↑ 0.279)
- Current query: variable v; Select v such that Modifies("modifies3", v)
- Previous run: 1.217
- Previous query: variable v; Select v such that Modifies("modifies3", v)

#### Average
- Current run: 1.385 (↑ 0.238)
- Previous run: 1.147
----

### ModifiesP_2
#### Overall statistics
- Total time 6.7 (previously 5.784)
- 5 queries, (previously 5)

#### Maximum
- Current run: 1.508 (↑ 0.158)
- Current query: variable v; Select v such that Modifies(1, v)
- Previous run: 1.35
- Previous query: variable v; Select v such that Modifies(1, v)

#### Average
- Current run: 1.34 (↑ 0.183)
- Previous run: 1.157
----

### Multi-clause
#### Overall statistics
- Total time 16.77 (previously 14.456)
- 12 queries, (previously 12)

#### Maximum
- Current run: 1.747 (↑ 0.332)
- Current query: assign a; Select a such that Modifies (a, "b") and Parent* (1,a) and Next(3,a)
- Previous run: 1.415
- Previous query: assign a; Select a such that Modifies(a, "b") such that Parent* (1,a) pattern a("b", _)

#### Average
- Current run: 1.397 (↑ 0.192)
- Previous run: 1.205
----

### Next
#### Overall statistics
- Total time 14.8 (previously 13.307)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.509 (↑ 0.051)
- Current query: stmt stmt; Select stmt such that Next(18, stmt)
- Previous run: 1.458
- Previous query: stmt stmt; Select stmt such that Next(18, stmt)

#### Average
- Current run: 1.345 (↑ 0.135)
- Previous run: 1.21
----

### Next_2
#### Overall statistics
- Total time 8.234 (previously 7.672)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.531 (↑ 0.088)
- Current query: stmt s1, s2; Select s1 such that Next(s1, s2) and Next(s2, s1)
- Previous run: 1.443
- Previous query: stmt s1, s2, s3, s4; Select s1 such that Next(s1, s2) and Next(s2, s3) such that Next(s3, s4)

#### Average
- Current run: 1.372 (↑ 0.093)
- Previous run: 1.279
----

### Parent
#### Overall statistics
- Total time 8.622 (previously 7.171)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.648 (↑ 0.175)
- Current query: if if; stmt s; Select s such that Parent(s, if)
- Previous run: 1.473
- Previous query: if if; stmt s; Select s such that Parent(s, if)

#### Average
- Current run: 1.437 (↑ 0.242)
- Previous run: 1.195
----

### Parent_2
#### Overall statistics
- Total time 16.309 (previously 13.986)
- 11 queries, (previously 11)

#### Maximum
- Current run: 1.655 (↓ -0.118)
- Current query: stmt s; Select s such that Parent(s,2)
- Previous run: 1.773
- Previous query: stmt s; Select s such that Parent*(1,s)

#### Average
- Current run: 1.483 (↑ 0.212)
- Previous run: 1.271
----

### Parentt
#### Overall statistics
- Total time 4.366 (previously 3.72)
- 3 queries, (previously 3)

#### Maximum
- Current run: 1.573 (↑ 0.217)
- Current query: stmt s; while w; Select s such that Parent*(s, w)
- Previous run: 1.356
- Previous query: stmt s; while w; Select s such that Parent*(s, w)

#### Average
- Current run: 1.455 (↑ 0.215)
- Previous run: 1.24
----

### Pattern
#### Overall statistics
- Total time 12.312 (previously 8.816)
- 7 queries, (previously 7)

#### Maximum
- Current run: 2.494 (↑ 0.979)
- Current query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")
- Previous run: 1.515
- Previous query: assign assign; variable v; Select assign pattern assign(v, "x + y * z")

#### Average
- Current run: 1.759 (↑ 0.5)
- Previous run: 1.259
----

### PatternIf
#### Overall statistics
- Total time 2.792 (previously 2.314)
- 2 queries, (previously 2)

#### Maximum
- Current run: 1.444 (↑ 0.221)
- Current query: if ifs; Select ifs pattern ifs(_,_,_)
- Previous run: 1.223
- Previous query: if ifs; Select ifs pattern ifs(_,_,_)

#### Average
- Current run: 1.396 (↑ 0.239)
- Previous run: 1.157
----

### PatternWhile
#### Overall statistics
- Total time 3.768 (previously 2.615)
- 2 queries, (previously 2)

#### Maximum
- Current run: 2.085 (↑ 0.705)
- Current query: while w; Select w pattern w(_,_)
- Previous run: 1.38
- Previous query: while w; Select w pattern w(_,_)

#### Average
- Current run: 1.884 (↑ 0.576)
- Previous run: 1.308
----

### Tuple_clause
#### Overall statistics
- Total time 15.412 (previously 10.612)
- 9 queries, (previously 9)

#### Maximum
- Current run: 2.759 (↑ 1.418)
- Current query: variable v; procedure p, q, r; assign a; Select <p, q, r, v> such that Calls(p, q) and Calls(q, r) pattern a(v, _"x"_)
- Previous run: 1.341
- Previous query: assign a; variable v; Select <a, v> such that Modifies(a, v)

#### Average
- Current run: 1.712 (↑ 0.533)
- Previous run: 1.179
----

### Uses
#### Overall statistics
- Total time 14.213 (previously 11.054)
- 9 queries, (previously 9)

#### Maximum
- Current run: 1.828 (↑ 0.328)
- Current query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)
- Previous run: 1.5
- Previous query: variable legend27; stmt mobileGame; Select legend27 such that Uses(mobileGame, legend27)

#### Average
- Current run: 1.579 (↑ 0.351)
- Previous run: 1.228
----

### UsesP
#### Overall statistics
- Total time 8.61 (previously 6.863)
- 6 queries, (previously 6)

#### Maximum
- Current run: 1.508 (↑ 0.248)
- Current query: variable v; Select v such that Uses("uses2", v)
- Previous run: 1.26
- Previous query: variable v; Select v such that Uses("uses2", v)

#### Average
- Current run: 1.435 (↑ 0.291)
- Previous run: 1.144
----

### With
#### Overall statistics
- Total time 33.402 (previously 28.523)
- 25 queries, (previously 25)

#### Maximum
- Current run: 1.65 (↑ 0.323)
- Current query: stmt s; constant c; Select s with s.stmt# = c.value
- Previous run: 1.327
- Previous query: stmt s; constant c; Select s with s.stmt# = c.value

#### Average
- Current run: 1.336 (↑ 0.195)
- Previous run: 1.141
----


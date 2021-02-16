# Sportsmen

Each athlete has a unique number written on his jersey. The athletes take turns leaving the dressing room and must line up in the stadium. The coach tells each athlete exiting the number of the athlete in front of whom you need to stand. If the athlete with the named number is not on the field, then you need to stand at the end of the line.

In the standard input, a natural number n, not exceeding 100,000, is first given - the number of athletes. Then there are n pairs of non-negative integers not exceeding 100000. The first number in the pair is the number of the next outgoing athlete. The second number in the pair is the number of the athlete in front of whom the current one should stand.

Print to standard output the athlete numbers in the order they appear on the field.

Time limit - 0.8 sec.
Example

## Input
```
5
42 0
17 42
13 0
123 42
5 13
```
## Output
```
17
123
42
5
13

```

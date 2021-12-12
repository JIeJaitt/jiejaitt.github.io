# B - Power Socket

Time Limit: 2 sec / Memory Limit: 1024 MB

Score : 200 points

## Problem Statement
Takahashi's house has only one socket.
Takahashi wants to extend it with some number of power strips, each with A sockets, into B or more empty sockets.
One power strip with A sockets can extend one empty socket into A empty sockets.
Find the minimum number of power strips required.

## Constraints
- All values in input are integers.
- 2≤A≤20
- 1≤B≤20

## Input
Input is given from Standard Input in the following format:
```bash
A B
```
## Output
Print the minimum number of power strips required.

## Sample Input 1
```bash
4 10
```
## Sample Output 1
```bash
3
```
3 power strips, each with 4 sockets, extend the socket into 10 empty sockets.

## Sample Input 2
```bash
8 9
```

## Sample Output 2
```bash
2
```

## Sample Input 3
```bash
8 8
```

## Sample Output 3
```bash
1
```
# Project: Strands

## Context
_Text below is the instructions for Program 3 of Fall 2025 COP3502C (Computer Science 1). Uploaded to Github for archival and future reference purposes only. DO NOT USE CODE WITHOUT PERMISSION._

## Objective
1) Give practice with linked lists
2) Give practice with functions in C

## Strands Queries - Modified

In the original NY Times Strands game, users are given a 2D grid of letters, and are asked to
partition the grid into "strands", where each strand is a path formed by starting at one letter and
moving in one of the eight directions (NW, N, NE, W, E, SW, S, SE) to get to the next letter,
continuing the process until each letter in the grid is part of precisely one word.

Here is an example puzzle with a theme (school related terms):
```
  C↓  E→  X↓  G   R→    E
  O↓  M  ←A   N↑  ←I  ↑←U
  L→  L→  E↓  D→↑ ↓←E  T↑
  R   Q↓  G↓  A↑  R↑  C↑
  E↑  U→↓  E  C→  O↓  E↑
  P↑  M→↓  I→  Z  U↓  L↑
  A↑  O↑  E→  W→↓ R→  S↓
  P↑  H↑  K  ←R  ←O    E
```

A few of the squares are start squares (no incoming arrows), which store the first letter of a word,
and few other squares are end squares (no outgoing arrys), which store the last letter of a word.

For this program, you'll be given information about the board and be required to store the board as
a 2D array of pointers to structs, each of which are nodes for a doubly linked list. For each cell,
you'll be given both the where the next letter for that word is and the previous letter, if those exist.
Thus, each word will be stored in a doubly linked list, while each of the physical nodes will reside
in an indexed array.

Note: In the illustration above, only next pointers are shown with arrows. (The previous pointers
can be inferred.)

## Problem
Given the initial structure of the board as described above, write a program that builds the structure
in the manner designated (there are many ways to store this data differently, but the point of the
assignment is to practice linked lists), then handles the following query types in sequence

1. Given a position in the grid (0-based row and column numbers), prints out the word that grid
position is part of in the current Strands configuration.
2. Given a position in the grid, reverse the word that grid position is part of.
3. Given a position in the grid that is an ending position, as well as an adjacent position that is a
starting position for a different word, concatenate those two words together.

## Required Data Structures/Constants/Variables
You must use the following doubly linked list struct:
```
typedef struct dllnode {
  char ch;
  struct dllnode* prev;
  struct dllnode* next;
} dllnode;
```
In your main function, please declare the following variables to store the grid:
```
int numRows;
int numCols;
dllnode*** strandsGrid;
```
There will be 8 possible directions of movement, using the following "codes":

  NW = 0, N = 1, NE = 2, W = 3, E = 4, SW = 5, S = 6, SE = 7.
  
These codes correspond to the following two constant arrays and directions for the previous and
next pointers, which you must use:
```
const int NUMDIR = 8;
const int NULLPTR = -1;
const int DR[NUMDIR] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DC[NUMDIR[ = {-1, 0, 1, -1, 1, -1, 0, 1};
```
The reason you will need to use these fixed arrays is that the input will refer to the link directions
for both the previous letter and the next letter using the 0 through 7 codes provided above. If a
pointer is NULL, then the code of -1 will be used.

## Input
The first line of input contains two space separated integers, r (2 ≤ r ≤ 100), and c (2 ≤ c ≤ 100),
the number of rows and columns, respectively, in the input grid.

The following r lines will each contain c lowercase letters. The ith of these lines will indicate the
contents of row i (0 ≤ i < r), from left to right. The indexing to the grid will be 0-based, so the first
character in each row is column 0, the second character in each row is column 1, etc.

The second set of r lines will each contain c space separated integers, each in between -1 and 7,
inclusive, representing the direction for the next pointer from that letter to the next letter in the
word it is part of. If this number is in between 0 and 7, inclusive, then a next letter exists, and it's
in the relative direction specified previously by the direction codes. Namely, the DR/DC arrays
store the relative movement to get to the next letter in this index location. If this number is -1, then
this position in the grid represents the last letter in the word it forms in the Strands configuration.

The third set of r lines will each contain c space separated integers, each in between -1 and 7,
inclusive, representing the direction for the previous pointer from that letter to the previous letter
in the word it is part of. If this number is in between 0 and 7, inclusive, then a previous letter exists,
and it's in the relative direction specified previously by the direction codes. If this number is -1,
then this position in the grid represents the first letter in the word it forms in the Strands
configuration.

The next line of input contains a single positive integer, q (1 ≤ q ≤ 1000), representing the number
of queries that follow, each query on a single line.

There are three query types:
1. Print the word that the node in a particular grid square is part of.
2. Reverse the word that the node in a particular grid square is part of.
3. Given the position of the last letter in one word, and an adjacent position that is the starting letter
in a different word, concatenate the word in the first position to the word in the second listed
position.

For each query, the first integer, t (1 ≤ t ≤ 3), will represent the query type corresponding to the
numeric list above.

If t is 1 or 2, then the line will contain 2 more space-separated integers, y (0 ≤ y < r), and x (0 ≤ x
< c), respectively, representing the 0-based row number and 0-based column number of the grid
square for the query.

If t is 3, then the line will contain 4 more space separated integers, y1 (0 ≤ y1 < r), x1 (0 ≤ x1 < c),
y2 (0 ≤ y2 < r), and x2 (0 ≤ x2 < c), respectively, where y1 and x1 are the row and column numbers,
of the last grid square in the first word for the query, and y2 and x2 are the row and column numbers,
of the first grid square in the second word for the query. In addition, it will be guaranteed that these
two positions are adjacent in the grid.

## Output
For each query of type 1, on a line by itself, print out the word that grid position is part of. No
output should be produced for queries of types 2 or 3.

#### Sample Input
```
8 6
cexgre
omaniu
lledet
rqgarc
euecoe
pmiaul
aoewrs
phkroe
6 4 6 -1 4 -1
6 -1 3 1 3 0
4 4 6 2 5 1
-1 6 6 1 1 1
1 7 -1 4 6 1
1 7 4 -1 6 1
1 1 4 7 4 6
1 1 -1 3 3 -1
-1 -1 3 6 7 3
1 4 1 4 5 6
1 3 3 6 6 6
6 -1 1 2 -1 6
6 1 1 -1 3 6
6 6 0 3 1 -1
6 6 0 3 1 3
-1 -1 4 4 0 1
10
1 1 0
1 6 2
1 5 4
2 7 4
1 7 1
3 4 2 4 3
1 2 2
1 6 5
1 4 0
1 2 4
```

#### Sample Output
```
college
homework
course
krowemoh
collegecourse
collegecourse
paper
reading
```

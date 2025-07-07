# n-queens

## Problem/Puzzle

  Try to place n queens on an n*n-chess board, so that no queen attacks another queen.
  Queens attack horizontal, vertical and in a diagonal.

## Usage

```sh
gcc -o main main.c && ./main <n>
```
Command requires gcc.
Should work with other compilers and on other platforms.

## Sample output

For n = 14 (ran in 1.38ms):  
```
q . . . . . . . . . . . . . 
. . q . . . . . . . . . . . 
. . . . q . . . . . . . . . 
. . . . . . q . . . . . . . 
. . . . . . . . . . . q . . 
. . . . . . . . . q . . . . 
. . . . . . . . . . . . q . 
. . . q . . . . . . . . . . 
. . . . . . . . . . . . . q 
. . . . . . . . q . . . . . 
. q . . . . . . . . . . . . 
. . . . . q . . . . . . . . 
. . . . . . . q . . . . . . 
. . . . . . . . . . q . . . 
```

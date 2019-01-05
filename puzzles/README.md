Sample level file:

```
5 5

R.G.Y
..B.O
.....
.G.Y.
.RBO.
```

On the first line, the first number is the number of rows, and the second number is the number of columns (the board need not be square).

To represent a flow source of a given color, use the color character below.

To represent a blank space, use any non-whitespace character (I would recommend something like `.` or `+`).

Sample state/solution file:

```
5 5

BRRRO
BR.YO
BRYOO
BROOG
BBG..
```

State files follow the same rules as level files, except some of the blank squares can be replaced by colors to represent the flows.

Available colors:

| Letter | Color        |
|--------|--------------|
| R      | red          |
| B      | blue         |
| Y      | yellow       |
| G      | green        |
| O      | orange       |
| C      | cyan         |
| M      | magenta      |
| m      | maroon       |
| P      | purple       |
| A      | gray         |
| W      | white        |
| g      | bright green |
| T      | tan          |
| b      | dark blue    |
| c      | dark cyan    |
| p      | pink         |
# rubiks-cube-cracker

A virtual Rubik's Cube with a built-in optimal solver written in C++ and
rendered with OpenGL.  The optimal solver can solve any scrambled cube in 20
moves or fewer using Korf's algorithm.  Although the program is quite
performant--more so than other optimal solvers that were tested--it takes
awhile to generate optimal solutions for some scrambles.  So for the impatient,
there's also a Thistlethwaite solver that rapidly solves any scramble.

[A video demonstration is available on
YouTube.](https://www.youtube.com/watch?v=ZtlMkzix7Bw&feature=youtu.be)

### Rubik's Cube Notation

The documentation below describes the program and the various algorithms that
are implemented.  Standard twist notation is used: U, L, F, R, B and D desribe
90-degree clockwise twists of the up, left, front, right, back, and down faces,
respectively.  Adding an apostrophe indicates a counter-clockwise twist, so U'
means twist the up face 90-degrees counter-clockwise.  Adding a 2 to a move
indicates a 180-degree twist; F2 means to twist the front face twice.  With 6
faces and three types of moves per face, there are a total of 18 face twists.
There's more information, [here](https://ruwix.com/the-rubiks-cube/notation/).

A Rubik's Cube is made up of cubies (the cubies are the small cubes with
stickers on them).  There are corner cubies, which are the cubies with three
stickers.  Edge cubies are the cubies with two stickers.  And there are center
cubies, which are stationary and cannot be moved with the 18 twists described
above.

### Building and Running the Application

Reference the [BUILDING.md](BUILDING.md) document.  The program was developed
under Linux and compiles with g++, but has also been tested and compiled under
Windows using Mingw (the 64-bit version).

### Keys

Twist the faces of the cube using these keys: `U`, `L`, `F`, `R`, `B`, and `D`
for up, left, front, right, back, and down twists, respectively.  Hold `SHIFT`
for prime (counter-clockwise) moves, or `ALT` for double (180-degree) twists.

Rotate the entire cube using the arrow keys: `UP`, `DOWN`, `LEFT`, and `RIGHT`
for X and Y rotations.  Press `Z` for a Z rotation (hold `SHIFT` for prime).

For slice moves, use `M`, `E`, and `S` for the respective slices.

Rapidly solve a scrambled cube using Thistlethwaite's algorithm by pressing
`F1`.

To solve a scrambled cube optimally using the Korf algorithm, press `F2`.

Apply a 100-move scramble by pressing `F5`.

### The Display

OpenGL is used to render the Rubik's Cube.  The renderer was written from
scratch.  Quaternions are used to rotate the faces, and there's a cool SLERP
animation.  The lighting is a custom implementation of the Phong reflection
model using a single distance light and some shiny materials.  The reflection
model can be seen clearly when the entire cube is rotated using the arrow keys.

Shading is also custom, with procedurally-generated cubie stickers.  The
stickers intentionally have some imperfections, which is supposed to look like
smudges (in my opinion a Rubik's Cube aught to be used!).

The cube also has a levitation effect, which is modeled after levitating
characters in the original EverQuest game.  Sorry if that makes you nauseous.

### Optimal Solver

The optimal solver is an implementation of [Richard Korf's
algorithm](https://www.cs.princeton.edu/courses/archive/fall06/cos402/papers/korfrubik.pdf),
with minor variations, and can solve any cube in 20 moves or fewer.  It works
by searching for solutions using an iterative-deepening depth-first search
combined with A\* (IDA\*).

Iterative-deepening depth-first search (IDDFS) is a tree-traversal algorithm.
Like a breadth-first search (BFS), IDDFS is guaranteed to find an optimal path
from the root node of a tree to a goal node, but it uses much less memory than
a BFS.  Consider a cube as the root of a tree, i.e. depth 0.  Applying each
possible twist of the cube (left, front, right, etc.) brings the cube to a new
node at depth 1, any of which may be the solved state.  If not, applying each
combination of two moves (left-up, left-down, etc.) may solve the cube.  That
continues until a solution is found.

IDDFS alone would take far too much time to solve most scrambled cubes.  There
are 18 possible face twists of the cube, a large branching factor.  After the
first set of twists, some of the moves can be pruned.  For example, turning the
same face twice is redundant: F F is the same as F2; F F' is the same as no
move; F F2 is the same as F'; and so on.  Also, some moves are commutative: F B
is the same as B F; U2 D is the same as D U2; etc.  But even after pruning the
branching factor is over 13, so searching for a solution with raw IDDFS would
take thousands of years on a modern computer!  Here's where A\* comes in.

A\* is a graph-traversal algorithm that's used to find the optimal path from
one node of a graph to another, and, given that a tree is just a graph, it can
be combined with IDDFS.  A\* uses a heuristic to guide the search.  A heuristic
provides an estimated distance (number of moves) from one node (a scrambled
state) to another (the solved state).  For A\* to operate
correctly--specifically, to guarantee an optimal path--the heuristic must never
overestimate the distance.  IDA\* works the same way as IDDFS, but rather than
starting at depth 0 it queries a heuristic for an estimated distance to the
goal state and starts at that depth.  During the search, if the estimated
distance from a node to the goal state exceeds the depth, then the node is
pruned from the tree.  In other words, the heuristic is used to see if moving
from one state of the cube to another brings the cube closer to or farther away
from the solved state.

Richard Korf proposed using a series of pattern databases as a heuristic for
the Rubik's Cube.  One of the databases stores the number of moves required to
solve the corner pieces of any cube.  There are 8 corner cubies, and each can
occupy any of the 8 positions, so there are 8! possible permutations.  Each of
the corner pieces can be oriented in 3 different ways--any of the three
stickers can face up, for example--but the orientations of 7 of the cubies
dictate the orientation of the 8th (by the [laws of the
cube](https://www.ryanheise.com/cube/cube_laws.html)).  Therefore, there are
3^7 possible ways the corners can be orientated.  Altogether then, there are 8!
\* 3^7 possible ways for the corners of the cube to be scrambled, and these
88,179,840 states can be iterated in a reasonable amount of time (30 minutes or
so).  All corner states can be reached in 11 moves or fewer, so each entry in
the corner pattern database can be stored in a nibble (4 bits).  On disk, the
corner pattern database occupies about 42MB.

Korf suggests two additional databases: one for 6 of the 12 edges, and another
for the other 6 edges.  Given that modern developer boxes have plenty of RAM,
this program uses two databases with 7 edges each.  7 edges can occupy 12
positions, so there are 12P7 (12! / (12-7)!) permutations.  Each corner can
be oriented in 2 ways, so there are 2^7 possible orientations of 7 edges.
Again, this is a small enough number of cube states to iterate over, and all
states can be reached in 10 moves or fewer.  Storing each entry in a nibble,
each of the 7-edge databases occupies about 244MB (12P7 \* 2^7 / 2 bytes).

This program uses one additional database that holds the permutations of the 12
edges.  It takes about 228MB (12! / 2 bytes).

Using larger edge databases and the additional edge permutation database
results in a huge speed increase.  Larger databases would result in an even
bigger performance increase, but it's easy to use an enormous amount of memory.
Adding just one more edge piece to the 7-edge database, for example, increases
the size of each database to roughly 2.4GB.

An implementation detail that Korf glazes over in his algorithm is how to
create indexes into these pattern databases.  That is, given a scrambled cube,
how to create a perfect hash of the corner or edge permutations.  To that end,
this program converts permutations to a factorial number system.  There's an
[algorithm](https://en.wikipedia.org/wiki/Factorial_number_system#Permutations)
on Wikipedia that's pretty simple, but it has quadratic complexity.  In
[another](https://www.aaai.org/Papers/AAAI/2005/AAAI05-219.pdf) of Korf's
papers, he describes a linear algorithm, and this program uses the linear
version.  This program was compared against
[another](https://github.com/brownan/Rubiks-Cube-Solver) optimal solver written
in C, and this program is significantly faster.  The main reason for the
improved performance is the linear algorithm that's used to convert
permutations to numbers in a factorial base (a.k.a. generating [Lehmer
codes](https://en.wikipedia.org/wiki/Lehmer_code_)).

### Quick Solver

The optimal solver can take a long time, especially for scrambles that take 18+
moves to solve.  As such, this program also includes an implementation of
Thistlethwaite's algorithm.  The algorithm implemented by this program can
solve any scrambed cube quickly in at most 46 moves, effectively instantaneously.  Thistlethwaite's
algorithm orignally had a maximum of 52 moves, but this implementation differs
slightly (details below).

The Thistlethwaite algorithm implementation also uses IDA\* with pattern
databases as heuristics.  It works by moving the cube from one "group" to
another, and each successive group is computationally easier to solve than its
predecessor.  Each transition from one group to the next uses a separate
pattern database, but unlike the databases used with Korf's algorithm, the
Thistlethwiate databases give the exact number of moves required to get to the
next group.

The initial group, group 0, is any scrambled cube.  Above it was mentioned that
each edge cubie can be in one of two orientations.  Well, it turns out that
edge pieces cannot be flipped if quarter turns of the front and back faces are
not used.  So, by moving the cube to a state wherein all 12 edge pieces are
correctly oriented, group 1, the cube can be solved _without_ using quarter
turns of the front or back faces.

Next, the cube is moved to a state such that all corners are correctly
oriented.  Also, four of the edges are moved to the correct slice: the
front-right, front-left, back-left, and back-right edges are placed in the E
slice.  This is group 2.  The branching factor is smaller when moving from
group 1 to group 2 because four of the moves (F, F', B, and B') are excluded.

Group 3 differs a bit from Thistlethwaite's original algorithm, wherein he uses
a series of preliminary moves to check how corner cubies are positioned within
their tetrads.  (Corners `{ULB, URF, DLF, DRB}` make up one tetrad, and `{URB,
ULF, DLB, DRF}` make up the other.)  This implementation employs [Stefan
Pochmann's
technique](https://www.stefan-pochmann.info/spocc/other_stuff/tools/solver_thistlethwaite/solver_thistlethwaite.txt)
and pairs up corners, ensuring that `{ULB, URF}`, `{DLF, DRB}`, `{URB, ULF}`,
and `{DLB, DRF}` are paired up within their respective tetrads.  At the same
time it makes the parity of the corners even, meaning that the corners can be
brought into the solved state with an even number of swaps.  (When corner
parity is even, edge parity is, too.)  Lastly, moving to group 3 ensures that
the M- and S-slice edges are positioned within their slices.  In group 2, all
the corners are oriented correctly, so moving to group 3 can be done without
quarter turns of L and R (10 permissible moves).

Moving from group 3 to the solved state uses only 6 moves: U2, F2, L2, R2, B2,
and D2.

| Group | Moves                                             | Database Size                 | Max Twists |
|:------|:--------------------------------------------------|:------------------------------|:-----------|
| G0    | <L,L',L2,R,R',R2,U,U',U2,D,D',D2,F,F',F2,B,B',B2> | 2^11=2,048                    | 7          |
| G1    | <L,L',L2,R,R',R2,U,U',U2,D,D',D2,F2,B2>           | 12C4\*3^7=1,082,565           | 10         |
| G2    | <L2,R2,U,U',U2,D,D',D2,F2,B2>                     | 8C2\*6C2\*4C2\*8C4\*2=352,800 | 14         |
| G3    | <L2,R2,U2,D2,F2,B2>                               | 4!\*4!\*4P2\*4!\*4P1=663,552  | 15         |

### Optimal Solver Stats

Below is a table of 10 100-move scrambles, along with the time and number of
moves required to solve each.  The scrambles are naive--random moves
_excluding_ prunable moves (two moves of the same face, etc.).

These numbers were generated on a Core i7 Sandy Bridge circa 2011, using
version 2.2.0 of the code.  The speed is improved in newer releases.

| Scramble                                                                                                                                                                                                                                                                                                    | Solution                                           | Solution Length (Twists) | Solution Time (Seconds) | Solution Time (Hours) |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------|--------------------------|-------------------------|-----------------------|
| U  R  L  D  R' B  U2 R  B' U  F' D' B' D2 R' L' B' F' U' R  L  U  B  U  R  D  R  B2 U  B  D2 R  L' U2 B2 U  L' F' R2 L  F2 R  U2 B  D  R' F  R  L  U2 B' R' B  U  L2 F2 R  U  R2 L  D2 U2 F2 R' L' D2 U  B2 F  U2 R' U2 R' L2 D  L' D2 B2 U' B2 U2 R' D  L' D' R' F  D  F  R2 L2 D2 B' U2 B  D  U' B  R2 U  | R B U2 L2 U F2 R2 F2 U F' U2 R2 F' U' F2 L B L'    | 18                       | 24152.5                 | 6.709027778           |
| U  R' B' F' R' D2 B2 D2 U  B2 F  D  U2 F2 D' L2 U2 F' L2 F  U  B2 D  R2 D2 U2 R2 L2 D  R2 D' L' B2 D2 F2 L2 D  F2 R2 U' F2 D2 F' D' B  L' D  F  U' B  U' F2 L' B' L2 D' R  L  B  F  U' L' B  D  B  R2 D  B' U' L  F' R2 L2 D' F2 D  U' L' B  R2 F  R  U' F  D  U2 L  B2 U2 F' L  F' U' F' L2 U  F  R2 U2 B' | B' L2 R' F U' B' R F' D2 B U2 D R U F B' L B U2    | 19                       | 88412.5                 | 24.55902778           |
| B2 R  B' D2 F  R' B' F' U2 L  B  U  B  L' U2 L  B2 R' F' L2 B2 L2 B2 U  L2 U' B' R  L  B' F2 L' U' F' U  B' U' F' D' R  F  R' U' L' U2 F' R  U  R' L' F2 R2 F' L2 U  B  L' B  F' D  L2 U  B  F  U  B' D2 F2 U  B  U' L' U  L2 B2 R' U2 R2 D2 B2 D' R  U2 F2 D  R' F2 L2 B  L' B2 U' R2 D  L2 F2 D2 F2 L' D' | U2 B' U F B U' R F' R2 F' U' R B' L D' L2 R U2     | 18                       | 25116.5                 | 6.976805556           |
| F' R  L' D' L' F  D' B' F' D' F  L' B  U' B' D  F2 D' L' F  U' L2 D' B2 U  B  R' U2 L' B2 D  F' L  D  F2 U2 B2 U' R' F' L  B' U' L' U2 R  D2 L  F  U2 L2 U' L  F2 U' L' F2 R' D2 F2 L' D  L2 U2 R  D2 U  F' U2 R2 L  U2 L  D  U  B  F  R2 U2 R  F' L  B  U' L  D  U2 L  D' U2 L' B' L' U2 L2 U  F2 R  F' D' | R F U' D' B2 R B2 D2 F' R' B U2 F R D2 R2 U2 D'    | 18                       | 9788.57                 | 2.719047222           |
| L2 F2 L  F  D2 F2 U2 R' D  F  U  L' F' R2 F2 L  F  L2 U2 L  U' B  U2 L  U2 L  D  R2 L' D' F2 D2 L2 B  F' U2 R' F  U2 F  D  F' D' R' B2 U' L2 D' U  F  D2 F2 D  B  F2 D2 L' U  B2 F2 L' B2 L' D' L2 U  B' R  L  D2 L2 B' U2 R  F  L  D  L' F2 D  L  F  R' F  D2 F' U2 R  U' L2 F' U2 R' U' B2 L2 U  R' B2 F' | U2 B L R' F2 U2 L' F2 R U' L2 F' L R' U L' R2 D'   | 18                       | 25470.5                 | 7.075138889           |
| B  L' D  R' F  R' L' B' R2 U2 B' U  R  L2 D2 F2 L' F' D  F2 D  U2 F2 D' L2 B2 L' F  L  U  B  U2 R' L2 F' R2 U' B' D  L2 D  R' D  R  U  R  B2 D' L  F  D' U  F' L2 F2 U2 R' B' F' U' F' U  L' D2 F2 L' F2 R' B2 F  L2 D' L' B2 D2 R2 D' L' B' L2 D2 U' B2 D' B  F  U2 R' F  U2 F2 U2 F  L' D2 F  L' F2 D  F' | B L U' L' U' B R U' B' U' L2 U' F R F B R U        | 18                       | 14478.4                 | 4.021777778           |
| F2 D2 B2 L2 D' B2 L2 U2 B' L' U2 B2 U  F  R  U' F  D2 L' F' L' B  D  F2 R2 U2 R2 D' U' L  F  U  B2 R2 L' B  D  U' L2 D  F2 L2 D  U  F' D2 L2 U  L  F  D' F' D2 B  U' L2 F2 R' U2 R2 B  U' B' D  R' B2 F' U' B' U  L2 F' L  B' D2 B2 R2 D2 R2 F  U' R' L2 D' F2 U  B' D  B  R' F' U  B' D2 U' L2 U2 L' D  L' | D' F2 U' R2 U L U2 B' L' R' U2 B' R' F2 U' F B2 R' | 18                       | 38683.1                 | 10.74530556           |
| L' U  B  D' L' F' D2 F2 R2 U' L' F' D  R' L  F2 D  R2 D  B  U' B2 D2 R  D2 F  U2 L' B2 U2 R' L2 U2 B2 L' B2 D' U' F2 U' F' D  R  B' L' B2 L2 D' U  L  B' D  U2 F2 L2 B  D2 L' D2 U' L' F' U' F2 D  L2 B2 R' F' U  R  D  B' F' U' L' F2 U  F2 D' F2 L2 B' U' L  U  L' B  D2 L' D  R' U2 F2 D' U' L  U  R2 L' | L' R2 D L' R2 B' D' F' R B R' U2 D' B2 L' F2 R'    | 17                       | 2212.68                 | 0.6146333333          |
| F' D  U2 R' L  B2 U2 L' B' D' L2 D  R  D  F  R  L  B' U2 L  D  F  R' B' D2 R  B2 L' U' F2 U2 F2 U' B  R  D  B' R' U  F  L' U  L2 B2 U' F  L' D' U' F' D2 U2 L' B  L' F' U  L  F2 R  D' L  U2 R2 F' L' U  F' L  U2 R2 D' B2 L  D' R  D  L  U  F  L  B' D  F2 L2 B  L  U  L2 U2 B2 R  L2 U' F' L' F2 R' B' U2 | D' B2 L F2 R' B2 L D2 F2 U F' U' R F' D L' U L2    | 18                       | 37914.8                 | 10.53188889           |
| B  F' L' F2 D  B  R' U2 L2 U' F' L2 B' R' U  B' U2 F2 U  F2 L  U2 B' R' F2 D' B2 R2 L2 B2 D' B  U2 R2 L' B2 U  F2 R2 D' L  B2 R' U2 R' L  U2 B' L2 D' L' F  L  B  U  F' L' F  D' U  L2 U' B2 R' D  F  R2 U  F2 U2 F  D2 L2 U  R2 U2 F2 U  F' D  B2 F2 R  U  R' F  D' U  L  F  R  D  U' L2 F2 D' F2 L  B2 L  | F D2 F' B D F L F U' F2 L2 B' L B R' F2 L' R'      | 18                       | 37511.7                 | 10.41991667           |

### References

Korf, Richard E.  [Finding Optimal Solutions to Rubik's Cube Using Pattern
Databases](https://www.cs.princeton.edu/courses/archive/fall06/cos402/papers/korfrubik.pdf).
This describes Korf's algorithm for solving the cube.

Korf, Richard E. et. al.  [Large-Scale Parallel Breadth-First
Search](https://www.aaai.org/Papers/AAAI/2005/AAAI05-219.pdf).  A linear
algorithm for generating sequential indexes into a pattern database using a
factorial number system.

Brown, Andrew.  [Rubik's Cube
Solver](https://github.com/brownan/Rubiks-Cube-Solver).  Used for speed
comparison.  Also used to compare optimal solutions.

Scherphuis, Jaap.  Thistlethwaite, Morwen. [Thistlethwaite's 52-move
algorithm](https://www.jaapsch.net/puzzles/thistle.htm).  Jaap has an overview
of the algorithm, as well as scans of a letter from Thistlethwaite.

Taylor, Peter.  [Indexing Edge Permutations for the Rubik's
Cube](https://cs.stackexchange.com/questions/107111/indexing-edge-permutations-for-the-rubiks-cube).
Peter was kind enough to help me with creating indexes for the 7-edge pattern
databases, which is a variation of the Lehmer code using partial permutations.

Rider, Conrad. [Edge Orientation
Detection](http://cube.crider.co.uk/zz.php?p=eoline#eo_detection).  This page
presents a simple algorithm for detecting the orientation of the edge pieces.

Heise, Ryan.  [Rubik's Cube
Theory](https://www.ryanheise.com/cube/cube_laws.html).  This has some advanced
discussion about reachable permutations and orienations of the cubies.

Pochmann, Stefan.  [Thistlethwaite 3x3
solver](https://www.stefan-pochmann.info/spocc/other_stuff/tools/solver_thistlethwaite/solver_thistlethwaite.txt).
Stefan Pochmann's Group 3 pairing method.

Enright, Brandon.  [What is the meaning of a “tetrad twist” in Thistlethwaite's
algorithm?](https://puzzling.stackexchange.com/questions/5402/what-is-the-meaning-of-a-tetrad-twist-in-thistlethwaites-algorithm).
Great visual representation of tetrads, accompanied by an explanation of size
of the corner coset in Group 3.

Scherphuis, Jaap.  [Way to calculate the total tetrad twist of a rubik's
cube](https://puzzling.stackexchange.com/questions/101256/way-to-calculate-the-total-tetrad-twist-of-a-rubiks-cube?noredirect=1&lq=1).
A manual algorithm for determining and encoding a tetrad twist.

# rubiks-cube-cracker

An OpenGL Rubik's Cube program with a built-in optimal solver written in C++.
The optimal solver can solve any scrambled cube in 20 moves or fewer using
Korf's algorithm.  Although the program is quite fast--faster than other
optimal solvers I tested--it takes awhile to generate optimal solutions for
some scrambles.  So for the impatient, there's also a Thistlethwaite solver
that rapidly solves any scramble.

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

To solve a scrambled cube optimally using the Korf algorithm, press `F2`.

Rapidly solve a scrambled cube using Thistlethwaite's algorithm by pressing
`F1`.

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
* 3^7 possible ways for the corners of the cube to be scrambled, and these
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
each of the 7-edge databases occupies about 244MB (12P7 * 2^7 / 2 bytes).

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
this program converts permutations to a factorial number system.  [There's an
algorithm on
Wikipedia](https://en.wikipedia.org/wiki/Factorial_number_system#Permutations)
that's pretty simple, but it has quadratic complexity.  In
[another](https://www.aaai.org/Papers/AAAI/2005/AAAI05-219.pdf) of Korf's
papers, he describes a linear algorithm, and this program uses the linear
version.  This program was compared against another optimal solver written in
C, and this program is significantly faster.  The main reason for the improved
performance is the linear algorithm that's used to convert permutations to
numbers in a factorial base (a.k.a. generating [Lehmer
codes](https://en.wikipedia.org/wiki/Lehmer_code_)).

### Quick Solver

The optimal solver can take a long time, especially for scrambles that take 18+
moves to solve.  As such, this program also includes an implementation of
Thistlethwaite's algorithm which can solve any scrambed cube quickly in 52 or
fewer moves.

Like Korf's, Thistlethwaite's algorithm uses IDDFS, but no heuristic pattern
databases are used.  It works by moving the cube from one "group" to another,
and each successive "group" is computationally easier to solve than the last.

The initial group--group 0--is any scrambled cube.  Above it was mentioned that
each edge cubie can be in one of two orientations.  Well, it turns out that
edge pieces cannot be flipped if quarter turns of the front and back faces are
not used.  So, by moving the cube to a state wherein all 12 edge pieces are
correctly oriented--group 1--the cube can be solved _without_ using quarter
turns of the front or back faces.

Next, the cube is moved to a state such that all corners are correctly
oriented.  Also, four of the edges are moved to the correct slice: the
front-up, front-down, back-up, and back-down edges are placed in the M slice.
This is group 2.  The branching factor is smaller when moving from group 1 to
group 2 because four of the moves (F, F', B, and B') are excluded.

For group 3, all corners are moved to the correct oribit.  (A corner is in the
correct orbit if it can be moved to its home position with only 180-degree
twists.)  Also, each edge is moved to its home slice.  At that point, the cube
can be solved with only 180-degree twists.

Moving from group 3 to the solved state has a branching factor of only 6,
comprised of U2, F2, L2, R2, B2, and D2.

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


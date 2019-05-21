# rubiks-cube-cracker

An OpenGL Rubik's Cube program with a built-in optimal solver written in C++.
The optimal solver can solve any scrambled cube in 20 moves or fewer using
Korf's algorithm.  Although the program is quite fast--faster than other
optimial solvers I tested--it takes awhile to generate optimal solutions for
some scrambles.  So for the impatient, there's also a Thistlethwaite solver
that rapidly solves any scramble.

### Bulding and Running the Application

Reference the [BUILDING.md](BUILDING.md) document.  The program was developed
under Linux and compiles with g++, but has also been tested and compiled under
Windows using Mingw (the 64-bit version).

### Keys

Twist the faces of the cube using these keys: `U`, `L`, `F`, `R`, `B`, and `D`
for up, left, front, right, back, and down twists, respectively.  Hold `SHIFT`
  for prime (counter-clockwise) moves, or `ALT` for double (180-degree) twists.

Rotate the entire cube using the arrow keys: `UP`, `LEFT`, `DOWN`, and `RIGHT`.

For slice moves, use `M`, `E`, and `S` for the respective slices.

### The Display

OpenGL is used to render the Rubik's Cube.  The renderer was written from
scratch.  Quaternions are used to rotate the faces, and there's a cool SLERP
animation.  The lighting is a custom implementation of the Phong reflection
model using a single distance light and some shiny materials.  The reflection
model can be seen clearly when the entire cube is rotated using the arrow keys.

Shading is also custom, with procedurally-generated cubie stickers.  The
stickers intentionally have some imperfections, which is supposed to look like
smudges (in my opinion, a Rubik's Cube aught to be used!).

The cube also has a levitation effect, which is modeled after levitating
characters in the original EverQuest game.  Sorry if that makes you nauseous.

### Optimal Solver


#include "GoalG3_Permute_Corners.h"

namespace busybin
{
  /**
   * Convert a permutation of the corners to a string.
   * @param cube The cube.
   */
  string GoalG3_Permute_Corners::permToString(const RubiksCubeModel& cube) const
  {
    char colors[] = {'W', 'G', 'R', 'B', 'O', 'Y'};

    COLOR ULB = cube.get(FACE::UP,    0, 0);
    COLOR LUB = cube.get(FACE::LEFT,  0, 0);
    COLOR BUL = cube.get(FACE::BACK,  0, 2);

    COLOR ULF = cube.get(FACE::UP,    2, 0);
    COLOR LUF = cube.get(FACE::LEFT,  0, 2);
    COLOR FUL = cube.get(FACE::FRONT, 0, 0);

    COLOR URB = cube.get(FACE::UP,    0, 2);
    COLOR RUB = cube.get(FACE::RIGHT, 0, 0);
    COLOR BUR = cube.get(FACE::BACK,  0, 0);

    COLOR URF = cube.get(FACE::UP,    2, 2);
    COLOR RUF = cube.get(FACE::RIGHT, 0, 0);
    COLOR FUR = cube.get(FACE::FRONT, 0, 2);

    COLOR DLB = cube.get(FACE::DOWN,  2, 0);
    COLOR LDB = cube.get(FACE::LEFT,  2, 0);
    COLOR BDL = cube.get(FACE::BACK,  2, 2);

    COLOR DLF = cube.get(FACE::DOWN,  0, 0);
    COLOR LDF = cube.get(FACE::LEFT,  2, 2);
    COLOR FDL = cube.get(FACE::FRONT, 2, 0);

    COLOR DRB = cube.get(FACE::DOWN,  2, 2);
    COLOR RDB = cube.get(FACE::RIGHT, 2, 2);
    COLOR BDR = cube.get(FACE::BACK,  0, 2);

    COLOR DRF = cube.get(FACE::DOWN,  0, 2);
    COLOR RDF = cube.get(FACE::RIGHT, 2, 0);
    COLOR FDR = cube.get(FACE::FRONT, 2, 2);



    /*COLOR UL = cube.get(FACE::UP,    1, 0);
    COLOR LU = cube.get(FACE::LEFT,  0, 1);

    COLOR UR = cube.get(FACE::UP,    1, 2);
    COLOR RU = cube.get(FACE::RIGHT, 0, 1);

    COLOR DL = cube.get(FACE::DOWN,  1, 0);
    COLOR LD = cube.get(FACE::LEFT,  2, 1);

    COLOR DR = cube.get(FACE::DOWN,  1, 2);
    COLOR RD = cube.get(FACE::RIGHT, 2, 1);

    COLOR LB = cube.get(FACE::LEFT,  1, 0);
    COLOR BL = cube.get(FACE::BACK,  1, 2);

    COLOR LF = cube.get(FACE::LEFT,  1, 2);
    COLOR FL = cube.get(FACE::FRONT, 1, 0);

    COLOR RB = cube.get(FACE::RIGHT, 1, 2);
    COLOR BR = cube.get(FACE::BACK,  1, 0);

    COLOR RF = cube.get(FACE::RIGHT, 1, 0);
    COLOR FR = cube.get(FACE::FRONT, 1, 2);

    COLOR UF = cube.get(FACE::UP,    2, 1);
    COLOR FU = cube.get(FACE::FRONT, 0, 1);

    COLOR UB = cube.get(FACE::UP,    0, 1);
    COLOR BU = cube.get(FACE::BACK,  0, 1);

    COLOR DF = cube.get(FACE::DOWN,  0, 1);
    COLOR FD = cube.get(FACE::FRONT, 2, 1);

    COLOR DB = cube.get(FACE::DOWN,  2, 1);
    COLOR BD = cube.get(FACE::BACK,  2, 1);*/


    // Make a string out of the corner permutations.
    string perm = "";

    perm += colors[(unsigned)ULB];
    perm += colors[(unsigned)LUB];
    perm += colors[(unsigned)BUL];

    perm += colors[(unsigned)ULF];
    perm += colors[(unsigned)LUF];
    perm += colors[(unsigned)FUL];

    perm += colors[(unsigned)URB];
    perm += colors[(unsigned)RUB];
    perm += colors[(unsigned)BUR];

    perm += colors[(unsigned)URF];
    perm += colors[(unsigned)RUF];
    perm += colors[(unsigned)FUR];

    perm += colors[(unsigned)DLB];
    perm += colors[(unsigned)LDB];
    perm += colors[(unsigned)BDL];

    perm += colors[(unsigned)DLF];
    perm += colors[(unsigned)LDF];
    perm += colors[(unsigned)FDL];

    perm += colors[(unsigned)DRB];
    perm += colors[(unsigned)RDB];
    perm += colors[(unsigned)BDR];

    perm += colors[(unsigned)DRF];
    perm += colors[(unsigned)RDF];
    perm += colors[(unsigned)FDR];

    /*perm += colors[(unsigned)UL];
    perm += colors[(unsigned)LU];

    perm += colors[(unsigned)UR];
    perm += colors[(unsigned)RU];

    perm += colors[(unsigned)DL];
    perm += colors[(unsigned)LD];

    perm += colors[(unsigned)DR];
    perm += colors[(unsigned)RD];

    perm += colors[(unsigned)LB];
    perm += colors[(unsigned)BL];

    perm += colors[(unsigned)LF];
    perm += colors[(unsigned)FL];

    perm += colors[(unsigned)RB];
    perm += colors[(unsigned)BR];

    perm += colors[(unsigned)RF];
    perm += colors[(unsigned)FR];

    perm += colors[(unsigned)UF];
    perm += colors[(unsigned)FU];

    perm += colors[(unsigned)UB];
    perm += colors[(unsigned)BU];

    perm += colors[(unsigned)DF];
    perm += colors[(unsigned)FD];

    perm += colors[(unsigned)DB];
    perm += colors[(unsigned)BD];*/

    return perm;
  }


  /**
   * Solve the cube.
   * @param cube The cube.
   */
  bool GoalG3_Permute_Corners::isSatisfied(RubiksCubeModel& cube)
  {
    string perm = this->permToString(cube);

    if (this->perms.count(perm) == 0)
    {
      this->perms.insert(perm);
      //cout << this->perms.size() << " " << perm << endl;

      // There are 96 total permutations.
      if (this->perms.size() == 96)
        return true;
      /*if (this->perms.size() == 376820)
        return true;*/
    }

    return false;
  }

  /**
   * Check if the permutation of the cube's corners is one that can be achieved by only
   * 180-degree twists.
   * @cube The cube.
   */
  bool GoalG3_Permute_Corners::permutationExists(const RubiksCubeModel& cube) const
  {
    string perm = this->permToString(cube);
    return this->perms.count(perm) == 1;
  }

  /**
   * Describe the goal.
   */
  string GoalG3_Permute_Corners::getDescription() const
  {
    return "All permutations of corners in G3.";
  }
}

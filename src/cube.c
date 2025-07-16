#include <stdlib.h>
#include "3d.h"

struct obj_s cube;

void init_cube(void)
{
  cube.point = malloc(sizeof(struct empty_s));
  cube.point->posx = 0;
  cube.point->posy = 0;
  cube.point->posz = 0;
  cube.point->rtta = 0;
  cube.point->rttb = 0;
  cube.mesh = malloc(sizeof(struct mesh_s));
  cube.mesh->v_c = 24;
  cube.mesh->i_c = 36;
  cube.mesh->v = (signed char[]){
   -1,  1, -1,
    1,  1, -1,
    1, -1, -1,
   -1, -1, -1,
   -1,  1,  1,
    1,  1,  1,
    1, -1,  1,
   -1, -1,  1
  };
  cube.mesh->i = (char[]){
    0, 1, 2, 0, 2, 3,
    2, 1, 5, 2, 5, 6,
    3, 2, 6, 3, 6, 7,
    0, 3, 7, 0, 7, 4,
    1, 0, 4, 1, 4, 5,
    6, 5, 4, 6, 4, 7
  };
}

void free_cube(void)
{
  free(cube.point);
  free(cube.mesh);
}

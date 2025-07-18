#include <stdlib.h>
#include "3d.h"

int cubeposx = 0;
int cubeposy = 0;
int cubeposz = 0;
char cubertta = 0;
char cuberttb = 0;
int cubev[] = {
 -64,  64, -64,
  64,  64, -64,
  64, -64, -64,
 -64, -64, -64,
 -64,  64,  64,
  64,  64,  64,
  64, -64,  64,
 -64, -64,  64
};
char cubei[] = {
  0, 1, 2, 0, 2, 3,
  2, 1, 5, 2, 5, 6,
  3, 2, 6, 3, 6, 7,
  0, 3, 7, 0, 7, 4,
  1, 0, 4, 1, 4, 5,
  6, 5, 4, 6, 4, 7
};

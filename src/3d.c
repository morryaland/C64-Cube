#include <stdio.h>
#include "draw.h"
#include "3d.h"

__zp char tsin[] = {
  1, 26, 50, 75, 98, 121, 143, 163, 182, 198, 213, 226, 237, 245, 252, 255,
  255, 255, 252, 245, 237, 226, 213, 198, 182, 163, 143, 121, 98, 75, 50, 26
};

void look_at(struct empty_s *cam)
{
  char nvert, i, j, k;
  char sv[3][2];
  int v[3][3];
  for (i = 0; i < cube.mesh->i_c; i += 3) {
    for (j = 0; j < 3; j++) {
      nvert = cube.mesh->i[i+j] * 3;
      for (k = 0; k < 3; k++) {
        v[j][k] = cube.mesh->v[nvert+k] << 8;
      }
      rotate_v3(v[j], cube.point->rtta, cube.point->rttb);
      v[j][0] += cube.point->posx - cam->posx;
      v[j][1] += cube.point->posy - cam->posy;
      v[j][2] += cube.point->posz - cam->posz;
      rotate_v3(v[j], cam->rtta, cam->rttb);
      if (v[j][2] > 0) break;
      v[j][0] = (((long)v[j][0]) << 8)/v[j][2];
      if (v[j][0] <= -127 || v[j][0] >= 128)
        break;
      v[j][1] = (((long)v[j][1]) << 8)/v[j][2];
      if (v[j][1] <= -100 || v[j][1] >= 100)
        break;
      sv[j][0] = v[j][0] + 128;
      sv[j][1] = v[j][1] + 100;
    }
    triangle(sv[0][0], sv[0][1], sv[1][0], sv[1][1], sv[2][0], sv[2][1]);
  }
}

void rotate_v3(int v[3], char a, char b)
{
  long tx, ty, tz;
  int sin, cos;
  if (a) {
    ty = v[1];
    tz = v[2];
    sin = a&32 ? -tsin[a&31] : tsin[a&31];
    a += 16;
    cos = a&32 ? -tsin[a&31] : tsin[a&31];
    v[1] = (ty * cos + tz * sin) >> 8;
    v[2] = (tz * cos - ty * sin) >> 8;
  }
  if (b) {
    tx = v[0];
    tz = v[2];
    sin = b&32 ? -tsin[b&31] : tsin[b&31];
    b += 16;
    cos = b&32 ? -tsin[b&31] : tsin[b&31];
    v[0] = (tx * cos + tz * sin) >> 8;
    v[2] = (tz * cos - tx * sin) >> 8;
  }
}

/*
float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;						// evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	return y;
}
*/

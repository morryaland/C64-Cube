#include <stdlib.h>
#include <string.h>
#include "draw.h"
#include "3d.h"

signed char tsin[] = {
1, 7, 13, 19, 25, 31, 36, 41, 46, 50, 54, 57, 60, 62, 63, 64, 64, 64,
63, 62, 60, 57, 54, 50, 46, 41, 36, 31, 25, 19, 13, 7, 1, -6, -12, -18,
-24, -30, -35, -40, -45, -49, -53, -56, -59, -61, -62, -63, -64, -63,
-62, -61, -59, -56, -53, -49, -45, -40, -35, -30, -24, -18, -12, -6
};

void look_at_cam()
{
  char nvert, i, j;
  char sv[3][2];
  int v[3][3];
  for (i = 0; i < 36 /* cubei len */; i += 3) {
    for (j = 0; j < 3; j++) {
      nvert = cubei[i+j] * 3;
      v[j][0] = cubev[nvert];
      v[j][1] = cubev[nvert+1];
      v[j][2] = cubev[nvert+2];
      rotate_v3(v[j], cubertta, cuberttb);
      v[j][0] += cubeposx - camposx;
      v[j][1] += cubeposy - camposy;
      v[j][2] += cubeposz - camposz;
      rotate_v3(v[j], camrtta, camrttb);
      v[j][2] += 64;
      if (v[j][2] <= 0) break;
      v[j][0] = (v[j][0] << 6)/v[j][2];
      if (v[j][0] <= -127 || v[j][0] >= 128)
        break;
      v[j][1] = (v[j][1] << 6)/v[j][2];
      if (v[j][1] <= -100 || v[j][1] >= 100)
        break;
      sv[j][0] = 128 - v[j][0];
      sv[j][1] = 100 - v[j][1];
    }
    if (j == 3) {
#if LINE_MODE
      line(sv[0][0], sv[0][1], sv[1][0], sv[1][1]);
      line(sv[1][0], sv[1][1], sv[2][0], sv[2][1]);
      line(sv[2][0], sv[2][1], sv[0][0], sv[0][1]);
#else
      triangle(sv[0][0], sv[0][1], sv[1][0], sv[1][1], sv[2][0], sv[2][1]);
#endif
    }
  }
}

void rotate_v3(int v[3], char a, char b)
{
  int tx, ty, tz;
  signed char sin, cos;
  if (a) {
    ty = v[1];
    tz = v[2];
    sin = tsin[a&63];
    cos = tsin[(a+16)&63];
    v[1] = (ty * cos + tz * sin) >> 6;
    v[2] = (tz * cos - ty * sin) >> 6;
  }
  if (b) {
    tx = v[0];
    tz = v[2];
    sin = tsin[b&63];
    cos = tsin[(b+16)&63];
    v[0] = (tx * cos + tz * sin) >> 6;
    v[2] = (tz * cos - tx * sin) >> 6;
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

#include <string.h>
#include "draw.h"

#define BA BITMAP_ADDR
/* i in 0..199 */
/* 0x20 + ((i & 0xF8) * 40) + (i & 7) */
const unsigned int ylookup[] = {
BA+32,BA+33,BA+34,BA+35,BA+36,BA+37,BA+38,BA+39,BA+352,BA+353,BA+354,BA+355,BA+356,BA+357,BA+358,BA+359,BA+672,BA+673,BA+674,BA+675,BA+676,BA+677,BA+678,BA+679,BA+992,BA+993,BA+994,BA+995,BA+996,BA+997,BA+998,BA+999,BA+1312,BA+1313,BA+1314,BA+1315,BA+1316,BA+1317,BA+1318,BA+1319,BA+1632,BA+1633,BA+1634,BA+1635,BA+1636,BA+1637,BA+1638,BA+1639,BA+1952,BA+1953,BA+1954,BA+1955,BA+1956,BA+1957,BA+1958,BA+1959,BA+2272,BA+2273,BA+2274,BA+2275,BA+2276,BA+2277,BA+2278,BA+2279,BA+2592,BA+2593,BA+2594,BA+2595,BA+2596,BA+2597,BA+2598,BA+2599,BA+2912,BA+2913,BA+2914,BA+2915,BA+2916,BA+2917,BA+2918,BA+2919,BA+3232,BA+3233,BA+3234,BA+3235,BA+3236,BA+3237,BA+3238,BA+3239,BA+3552,BA+3553,BA+3554,BA+3555,BA+3556,BA+3557,BA+3558,BA+3559,BA+3872,BA+3873,BA+3874,BA+3875,BA+3876,BA+3877,BA+3878,BA+3879,BA+4192,BA+4193,BA+4194,BA+4195,BA+4196,BA+4197,BA+4198,BA+4199,BA+4512,BA+4513,BA+4514,BA+4515,BA+4516,BA+4517,BA+4518,BA+4519,BA+4832,BA+4833,BA+4834,BA+4835,BA+4836,BA+4837,BA+4838,BA+4839,BA+5152,BA+5153,BA+5154,BA+5155,BA+5156,BA+5157,BA+5158,BA+5159,BA+5472,BA+5473,BA+5474,BA+5475,BA+5476,BA+5477,BA+5478,BA+5479,BA+5792,BA+5793,BA+5794,BA+5795,BA+5796,BA+5797,BA+5798,BA+5799,BA+6112,BA+6113,BA+6114,BA+6115,BA+6116,BA+6117,BA+6118,BA+6119,BA+6432,BA+6433,BA+6434,BA+6435,BA+6436,BA+6437,BA+6438,BA+6439,BA+6752,BA+6753,BA+6754,BA+6755,BA+6756,BA+6757,BA+6758,BA+6759,BA+7072,BA+7073,BA+7074,BA+7075,BA+7076,BA+7077,BA+7078,BA+7079,BA+7392,BA+7393,BA+7394,BA+7395,BA+7396,BA+7397,BA+7398,BA+7399,BA+7712,BA+7713,BA+7714,BA+7715,BA+7716,BA+7717,BA+7718,BA+7719,
};
#undef BA

__zp char xbit[] = {
  0b10000000,
  0b01000000,
  0b00100000,
  0b00010000,
  0b00001000,
  0b00000100,
  0b00000010,
  0b00000001
};

inline void plot(char x, char y)
{
  ((char*)ylookup[y])[x & ~7] |= xbit[x & 7];
}
 
void line(char x1, char y1, char x2, char y2)
{
  char dx, dy;
  signed char xi, yi;
  int d, ai, bi;
  if (x1 < x2) {
    xi = 1;
    dx = x2 - x1;
  }
  else {
    xi = -1;
    dx = x1 - x2;
  }
  if (y1 < y2) {
    yi = 1;
    dy = y2 - y1;
  }
  else {
    yi = -1;
    dy = y1 - y2;
  }
  if (dx > dy) {
    ai = (dy - dx) * 2;
    bi = dy * 2;
    d = bi - dx;
    while (x1 != x2) {
      if (d > 0) {
        y1 += yi;
        d += ai;
      }
      else
        d += bi;
      x1 += xi;
      plot(x1, y1);
    }
  }
  else {
    ai = (dx - dy) * 2;
    bi = dx * 2;
    d = bi - dy;
    while (y1 != y2) {
      if (d > 0) {
        x1 += xi;
        d += ai;
      }
      else
        d += bi;
      y1 += yi;
      plot(x1, y1);
    }
  }
}

/*
void triangle(char x1, char y1, char x2, char y2, char x3, char y3)
{
#if LINE_MODE
  line(x1, y1, x2, y2);
  line(x2, y2, x3, y3);
  line(x3, y3, x1, y1);
#endif
}
*/

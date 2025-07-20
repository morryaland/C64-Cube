#include <c64.h>
#include <stdio.h>
#include <string.h>
#include "draw.h"
#include "3d.h"

#define VIC_BITMAP_MODE 32
#define VIC_MULTICOLOR_MODE 16
#define VIC_MEMSETUP 128

int main(void)
{
  /* configure vic */
  VIC.bordercolor = COLOR_BLACK;
  VIC.bgcolor0 = COLOR_BLACK;
  VIC.ctrl1 |= VIC_BITMAP_MODE;
#if !LINE_MODE
  VIC.ctrl2 |= VIC_MULTICOLOR_MODE;
#endif
  CIA2.pra &= ~1;
  VIC.addr = VIC_MEMSETUP;
  /* set pallite */
#if LINE_MODE
  memset(SCREEN_RAM, 0x10, 1000);
#else
  memset(COLOR_RAM, 1, 1000);
#endif
  while (1) {
    /* clearbitmap */
    memset(BITMAP_RAM, 0, 8000);
    triangle(123, 100, 12, 42, 35, 120, 0);
    /*
    look_at_cam();
    cuberttb++;
    cubertta++;
    */
  }
}

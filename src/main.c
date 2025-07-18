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
  memset(SCREEN_RAM, 0x10, 1000);
  while (1) {
    /* clearbitmap */
    memset(BITMAP_RAM, 0, 8000);
    look_at_cam();
    cuberttb++;
    cubertta++;
  }
}

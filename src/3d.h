#ifndef __3D_H__
#define __3D_H__

extern signed char tsin[];

extern int cubeposx;
extern int cubeposy;
extern int cubeposz;
extern char cubertta;
extern char cuberttb;
extern int cubev[];
//extern int cubef[];
extern char cubei[];

extern int camposx;
extern int camposy;
extern int camposz;
extern char camrtta;
extern char camrttb;

void look_at_cam();

void rotate_v3(int v[3], char a, char b);

/*float Q_rsqrt(float number);*/

#endif

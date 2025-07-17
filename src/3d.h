#ifndef __3D_H__
#define __3D_H__

#define GRID 255

struct mesh_s {
  int *v;
  int *f;
  char *i;
  char v_c;
  char i_c;
};

struct empty_s {
  int posx;
  int posy;
  int posz;
  char rtta;
  char rttb;
};

struct obj_s {
  struct empty_s *point;
  struct mesh_s *mesh;
};

extern signed char tsin[];

extern struct obj_s cube;
extern struct empty_s cam;

void init_cube(void);
void free_cube(void);

void look_at(struct empty_s *point);

void rotate_v3(int v[3], char a, char b);

/*float Q_rsqrt(float number);*/

#endif

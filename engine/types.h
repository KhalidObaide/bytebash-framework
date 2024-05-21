#ifndef TYPES_H
#define TYPES_H

typedef struct {
  int width;
  int height;
} Size;

typedef struct {
  int x;
  int y;
} Coordinate;

typedef struct {
  int r, g, b, a;
} RGBA;

#endif // !TYPES_H

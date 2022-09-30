#include <math.h>
#ifndef VECTOR3_H
#define VECTOR3_H
struct Vector3
{
  double x;
  double y;
  double z;
};

inline double GetNormVector3(struct Vector3 v){ return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }

struct Vector3 AddVector3(struct Vector3, struct Vector3);

struct Vector3 SubVector3(struct Vector3, struct Vector3);

struct Vector3 ScalarMultiplicationVector3(double, struct Vector3);

double DotProductVector3(struct Vector3, struct Vector3);

struct Vector3 CrossProductVector3(struct Vector3, struct Vector3);

void PrintVector3(struct Vector3);
#endif


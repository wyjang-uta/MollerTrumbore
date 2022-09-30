#include <stdio.h>
#include <math.h>
#include "Vector3.h"

struct Vector3 AddVector3(struct Vector3 v1, struct Vector3 v2)
{
  struct Vector3 sum;
  sum.x = v1.x + v2.x;
  sum.y = v1.y + v2.y;
  sum.z = v1.z + v2.z;

  return sum;
}


struct Vector3 SubVector3(struct Vector3 v1, struct Vector3 v2)
{
  struct Vector3 sub;
  sub.x = v1.x - v2.x;
  sub.y = v1.y - v2.y;
  sub.z = v1.z - v2.z;
  return sub;
}


struct Vector3 ScalarMultiplicationVector3(double c, struct Vector3 v)
{
  struct Vector3 result;
  result.x = c * v.x;
  result.y = c * v.y;
  result.z = c * v.z;

  return result;
}


double DotProductVector3(struct Vector3 v1, struct Vector3 v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

struct Vector3 CrossProductVector3(struct Vector3 v1, struct Vector3 v2)
{
  struct Vector3 crossProduct;
  crossProduct.x = v1.y * v2.z - v1.z * v2.y;
  crossProduct.y = v1.z * v2.x - v1.x * v2.z;
  crossProduct.z = v1.x * v2.y - v1.y * v2.x;
  return crossProduct;
}


void PrintVector3(struct Vector3 v)
{
  printf("1st component: %.3f\n", v.x);
  printf("2nd component: %.3f\n", v.y);
  printf("3rd component: %.3f\n", v.z);
}

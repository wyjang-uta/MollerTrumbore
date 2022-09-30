#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "Vector3.h"
#include "Triangle.h"
#include "MollerTrumbore.h"

int main(int argc, char* argv[])
{
  struct Vector3 rayO = {0.0, 0.0, 0.0};     // beam start point
  struct Vector3 rayV = {0.0, 0.0, 1.0};     // beam direction vector
  struct Vector3 tri_v0 = {+1.0,  0.0, 1.0};
  struct Vector3 tri_v1 = {-1.0, -1.0, 1.0};
  struct Vector3 tri_v2 = {-1.0, +1.0, 1.0};
  struct Triangle tri = {tri_v0, tri_v1, tri_v2};
  struct Vector3 inter;

  bool intersect = MollerTrumbore(rayO, rayV, tri, inter);
  if( intersect == true )
  {
    printf("This vector intersects the triangle\n");
  }
  else
  {
    printf("This vector does not intersect the triangle\n");
  }

  struct Vector3 v1 = {1.1, 2.8, -5.1};
  printf("=====Print components of v1 =====\n");
  PrintVector3(v1);
  printf("\n");

  struct Vector3 v2 = {2.3, 3.1, 0.4};
  printf("=====Print components of v2 =====\n");
  PrintVector3(v2);
  printf("\n");

  struct Vector3 v3 = AddVector3(v1, v2);
  printf("=====Print components of v1 + v2 =====\n");
  PrintVector3(v3);
  printf("\n");

  struct Vector3 vCross = CrossProductVector3(v1, v2);
  printf("=====Print components of v1 x v2 =====\n");
  PrintVector3(vCross);
  printf("\n");

  double inner = DotProductVector3(vCross, v1);
  printf("Inner product of vCross and v1: %f\n", inner);

  return 0;
}

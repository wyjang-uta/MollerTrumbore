#include "Vector3.h"
#include "Triangle.h"
#include "MollerTrumbore.h"
#include "stdbool.h"

bool MollerTrumbore(struct Vector3 rayOrigin,
                    struct Vector3 rayVector,
                    struct Triangle inputTriangle,
                    struct Vector3 outIntersectionPosition)
{
  const double EPSILON = 1.e-7;   // tollerance
  struct Vector3 vertex0 = inputTriangle.vertex0;
  struct Vector3 vertex1 = inputTriangle.vertex1;
  struct Vector3 vertex2 = inputTriangle.vertex2;
  struct Vector3 edge1, edge2, h, s, q;
  double a, f, u, v;
  edge1 = SubVector3(vertex1, vertex0);
  edge2 = SubVector3(vertex2, vertex0);
  h = CrossProductVector3(rayVector, edge2);
  a = DotProductVector3(edge1, h);

  if( a > -EPSILON && a < EPSILON )
    return false;     // this ray is parallel to this triangle.
  f = 1.0/a;
  s = SubVector3( rayOrigin, vertex0 );
  u = f * DotProductVector3( s, h );
  if( u < 0.0 || u > 1.0 )
    return false;
  q = CrossProductVector3( s, edge1 );
  v = f * DotProductVector3( rayVector, q );
  if( v < 0.0 || u + v > 1.0 )
    return false;
  // At this stage we can compute t to find out where the intersection point is on the line.
  double t = f * DotProductVector3( edge2, q );
  if( t > EPSILON ) // ray intersection
  {
    outIntersectionPosition = AddVector3(rayOrigin,  ScalarMultiplicationVector3(t, rayVector));
    return true;
  }
  else  // This means that there is a line intersection but not a ray intersection.
    return false;
}

#include <iostream>
#include <fstream>
#include <cmath>

class Vector3D
{
  public:
    float x, y, z;
    Vector3D(){x=y=z=0;}
    Vector3D(float a, float b, float c){x=a, y=b, z=c;}
    ~Vector3D() {}

    float GetMagnitude()
    {
      return sqrt(x*x + y*y + z*z);
    }

    Vector3D operator*(float num) const
    {
      return Vector3D(x*num, y*num, z*num);
    }

    Vector3D operator+(const Vector3D &vec) const
    {
      return Vector3D(x + vec.x, y + vec.y, z + vec.z);
    }

    Vector3D operator-(const Vector3D &vec) const
    {
      return Vector3D(x - vec.x, y - vec.y, z - vec.z);
    }

    Vector3D &operator=(const Vector3D &vec)
    {
      x = vec.x;
      y = vec.y;
      z = vec.z;
      return *this;
    }

    void NormalizeVector3D(void)
    {
      float mag = sqrt(x*x + y*y + z*z);
      x /= mag;
      y /= mag;
      z /= mag;
    }

    float DotVector3D(const Vector3D &vec) const
    {
      return x*vec.x + y*vec.y + z*vec.z;
    }

    Vector3D CrossVector3D(const Vector3D &vec) const
    {
      return Vector3D(y*vec.z - z*vec.y,
          z*vec.x - x*vec.z,
          x*vec.y - y*vec.x);
    }

    float AngleBetweenVector3Ds(Vector3D& vec)
    {
      return ( acos( DotVector3D(vec) / (GetMagnitude() * vec.GetMagnitude())) * (180./M_PI));
    }

    void Print(void)
    {
      std::cout << "v.x: " << x << ", v.y: " << y << ", v.z: " << z << std::endl;
    }
};

class Ray
{
  Vector3D o;          // Origin
  Vector3D d;          // Direction
  Ray(Vector3D i, Vector3D j) { o = i; d = j;}
};

// a rectangular plane
class RecPlane
{
  float a, b, c;     // direction vector
  float x, y, z;     // position vector
};

// a box - defined by 6 planes
/*
class Box
{
  float x, y, z;    // its position of center of gravity
  float w, h, d;    // wide, height, depth
  float a, b, c;    // rotation
  Box(float i, float j, float k, float u, float v, float w)
  {
    x = i;
    y = j;
    z = k;
    a = u;
    b = v;
    c = w;
  }
  bool Intersect(Ray ray)
  {
    // test six planes
    return false;
  }
};
*/

class Triangle
{
  public:
    Vector3D vertex0;
    Vector3D vertex1;
    Vector3D vertex2;
    Triangle() {}
    Triangle(Vector3D v0, Vector3D v1, Vector3D v2)
    {
      vertex0 = v0, vertex1 = v1, vertex2 = v2;
    }

    void Print(void)
    {
      std::cout << "Triangle information:" << std::endl;
      std::cout << "1st vertex: (" << vertex0.x << ", " << vertex0.y << ", " << vertex0.z << ")." << std::endl;
      std::cout << "2nd vertex: (" << vertex1.x << ", " << vertex1.y << ", " << vertex1.z << ")." << std::endl;
      std::cout << "3rd vertex: (" << vertex2.x << ", " << vertex2.y << ", " << vertex2.z << ")." << std::endl;
      std::cout << "End of triangle information." << std::endl;
    }
};

class Rectangle
{
  public:
    Vector3D vertex[4];
    Rectangle(Vector3D v0, Vector3D v1, Vector3D v2, Vector3D v3)
    {
      vertex[0] = v0, vertex[1] = v1, vertex[2] = v2, vertex[3] = v3;
    }
    void Print(void)
    {
      std::cout << "Rectangle information:" << std::endl;
      for( int i = 0; i < 4; i++ )
      {
        std::cout << i;
        if( i == 0 ) std::cout << "st";
        else if( i == 1 ) std::cout << "nd";
        else if( i == 2 ) std::cout << "rd";
        else    std::cout << "th";
        std::cout << " vertex: (" << vertex[i].x << ", " << vertex[i].y << ", " << vertex[i].z << ")." << std::endl;
      }
      std::cout << "End of rectangle information." << std::endl;
    }
};

class Box
{
  public:
    Vector3D vertex[8];
    Box(Vector3D v0, Vector3D v1, Vector3D v2, Vector3D v3, Vector3D v4, Vector3D v5, Vector3D v6, Vector3D v7)
    {
      vertex[0] = v0;
      vertex[1] = v1;
      vertex[2] = v2;
      vertex[3] = v3;
      vertex[4] = v4;
      vertex[5] = v5;
      vertex[6] = v6;
      vertex[7] = v7;
    }
};

bool RayIntersectsTriangle(Vector3D rayOrigin,
    Vector3D rayVector,
    Triangle* inTriangle,
    Vector3D& outIntersectionPoint)
{
  const float EPSILON = 1e-7;
  Vector3D vertex0 = inTriangle->vertex0;
  Vector3D vertex1 = inTriangle->vertex1;
  Vector3D vertex2 = inTriangle->vertex2;
  Vector3D edge1, edge2, h, s, q;
  float a, f, u, v;
  edge1 = vertex1 - vertex0;
  edge2 = vertex2 - vertex0;
  h = rayVector.CrossVector3D(edge2);
  a = edge1.DotVector3D(h);
  if( a > -EPSILON && a < EPSILON)
    return false;   // This ray is parallel to this triangle.
  f = 1.0/a;
  s = rayOrigin - vertex0;
  u = f * s.DotVector3D(h);
  if( u < 0.0 || u > 1.0 )
    return false;
  q = s.CrossVector3D(edge1);
  v = f * rayVector.DotVector3D(q);
  if( v < 0.0 || u + v > 1.0 )
    return false;
  // At this stage we can compute t to find out where the intersection point is on the line.
  float t = f * edge2.DotVector3D(q);
  if( t > EPSILON ) // ray intersection
  {
    outIntersectionPoint = rayOrigin + rayVector * t;
    return true;
  }
  else    // This means that there is a line intersection but not a ray intersection.
    return false;
}

// 1,2,3 앞면
// 2,3,4
//
// 1,5,3 왼쪽면
// 5,3,7
//
// 2,6,4 오른쪽면
// 6,4,8
//
// 1,5,2
// 5,2,6 윗면
//
// 3,4,7
// 4,7,8 아랫면
//
// 5,6,7 뒷면
// 6,7,8

bool RayIntersectsCube(Vector3D rayOrigin,
    Vector3D rayVector,
    Box* inBox)
{
  bool front, front1, front2;
  bool back, back1, back2;
  bool top, top1, top2;
  bool bottom, bottom1, bottom2;
  bool left, left1, left2;
  bool right, right1, right2;

  Triangle frontTri1, frontTri2;
  Triangle backTri1, backTri2;
  Triangle topTri1, topTri2;
  Triangle bottomTri1, bottomTri2;
  Triangle leftTri1, leftTri2;
  Triangle rightTri1, rightTri2;

  Vector3D intersection;
  // front test
  frontTri1 = Triangle(inBox->vertex[0], inBox->vertex[1], inBox->vertex[2]);
  frontTri2 = Triangle(inBox->vertex[1], inBox->vertex[2], inBox->vertex[3]);
  front1 = RayIntersectsTriangle(rayOrigin, rayVector, &frontTri1, intersection);
  front2 = RayIntersectsTriangle(rayOrigin, rayVector, &frontTri2, intersection);
  front = front1 || front2;

  // back test
  backTri1 = Triangle(inBox->vertex[4], inBox->vertex[5], inBox->vertex[6]);
  backTri2 = Triangle(inBox->vertex[5], inBox->vertex[6], inBox->vertex[7]);
  back1 = RayIntersectsTriangle(rayOrigin, rayVector, &backTri1, intersection);
  back2 = RayIntersectsTriangle(rayOrigin, rayVector, &backTri2, intersection);
  back = back1 || back2;

  // top test
  topTri1 = Triangle(inBox->vertex[0], inBox->vertex[4], inBox->vertex[1]);
  topTri2 = Triangle(inBox->vertex[4], inBox->vertex[1], inBox->vertex[5]);
  top1 = RayIntersectsTriangle(rayOrigin, rayVector, &topTri1, intersection);
  top2 = RayIntersectsTriangle(rayOrigin, rayVector, &topTri2, intersection);
  top = top1 || top2;

  // bottom test
  bottomTri1 = Triangle(inBox->vertex[2], inBox->vertex[3], inBox->vertex[6]);
  bottomTri2 = Triangle(inBox->vertex[3], inBox->vertex[6], inBox->vertex[7]);
  bottom1 = RayIntersectsTriangle(rayOrigin, rayVector, &bottomTri1, intersection);
  bottom2 = RayIntersectsTriangle(rayOrigin, rayVector, &bottomTri2, intersection);
  bottom = bottom1 || bottom2;

  // left test
  leftTri1 = Triangle(inBox->vertex[0], inBox->vertex[4], inBox->vertex[2]);
  leftTri2 = Triangle(inBox->vertex[4], inBox->vertex[2], inBox->vertex[6]);
  left1 = RayIntersectsTriangle(rayOrigin, rayVector, &leftTri1, intersection);
  left2 = RayIntersectsTriangle(rayOrigin, rayVector, &leftTri2, intersection);
  left = left1 || left2;

  // right test
  rightTri1 = Triangle(inBox->vertex[1], inBox->vertex[5], inBox->vertex[3]);
  rightTri2 = Triangle(inBox->vertex[5], inBox->vertex[3], inBox->vertex[7]);
  right1 = RayIntersectsTriangle(rayOrigin, rayVector, &rightTri1, intersection);
  right2 = RayIntersectsTriangle(rayOrigin, rayVector, &rightTri2, intersection);
  right = right1 || right2;

  int trueCounter = 0;

  if( front ) trueCounter++;
  if( back ) trueCounter++;
  if( top ) trueCounter++;
  if( bottom ) trueCounter++;
  if( left ) trueCounter++;
  if( right ) trueCounter++;

  if( trueCounter == 2 ) return true;
  else if( trueCounter > 2 )
  {
    std::cout << "something strange? hit counter is greater than 2" << std::endl;
    return true;
  }
  else return false;
}

int main()
{
  Vector3D rayO(0, 0, 0);
  Vector3D rayV(1, 0, 0);
  Vector3D v0(2, -1, +1);
  Vector3D v1(2, +1, +1);
  Vector3D v2(2, -1, -1);
  Vector3D v3(2, +1, -1);
  Vector3D v4(3, -1, +1);
  Vector3D v5(3, +1, +1);
  Vector3D v6(3, -1, -1);
  Vector3D v7(3, +1, -1);
  Vector3D triv0(2, -1,  1);
  Vector3D triv1(2,  1,  1);
  Vector3D triv2(2,  0, -1);
  Vector3D triv3(2,  2,  2);
  Vector3D inter;
  triv0.Print();
  triv1.Print();
  triv2.Print();
  Triangle tri(triv0, triv1, triv2);
  tri.Print();
  Rectangle rect(triv0, triv1, triv2, triv3);
  Box box(v0, v1, v2, v3, v4, v5, v6, v7);

  rect.Print();

  bool intersect = RayIntersectsTriangle(rayO, rayV, &tri, inter);
  if( intersect == true )
  {
    std::cout << "This vector intersects the triangle" << std::endl;
  }
  else
  {
    std::cout << "This vector does not intersect the triangle" << std::endl;
  }

  bool interCube = RayIntersectsCube(rayO, rayV, &box);
  if( interCube )
  {
    std::cout << "This vector intersects the given box!"  << std::endl;
  }
  else
  {
    std::cout << "This vector does not intersect the given box." << std::endl;
  }

  return 0;
}

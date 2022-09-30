class Vector3D
{
	public:
    float x, y, z;
    Vector3D() { x=y=z=0; }
    Vector3D(float a, float b, float c){x=a, y=b, z=c;}
    ~Vector3D() {}

    Vector3D  operator*(float num) const;
    Vector3D  operator+(const Vector3D &vec) const;
    Vector3D  operator-(const Vector3D &vec) const;
    Vector3D &operator=(const Vector3D &vec);

    float GetMagnitude();
    void NormalizeVector3D();
    float DotProduct(const Vector3D &vec) const;
    Vector3D CrossProduct(const Vector3D &vec) const;
    float AngleBetween(Vector3D& vec);
    void Print();
};

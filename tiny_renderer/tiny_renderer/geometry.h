#pragma once
#include <cmath>
#include <cstdint>

#define PI 3.14159265359

template <typename T>
struct Vec2
{
	union
	{
		struct { T x, y; };
		T raw[2];
	};

	inline Vec2(): x(0), y(0){}
	inline Vec2(T x, T y) : x(x), y(y) {}

	inline Vec2<T> & operator + (Vec2<T> other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	inline Vec2<T>& operator * (float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	inline T& operator [] (int inx)
	{
		return raw[inx];
	}
};

template <typename T>
struct Vec3
{
	union
	{
		struct { T x, y, z; };
		T raw[3];
	};

	inline Vec3() : x(0), y(0), z(0) {}
	inline Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

	inline Vec3<T>& operator + (Vec3<T> other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	inline Vec3<T>& operator - (Vec3<T> other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	inline Vec3<T>& operator * (float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	inline T& operator [] (int inx)
	{
		return raw[inx];
	}

	float norm()
	{
		return std::sqrt(x * x + y * y + z * z); 
	}

	inline Vec3<T>& normalize()
	{
		*this = (*this) * (1.0f / norm());
		return *this;
	}

};

typedef Vec2<int> Vert2i;
typedef Vec2<float> Vert2f;
typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;

typedef Vec3<int> Vert3i;
typedef Vec3<float> Vert3f;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;



template <typename T>
inline float dproduct(Vec3<T> a, Vec3<T> b)
{
	float res = 0;
	for (int i = 0; i < 3; i++)
		res += a[i] * b[i];

	return res;
}

template <typename T>
inline int dproduct(Vec2<T> a, Vec2<T> b)
{
	int res = 0;
	for (int i = 0; i < 2; i++)
		res += a[i] * b[i];

	return res;
}

template <typename T>
inline void cproduct(Vec3<T> a, Vec3<T> b, Vec3<T>* res)
{
	res->x = a.y * b.z - a.z * b.y;
	res->y = a.z * b.x - a.x * b.z;
	res->z = a.x * b.y - a.y * b.x;
}

template <typename T>
Vec3<T> cross(Vec3<T> v1, Vec3<T> v2) {
	return Vec3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template<typename T>
class Matrix44
{
public:
	T m[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };

	Matrix44() {}

	const T* operator [] (uint8_t i) const { return m[i]; }
	T* operator [] (uint8_t i) { return m[i]; }

	Matrix44 operator * (const Matrix44& rhs) const
	{
		Matrix44 mult;
		for (uint8_t i = 0; i < 4; ++i)
		{
			for (uint8_t j = 0; j < 4; ++j)
			{
				mult[i][j] = m[i][0] * rhs[0][j] +
							 m[i][1] * rhs[1][j] +
							 m[i][2] * rhs[2][j] +
							 m[i][3] * rhs[3][j];
			}
		}

		return mult;
	}
};

typedef Matrix44<float> Matrix44f;

template <typename T>
inline Matrix44<T> ratate_x(float angle)
{
	
}


template <typename T>
Vec3<T> rotateX(Vec3<T> v, float r)
{
	float x = r;
	v.y = v.y * cos(x) + v.z * -sin(x);
	v.z = v.y * sin(x) + v.z * cos(x);
	return v;
}

template <typename T>
Vec3<T> rotateY(Vec3<T> v, float r)
{
	float x = r;
	v.x = v.x * cos(x) + v.z * -sin(x);
	v.z = v.x * sin(x) + v.z * cos(x);
	return v;
}

template <typename T>
Vec3<T> rotateZ(Vec3<T> v, float r)
{
	float x = r;
	v.x = v.x * cos(x) + v.y * -sin(x);
	v.y = v.x * sin(x) + v.y * cos(x);
	return v;
}
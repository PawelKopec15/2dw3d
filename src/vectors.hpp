#pragma once
#include <cmath>

template <typename V = float>
struct Vect2
{
	V x;
	V y;

	Vect2()
	{
		x = V();
		y = V();
	}

	Vect2(V x, V y) : x(x), y(y)
	{

	}

	//add operator overloading here
	Vect2<V> operator +(Vect2<V> other)
	{
		return Vect2<V>(x + other.x, y + other.y);
	}

	Vect2<V> operator +(V other)
	{
		return Vect2<V>(x + other, y + other);
	}
	//rest:

	V Length()
	{
		return sqrt(x * x + y * y);
	}

	//direction is a vector to indicate rotation, but is NOT normalized
	Vect2 ToDirection()
	{
		V maxVal = max(abs(x), abs(y));
		return Vect2(x / maxVal, y / maxVal);
	}

	//normalizes original vector
	void Normalize()
	{
		V dist = Length();
		x = x / dist;
		y = y / dist;
	}

	//returns normalized version of vector
	Vect2 Normalized()
	{
		V dist = Length();
		return Vect2(x / dist, y / dist);
	}
};

//do same as Vect2
template <typename V = float>
struct Vect3
{
	V x;
	V y;
	V z;

	Vect3()
	{
		x = V();
		y = V();
		z = V();
	}

	Vect3(V x, V y, V z) : x(x), y(y), z(z)
	{

	}

	//Segmented getting
	Vect2<V> xy()
	{
		return Vect2<V>(x, y);
	}

	Vect2<V> xz()
	{
		return Vect2<V>(x, z);
	}

	Vect2<V> yz()
	{
		return Vect2<V>(y, z);
	}

	Vect2<V> yx()
	{
		return Vect2<V>(y, x);
	}

	Vect2<V> zx()
	{
		return Vect2<V>(z, x);
	}

	Vect2<V> zy()
	{
		return Vect2<V>(z, y);
	}

	//-------------------------------------------------
	//functions
	
	//v is regular vector, rot is in deegres
	static Vect3<V> Rotated3D(Vect3<V> pos, Vect3<V> rot) //using deegres
	{
		Vect3<V> rad = 0.0174532924 * rot;
		Vect3<V> Cos = Vect3<V>(cos(rad.x), cos(rad.y), cos(rad.z));
		Vect3<V> Sin = Vect3<V>(sin(rad.x), sin(rad.y), sin(rad.z));
		//this is matrix multiplication without generating matricies
		//x axis
		pos = Vect3<V>(pos.x, Cos.x * pos.y - Sin.x * pos.z, Sin.x * pos.y + Cos.x * pos.z);
		//y axis
		pos = Vect3<V>(Cos.y * pos.x + Sin.y * pos.z, pos.y, -Sin.y * pos.x + Cos.y * pos.z);
		//z axis
		pos = Vect3<V>(Cos.z * pos.x - Sin.z * pos.y, Sin.z * pos.x + Cos.z * pos.y, pos.z);

		return pos;
	}

	//rotates around 0 point
	Vect3<V>& Rotate3D(Vect3<V> rot) //using deegres
	{
		Vect3<V> rad = 0.0174532924 * rot;
		Vect3<V> Cos = Vect3<V>(cos(rad.x), cos(rad.y), cos(rad.z));
		Vect3<V> Sin = Vect3<V>(sin(rad.x), sin(rad.y), sin(rad.z));
		//this is matrix multiplication without generating matricies
		//x axis
		this = Vect3<V>(x, Cos.x * y - Sin.x * z, Sin.x * y + Cos.x * z);
		//y axis
		this = Vect3<V>(Cos.y * x + Sin.y * z, y, -Sin.y * x + Cos.y *z);
		//z axis
		this = Vect3<V>(Cos.z * x - Sin.z * y, Sin.z * x + Cos.z * y, z);
		return *this;
	}

	//------------------------------------------
	//operator overloading
	Vect3<V> operator +(Vect3<V>& other)
	{
		return Vect3<V>(x + other.x, y + other.y, z + other.z);
	}
	Vect3<V> operator +(Vect3<V> other)
	{
		return Vect3<V>(x + other.x, y + other.y, z + other.z);
	}
	Vect3<V> operator -(Vect3<V>& other)
	{
		return Vect3<V>(x - other.x, y - other.y, z - other.z);
	}
	Vect3<V> operator -(Vect3<V> other)
	{
		return Vect3<V>(x - other.x, y - other.y, z - other.z);
	}
	Vect3<V> operator -() //this is math negation
	{
		return Vect3<V>(-x, -y, -z);
	}
	Vect3<V> operator *(Vect3<V>& other)
	{
		return Vect3<V>(x * other.x, y * other.y, z * other.z);
	}
	Vect3<V> operator *(Vect3<V> other)
	{
		return Vect3<V>(x * other.x, y * other.y, z * other.z);
	}
	Vect3<V> operator *(V& other)
	{
		return Vect3<V>(x * other, y * other, z * other);
	}
	Vect3<V> operator /(Vect3<V>& other)
	{
		return Vect3<V>(x / other.x, y / other.y, z / other.z);
	}
	Vect3<V> operator /(Vect3<V> other)
	{
		return Vect3<V>(x / other.x, y / other.y, z / other.z);
	}
	Vect3<V> operator /(V& other)
	{
		return Vect3<V>(x / other, y / other, z / other);
	}
	Vect3<V> operator %(Vect3<V>& other)
	{
		return Vect3<V>(fmod(x, other.x), fmod(y, other.y), fmod(z, other.z));
	}
	Vect3<V> operator %(Vect3<V> other)
	{
		return Vect3<V>(fmod(x, other.x), fmod(y, other.y), fmod(z, other.z));
	}
	Vect3<V> operator %(V& other)
	{
		return Vect3<V>(fmod(x, other), fmod(y, other), fmod(z, other));
	}

	//assigment-like
	Vect3<V>& operator +=(const Vect3<V>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	Vect3<V>& operator -=(const Vect3<V>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vect3<V>& operator *=(const Vect3<V>& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}
	Vect3<V>& operator *=(const V& other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}
	Vect3<V>& operator /=(const Vect3<V>& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	Vect3<V>& operator /=(const V& other)
	{
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}
	Vect3<V>& operator %=(const Vect3<V>& other)
	{
		x = fmod(x, other.x);
		y = fmod(y, other.y);
		z = fmod(z, other.z);
		return *this;
	}
	Vect3<V>& operator %=(const V& other)
	{
		x = fmod(x, other);
		y = fmod(y, other);
		z = fmod(z, other);
		return *this;
	}

	/*
	ostream& operator<<(ostream& os, const Vect3& vect)
	{
		os << '(' << vect.x << ", " << vect.y << ", " << vect.z << ')';
		return os;
	}
	*/
};

template <typename V>
struct Vect4
{
	V x;
	V y;
	V z;
	V w;

	Vect4()
	{
		x = V();
		y = V();
		z = V();
		w = V();
	}

	Vect4(V x, V y, V z, V w) : x(x), y(y), z(z), w(w)
	{

	}
};
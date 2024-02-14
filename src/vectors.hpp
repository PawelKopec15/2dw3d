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

	//operator overloading
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
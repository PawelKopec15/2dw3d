#pragma once
#include <cmath>

template <typename V>
struct Vect
{

};

template <typename V>
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

	}

	//returns normalized version of vector
	Vect2 Normalized()
	{

	}
};

//do same as Vect2
template <typename V>
struct Vector3
{
	V x;
	V y;
	V z;

	Vect2<V> xy()
	{
		return Vect2(x, y);
	}
};
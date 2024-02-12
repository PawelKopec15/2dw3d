#pragma once
//class SpacialNode;
class Node;
//#include "objectStructure.hpp"
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
template <typename V>
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

//special vector for transform
//the only existance of it is to maintain nice transform edition
//while correctly synchronizing transforms
struct TransVect3 : Vect3<float>
{
	//this trick makes a "read only" public variable:
private:
	float x_;
	float y_;
	float z_;

public:
	const float& x = x_;
	const float& y = y_;
	const float& z = z_;



	TransVect3()
	{
		x_ = 0;
		y_ = 0;
		z_ = 0;
	}

	TransVect3(Vect3<float> vect) : x_(vect.x), y_(vect.y), z_(vect.z)
	{

	}

	TransVect3(float x, float y, float z) : x_(x), y_(y), z_(z)
	{

	}

	//synch triggers
	TransVect3& operator=(Vect3<float>& other)
	{
		std::cout << "= overloaded" << std::endl;
		x_ = other.x;
		y_ = other.y;
		z_ = other.z;
		return *this;
	}

	TransVect3& operator=(Vect3<float>&& other)
	{
		std::cout << "= overloaded" << std::endl;
		x_ = other.x;
		y_ = other.y;
		z_ = other.z;
		return *this;
	}

	TransVect3& operator=(TransVect3& other)
	{
		std::cout << "= overloaded" << std::endl;
		x_ = other.x;
		y_ = other.y;
		z_ = other.z;
		return *this;
	}

	//ummm I just want to keep it for now
	TransVect3& operator=(TransVect3&& other)
	{
		std::cout << "= overloaded" << std::endl;
		x_ = other.x;
		y_ = other.y;
		z_ = other.z;
		return *this;
	}

	//well unfortunately we have to rewrite everything as for vect3

	//we also converts transVect into regular vect for all r values
	//(because we do not need "secured" vector in vetor expressions)
	Vect3<float> operator+(Vect3& other)
	{
		return Vect3<float>(other.x + x_, other.y + y_, other.z + z_);
	}

	Vect3<float> operator-(Vect3& other)
	{
		return Vect3<float>(other.x - x_, other.y - y_, other.z - z_);
	}

	Vect3<float> operator-(Vect3&& other)
	{
		return Vect3<float>(x_ - other.x, y_ - other.y, z_ - other.z);
	}

	Vect3<float> operator-(TransVect3& other)
	{
		return Vect3<float>(x_ - other.x, y_ - other.y, z_ - other.z);
	}

	Vect3<float> operator*(Vect3& other)
	{
		return Vect3<float>(other.x * x_, other.y * y_, other.z * z_);
	}

	Vect3<float> operator*(float& other)
	{
		return Vect3<float>(other * x_, other * y_, other * z_);
	}

	Vect3<float> operator*(float&& other)
	{
		return Vect3<float>(x_ * other, y_ * other, z_ * other);
	}

	Vect3<float> operator/(float& other)
	{
		return Vect3<float>(other / x_, other / y_, other / z_);
	}

	Vect3<float> operator/(float&& other)
	{
		return Vect3<float>(x_ / other, y_ / other, z_ / other);
	}

	Vect3<float> operator%(float& other)
	{
		return Vect3<float>(fmod(other, x_), fmod(other, y_), fmod(other, z_));
	}

	Vect3<float> operator%(float&& other)
	{
		return Vect3<float>(fmod(x_, other), fmod(y_, other), fmod(z_, other));
	}

	//subscpription operators:
	TransVect3& operator+=(Vect3<float>&& other)
	{
		x_ = x_ + other.x;
		y_ = y_ + other.y;
		z_ = z_ + other.z;
		return *this;
	}

	TransVect3& operator-=(Vect3<float>&& other)
	{
		x_ = x_ - other.x;
		y_ = y_ - other.y;
		z_ = z_ - other.z;
		return *this;
	}

	TransVect3& operator*=(Vect3<float>&& other)
	{
		x_ = x_ * other.x;
		y_ = y_ * other.y;
		z_ = z_ * other.z;
		return *this;
	}

	TransVect3& operator/=(Vect3<float>&& other)
	{
		x_ = x_ / other.x;
		y_ = y_ / other.y;
		z_ = z_ / other.z;
		return *this;
	}

	TransVect3& operator%=(Vect3<float>&& other)
	{
		x_ = fmod(x_, other.x);
		y_ = fmod(y_, other.x);
		z_ = fmod(z_, other.x);
		return *this;
	}

	bool operator==(Vect3<float>&& other)
	{
		return (x_ == other.x && y_ == other.y && z_ == other.z);
	}
};

//contains only 3d coordinates as 2d objects are placed in 3d space
struct Transform
{
	Node* node;
	TransVect3 position;
	TransVect3 rotation;
	TransVect3 globalScale;

	TransVect3 localPosition;
	TransVect3 localRotation;
	TransVect3 scale; //usually when devs change scale they mean local scale

	//for 2d manipulation
	Vect2 <float> flatPosition;

	Transform(Node* node) : node(node), position(), rotation(), globalScale(), localPosition(), localRotation(), scale(1, 1, 1)
	{
		//maybe, will be checked later
		synch(4);
		synch(5);
		synch(6);
	}

	//synchronization
	void synch(int changeType)
	{
		if (changeType == 0) //position
		{
			//*
			Node* parent = node->parent;
			//Node* parent = node->parent;
			//parent synch
			if (!(parent == nullptr))
			{
				//localPosition = position - parent->transform.position;
			}
			else
			{
				localPosition = position;
			}
			//Transform parent = parent;


			//child synch
			//*/
		}
		else if (changeType == 1) //rotation
		{

		}
		else if (changeType == 2) //scale (global)
		{

		}
		else if (changeType == 3) //local pos
		{

		}
		else if (changeType == 3) //local rot
		{

		}
		else if (changeType == 3) //local scale
		{

		}
		else if (changeType == 3) //2d pos
		{

		}
	}

};


/*
struct Rigidbody : public Component
{

};
*/
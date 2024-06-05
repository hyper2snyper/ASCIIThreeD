#pragma once
#include <vector>
#include <math.h>

class Vertex
{
public:

	double x{}, y{}, z{};

	void operator*=(double s)
	{
		x *= s;
		y *= s;
		z *= s;
	}
};


class Triangle
{
public:
	Vertex vertices[3]{};
	char texture{ '@' };
};


class Object
{
public:
	std::vector<Triangle> triangles{};
	Vertex center{}; //World


	void rotate_x(double degrees)
	{
		double r{ degrees * (3.14159f / 180) };
		for (Triangle& tri : triangles)
		{
			for (Vertex& v : tri.vertices)
			{
				double Y{ v.y * cos(r) - v.z * sin(r) };
				double Z{ v.y * sin(r) + v.z * cos(r) };
				v.y = Y;
				v.z = Z;
			}
		}			
	}
	void rotate_y(double degrees)
	{
		double r{ degrees * (3.14159f / 180) };
		for (Triangle& tri : triangles)
		{
			for (Vertex& v : tri.vertices)
			{
				double X{ v.x * cos(r) + v.z * sin(r) };
				double Z{ v.z * cos(r) - v.x * sin(r) };
				v.x = X;
				v.z = Z;
			}
		}
	}
	void rotate_z(double degrees)
	{
		double r{ degrees * (3.14159f / 180) };
		for (Triangle& tri : triangles)
		{
			for (Vertex& v : tri.vertices)
			{
				double X{ v.x * cos(r) - v.y * sin(r) };
				double Y{ v.x * sin(r) + v.y * cos(r) };
				v.x = X;
				v.y = Y;
			}
		}
	}


};
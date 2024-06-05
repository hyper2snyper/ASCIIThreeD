#include <vector>
#include <algorithm>
#include <math.h>
#include "Vertex.h"

class Vertex2
{
public:
	double x{}, y{};

	void operator*=(double s)
	{
		x *= s;
		y *= s;
	}
};


class Plane 
{
public:

	Vertex2 vertices[3]{};
	Vertex o_vertices[3]{};
	char texture{};

	void operator*=(double s)
	{
		for (size_t i{}; i < 3; ++i)
		{
			vertices[i] *= s;
		}
	}


#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

	bool cast(float x, float y) const
	{
		Vertex2 v0{ vertices[0] };
		Vertex2 v1{ vertices[1] };
		Vertex2 v2{ vertices[2] };

		double denominator { (v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y) };
		double a {((v1.y - v2.y) * (x - v2.x) + (v2.x - v1.x) * (y - v2.y)) / denominator};
		double b { ((v2.y - v0.y) * (x - v2.x) + (v0.x - v2.x) * (y - v2.y)) / denominator };
		double c { 1 - a - b };

		return (a >= 0 && b >= 0 && c >= 0);
	}




	double avrg_z() const
	{
		double z{};
		for (size_t i{}; i < 3; ++i)
		{
			z += o_vertices[i].z;
		}
		return z / 3;
	}
};




class Renderer
{
	friend class World;
	char** buffer{};
	int xmax{}, ymax{};

	Vertex pos{};
	Vertex rot{};

	double distance_scale{ 5 };

public:

	Renderer(int x, int y)
	{
		xmax = x;
		ymax = y;
		buffer = new char* [ymax] {};
		for (size_t y{}; y < ymax; ++y)
		{
			buffer[y] = new char[xmax] {};
		}
	}

	void clear_buffer()
	{
		for (size_t y{}; y < ymax; ++y)
		{
			for (size_t x{}; x < xmax; ++x)
			{
				buffer[y][x] = '\0';
			}
		}
	}

	
	void render(std::vector<Object*> objects)
	{
		clear_buffer();
		std::vector<Plane> planes{ calculate_planes(objects) };
		std::sort(planes.begin(), planes.end(), [](const Plane& lhs, const Plane& rhs)
			{
				return lhs.avrg_z() > rhs.avrg_z();
			});
		for (size_t y{}; y < ymax; ++y)
		{
			for (size_t x{}; x < xmax; ++x)
			{
				for (Plane plane : planes)
				{
					if (!plane.cast((float)x/3, (float)y/3)) continue;
					
					buffer[y][x] = plane.texture;
					break;
				}
			}
		}
	}


#define cx cos(rot.x*v.x)
#define cy cos(rot.y*v.y)
#define cz cos(rot.z*v.z)
#define sx sin(rot.x*v.x)
#define sy sin(rot.y*v.y)
#define sz sin(rot.z*v.z)
#define X (v.x-pos.x)
#define Y (v.y-pos.y)
#define Z (v.z-pos.z)

	std::vector<Plane> calculate_planes(std::vector<Object*> objects)
	{
		std::vector<Plane> planes{};
		for (Object* object : objects)
		{
			for (Triangle triangle : object->triangles)
			{
				Plane plane{};
				for (size_t i{}; i<3; ++i)
				{
					Vertex vn{ triangle.vertices[i] };
					//vn *= distance_scale / object->center.z;
					Vertex v{ vn.x + object->center.x, vn.y + object->center.y, vn.z + object->center.z };

					double dx{cy*(sy*Y)-sy*Z};
					double dy{sx*(cy*Z+sy*(sz*Y+cz*X))+cx*(cz*Y-sz*X)};
					double dz{cx*(cy*Z+sy*(sz*Y+cz*X))-sx*(cz*Y-sz*X)};
				
					double bx{ (v.z / dz) * dx + v.x };
					double by{ (v.z / dz) * dy + v.y };

					double ix{ (dz > -0.1f && dz < 0.1f) ? v.x-pos.x : bx };
					double iy{ (dz > -0.1f && dz < 0.1f) ? v.y-pos.y : by };

					plane.vertices[i] = { ix, iy };
					plane.o_vertices[i] = vn;
				}
				plane.texture = triangle.texture;
				planes.push_back(plane);
			}
		}
		return planes;
	}
#undef cx
#undef cy
#undef cz
#undef sx
#undef sy
#undef sz
#undef X
#undef Y
#undef Z
};
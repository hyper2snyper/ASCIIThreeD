#include "Vertex.h"
#include "Renderer.h"
#include <iostream>

class World
{
public:
	std::vector<Object*> objects{};

	Renderer renderer{50,50};

	void add_object(Object* object)
	{
		objects.push_back(object);
	}

	void render()
	{
		renderer.render(objects);
	}


	char** get_buffer()
	{
		return renderer.buffer;
	}

	int get_x_max()
	{
		return renderer.xmax;
	}
	int get_y_max()
	{
		return renderer.ymax;
	}


};
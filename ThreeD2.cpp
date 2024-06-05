#include "World.h"
#include <iostream>

#include <ncurses.h>
#include <unistd.h>

int main()
{
    Object obj{};
    obj.center = { 5,3,0 };

    Triangle t1{};
    t1.vertices[0] = { 0,-2,0 };
    t1.vertices[1] = { -2,2,-2 };
    t1.vertices[2] = { 2,2,-2 };
    t1.texture = { '@' };
    obj.triangles.push_back(t1);

    Triangle t2{};
    t2.vertices[0] = { 0,-2,0 };
    t2.vertices[1] = { -2,2,2 };
    t2.vertices[2] = { 2,2,2 };
    t2.texture = { '|' };
    obj.triangles.push_back(t2);

    Triangle t3{};
    t3.vertices[0] = { 0,-2,0 };
    t3.vertices[1] = { 2,2,2 };
    t3.vertices[2] = { 2,2,-2 };
    t3.texture = { 'H' };
    obj.triangles.push_back(t3);

    Triangle t4{};
    t4.vertices[0] = { 0,-2,0 };
    t4.vertices[1] = { -2,2,2};
    t4.vertices[2] = { -2,2,-2 };
    t4.texture = { 'Y' };
    obj.triangles.push_back(t4);

    Triangle t5{};
    t5.vertices[0] = { -2,2,2 };
    t5.vertices[1] = { -2,2,-2 };
    t5.vertices[2] = { 2,2,-2 };
    t5.texture = { '.' };
    obj.triangles.push_back(t5);

    Triangle t6{};
    t6.vertices[0] = { 2,2,-2 };
    t6.vertices[1] = { 2,2,2 };
    t6.vertices[2] = { -2,2,2 };
    t6.texture = { '.' };
    obj.triangles.push_back(t6);
    


    World world{};
    world.add_object(&obj);
    world.render();

    initscr();
    char** buffer{world.get_buffer()};
    
    int x{};
    while(true)
    {
        clear();
        world.render();
        obj.rotate_x(x&2);
        obj.rotate_y(1);
        for(size_t y{}; y < world.get_y_max(); ++y)
        {
            for(size_t x{}; x < world.get_x_max(); ++x)
            {
                move(y,x*2);
                if(buffer[y][x] == '\0')
                {
                    addch(' ');
                    continue;
                }
                addch(buffer[y][x]);
                addch(' ');
            }
        }
        refresh();
        usleep(50000);
        x++;
    }
    endwin();


 
}

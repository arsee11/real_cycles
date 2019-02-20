#include "utils.h"
#include "GL/gl.h"
#include <vector>
#include <string.h>
#include <tuple>

void cycle_draw(const Vex vexs[], int slices)
{
    glBegin (GL_TRIANGLES);
    int i;
    for(i=0; i<slices*2&&i+2<slices*2; i++)
    {
        if(i%2)
            glColor3f(0, 1, 0);
        else
            glColor3f(1, 0,0);

        Vex v1 = vexs[i];
        Vex v2 = vexs[i+1];
        Vex v3 = vexs[i+2];
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }

    {
        Vex v1 = vexs[i];
        Vex v2 = vexs[i+1];
        Vex v3 = vexs[0];
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    {
        Vex v1 = vexs[i+1];
        Vex v2 = vexs[0];
        Vex v3 = vexs[1];
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }

    glEnd();
}

std::tuple<int, short*> build_cycle_indexs(int slices)
{
    std::vector<short> idxs;
    int i;
    for(i=0; i<slices*2&&i+2<slices*2; i++)
    {
        idxs.push_back(i);
        idxs.push_back(i+1);
        idxs.push_back(i+2);
    }

    {
        idxs.push_back(i);
        idxs.push_back(i+1);
        idxs.push_back(0);
    }
    {
        idxs.push_back(i);
        idxs.push_back(0);
        idxs.push_back(1);
    }

    short* s = new short[idxs.size()];
    memcpy(s, &idxs[0], idxs.size());
    return std::make_tuple(idxs.size(), s);
}

#ifndef CYCLES_H
#define CYCLES_H

#include <tuple>

extern void cycle_draw(const Vex vexs[], int slices);
extern std::tuple<int, short*> build_cycle_indexs(int slices);

#endif // CYCLES_H


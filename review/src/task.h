#ifndef TASK_H
#define TASK_H

#include <functional>
#include <iostream>

void execute(std::function<void(int)> t, int load);

#endif // TASK_H
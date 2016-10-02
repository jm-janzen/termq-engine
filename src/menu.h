#ifndef MENU_H
#define MENU_H

#include <stdlib.h>

#include <string>
#include <vector>

int init();
int run();
void close();

bool in_array(const std::string &value, const std::vector<std::string> &array);

#endif

#include <iostream>
#include <string>
#include "terminal.h"

using namespace std;

void Terminal::setterminal_name(string name)
	terminal_name = name;

void Terminal::setterminal_x(int x)
	terminal_x = x;

void Terminal::setterminal_y(int y)
	terminal_y = y;

string Terminal::getterminal_name(void)
	return terminal_name;

int Terminal::getterminal_x(void)
	return terminal_x;

int Terminal::getterminal_y(void)
	return terminal_y;

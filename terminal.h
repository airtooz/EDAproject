#ifndef _DEFINE_TERMINAL_
#define _DEFINE_TERMINAL_

#include <iostream>
#include <string>

using namespace std;

class Terminal
{
public:
	void setterminal_name(string);
	void setterminal_x(int);
	void setterminal_y(int);
	string getterminal_name(void);
	int getterminal_x(void);
	int getterminal_y(void);
private:
	string terminal_name;
	int terminal_x;
	int terminal_y;
};

#endif

#ifndef _DEFINE_CONTOUR_
#define _DEFINE_CONTOUR_

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Contour
{
public:
	Contour();
	void setnext(Contour*);
	void setprev(Contour*);
	Contour* getnext(void);
	Contour* getprev(void);
	void setcontour_x(int);
	void setcontour_y(int);
	int getcontour_x(void);
	int getcontour_y(void);
private:
	int contour_x;
	int contour_y;
	Contour* next;
	Contour* prev;
};

#endif

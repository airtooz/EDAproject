#include<iostream>
#include<string>
#include<vector>
#include"contour.h"

using namespace std;

Contour::Contour()
{
	next = NULL;
	prev = NULL;
}

void Contour::setnext(Contour* ptr)
	next = ptr;

void Contour::setprev(Contour* ptr)
	prev = ptr;

Contour* Contour::getnext()
	return next;

Contour* Contour::getprev()
	return prev;

void Contour::setcontour_x(int x)
	contour_x = x;

void Contour::setcontour_y(int y)
	contour_y = y;

int Contour::getcontour_x()
	return contour_x;

int Contour::getcontour_y()
	return contour_y;

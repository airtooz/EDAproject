// function implementations in class Module

#include <iostream>
#include <string>
#include <cstdlib>
#include "module.h"

using namespace std;

Module::Module()
{
	lchild = NULL;
	rchild = NULL;
	parent = NULL;
	block_x = 0;
	block_y = 0;
	lindex = -1;
	rindex = -1;
	pindex = -1;
}

void Module::setlchild(Module* lc)
	lchild = lc;

void Module::setrchild(Module* rc)
	rchild = rc;
	
void Module::setparent(Module* par)
	parent = par;
	
void Module::setblock_x(int x)
	block_x = x;

void Module::setblock_y(int y)
	block_y = y;

void Module::setblock_w(int w)
	block_w = w;
	
void Module::setblock_h(int h)
	block_h = h;

void Module::setblock_name(string name)
	block_name = name;
	
void Module::setblock_centerx(double x)
	centerx = x;

void Module::setblock_centery(double y)
	centery = y;

void Module::setblock_index(int id)
	index = id;

void Module::setlindex(int id)
	lindex = id;

void Module::setrindex(int id)
	rindex = id;

void Module::setpindex(int id)
	pindex = id;

Module Module::getlchild(void)
	return *lchild;

Module Module::getrchild(void)
	return *rchild;

Module Module::getparent(void)
	return *parent;

Module* Module::getlptr(void)
	return lchild;

Module* Module::getrptr(void)
	return rchild;

Module* Module::getpptr(void)
	return parent;

int Module::getblock_x(void)
	return block_x;

int Module::getblock_y(void)
	return block_y;

int Module::getblock_w(void)
	return block_w;

int Module::getblock_h(void)
	return block_h;

string Module::getblock_name(void)
	return block_name;

double Module::getblock_centerx(void)
	return centerx;

double Module::getblock_centery(void)
	return centery;

int Module::getblock_index(void)
	return index;

int Module::getlindex(void)
	return lindex;

int Module::getrindex(void)
	return rindex;

int Module::getpindex(void)
	return pindex;

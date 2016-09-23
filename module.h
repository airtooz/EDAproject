#ifndef _DEFINE_MODULE_
#define _DEFINE_MODULE_

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Module
{
public:
        Module();
        void setlchild(Module*);
        void setrchild(Module*);
        void setparent(Module*);
        void setblock_x(int);
        void setblock_y(int);
        void setblock_w(int);
        void setblock_h(int);
        void setblock_name(string);
	void setblock_centerx(double);
	void setblock_centery(double);
	void setblock_index(int);
	void setlindex(int);
	void setrindex(int);
	void setpindex(int);
        Module getlchild(void);
        Module getrchild(void);
        Module getparent(void);
        Module* getlptr(void);
        Module* getrptr(void);
        Module* getpptr(void);
        int getblock_x(void);
        int getblock_y(void);
        int getblock_w(void);
        int getblock_h(void);
        string getblock_name(void);
	double getblock_centerx(void);
	double getblock_centery(void);
	int getblock_index(void);
	int getlindex(void);
	int getrindex(void);
	int getpindex(void);
private:
        Module* lchild;
        Module* rchild;
        Module* parent;
        int block_x;
        int block_y;
        int block_w;
        int block_h;
        string block_name;
	double centerx;
	double centery;
	int index;
  	int lindex;
	int rindex;
	int pindex;
};

#endif

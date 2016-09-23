//Implementation of functions from b*tree.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>
#include "parser.h"
#include "module.h"
#include "terminal.h"
#include "net.h"
#include "contour.h"

using namespace std;

void Put(vector<Module>& blocks, Module* temp, vector<Contour>& bound)
{
	Contour* current;
	Contour leftup;
	Contour rightdown;
	Module* prev = temp->getpptr();
	if(prev==NULL)	// first block
	{
		temp->setblock_x(0);
		temp->setblock_y(0);
		leftup.setcontour_x(0);
		leftup.setcontour_y(temp->getblock_h());
		rightdown.setcontour_x(temp->getblock_w());
		rightdown.setcontour_y(0);

		bound.push_back(leftup);
		bound.push_back(rightdown);
	
		Contour* before = &bound[0];
		Contour* after = before->getnext();
	
		before->setnext(&(bound[bound.size()-2]));
		bound[bound.size()-2].setprev(before);
		bound[bound.size()-2].setnext(&(bound[bound.size()-1]));
		bound[bound.size()-1].setprev(&(bound[bound.size()-2]));
		bound[bound.size()-1].setnext(after);
		after->setprev(&(bound[bound.size()-1]));

	}
	else
	{
		if(prev->getlptr()==temp)
		{
			temp->setblock_x(prev->getblock_x()+prev->getblock_w());
		}
		else if(prev->getrptr()==temp)
		{
			temp->setblock_x(prev->getblock_x());	
		}
		Contour* ago;
		ago = &bound[0];
		current = &bound[0];
		current = current->getnext();
		while( (current->getcontour_x()) != (temp->getblock_x()))
		{
			Contour* buff_ptr = current->getnext();
			current = buff_ptr;
			ago = ago->getnext();
		}
		bound[0].setcontour_x(0);
		Contour* before = ago;

		int ymax = 0;
		if((before->getcontour_x()==0)&&(before->getcontour_y()==0))
		{

			while(current->getcontour_x() <= (temp->getblock_x()+temp->getblock_w()))
			{
				if(current->getcontour_x() == (temp->getblock_x()+temp->getblock_w()))
				{	
					current = current->getnext();
					break;
				}
				if(current->getcontour_y() > ymax)
				{
					ymax = current->getcontour_y();
				}
				Contour* buff_ptr = current->getnext();
				current = buff_ptr;
			}
				
			Contour* after = current;
			temp->setblock_y(ymax);
	
			leftup.setcontour_x(temp->getblock_x());
			leftup.setcontour_y(temp->getblock_y()+temp->getblock_h());
		
			rightdown.setcontour_x(temp->getblock_x()+temp->getblock_w());
			Contour* rdcontour = after->getprev();
			rightdown.setcontour_y(rdcontour->getcontour_y());

	
			bound.push_back(leftup);
			bound.push_back(rightdown);

			bound[0].setnext(&(bound[bound.size()-2]));
			bound[bound.size()-2].setprev(&bound[0]);
			bound[bound.size()-2].setnext(&(bound[bound.size()-1]));
			bound[bound.size()-1].setprev(&(bound[bound.size()-2]));
			bound[bound.size()-1].setnext(after);
			after->setprev(&(bound[bound.size()-1]));
	
/*			Contour* buff = &bound[0];
			while(buff!=NULL)
			{
				cout << buff->getcontour_x()<<"," << buff->getcontour_y()<<endl;
				buff = buff->getnext();
			}
*/
		}
		else
		{
			while(current->getcontour_x() <= (temp->getblock_x()+temp->getblock_w()))
			{
				if(current->getcontour_y() > ymax)
				{
					ymax = current->getcontour_y();
				}
				Contour* buff_ptr = current->getnext();
				current = buff_ptr;
			}
				
			Contour* after = current;
			temp->setblock_y(ymax);
	
			leftup.setcontour_x(temp->getblock_x());
			leftup.setcontour_y(temp->getblock_y()+temp->getblock_h());
		
			rightdown.setcontour_x(temp->getblock_x()+temp->getblock_w());
			Contour* rdcontour = after->getprev();
			rightdown.setcontour_y(rdcontour->getcontour_y());

			bound.push_back(leftup);
			bound.push_back(rightdown);

			before->setnext(&(bound[bound.size()-2]));
			bound[bound.size()-2].setprev(before);
			bound[bound.size()-2].setnext(&(bound[bound.size()-1]));
			bound[bound.size()-1].setprev(&(bound[bound.size()-2]));
			bound[bound.size()-1].setnext(after);
			after->setprev(&(bound[bound.size()-1]));

/*			Contour* buff = &bound[0];
			while(buff!=NULL)
			{
				cout << buff->getcontour_x()<<"," << buff->getcontour_y()<<endl;
				buff = buff->getnext();
			}
*/
		}
		
	}
/*
	cout << (*temp).getblock_name() << endl;
	cout << (*temp).getblock_x() << endl;
	cout << (*temp).getblock_y() << endl;
*/
}

void Packing(vector<Module>& blocks)
{
	vector<Contour> bound;
	Module* temp;
	Module* prev;
	int iter;
	int flag = 0;

	Contour start;
	Contour end;
	
	start.setcontour_x(0);
	start.setcontour_y(0);
	end.setcontour_x(1000000000);
	end.setcontour_y(0);
	
	bound.push_back(start);
	bound.push_back(end);
	
	bound[0].setnext(&bound[1]);
	bound[1].setprev(&bound[0]);

	temp = &blocks[0];

	while((*temp).getpptr()!=NULL)
	{
		Module* buff = (*temp).getpptr();
		temp = buff;
	}

	// temp == root_ptr
	
	if((*temp).getlptr()==NULL||(*temp).getrptr()==NULL)
		iter = 1;
	else
		iter = 2;
	for(int i = 0; i < iter; i++)
	{
		do
		{
			if(((*temp).getlptr() != NULL )&&(flag == 0))
			{
				Put(blocks,temp,bound);
				prev = temp;
				temp = (*temp).getlptr();
			}
			else if((*temp).getrptr() != NULL)
			{
				if(flag == 0)
				{
					Put(blocks,temp,bound);
				}
				prev = temp;
				temp = (*temp).getrptr();
				flag = 0;
			}
			else if(((*temp).getlptr() == NULL)&&((*temp).getrptr()==NULL))
			{
				Put(blocks,temp,bound);
				while( ((*temp).getrptr()==NULL)||((*temp).getrptr()==prev) )
				{
					if((*temp).getpptr() == NULL)
						break;
					prev = temp;
					temp = (*temp).getpptr();
				}
				flag = 1;
			}
			else
				cout << "Traversal Error!!" << endl;

		}while((*temp).getpptr()!=NULL);
	}
}

void Insert_Mod(vector<Module>& blocks, int index)
{
	int choose = rand()%index;
	int lr = rand()%2;
	if(lr == 0)
	{
		if(blocks[choose].getlptr() == NULL)
		{
			blocks[choose].setlchild(&blocks[index]);
			blocks[index].setparent(&blocks[choose]);
		}		
		else
		{
			Module* block_tempptr = blocks[choose].getlptr();
			blocks[index].setlchild(block_tempptr);
			block_tempptr = blocks[index].getlptr();
			(*block_tempptr).setparent(&blocks[index]);
			blocks[choose].setlchild(&blocks[index]);
			blocks[index].setparent(&blocks[choose]);
		}
			
	}
	else
	{
		if(blocks[choose].getrptr() == NULL)
		{
			blocks[choose].setrchild(&blocks[index]);
			blocks[index].setparent(&blocks[choose]);
		}		
		else
		{
			Module* block_tempptr = blocks[choose].getrptr();
			blocks[index].setrchild(block_tempptr);
			block_tempptr = blocks[index].getrptr();
			(*block_tempptr).setparent(&blocks[index]);
			blocks[choose].setrchild(&blocks[index]);
			blocks[index].setparent(&blocks[choose]);
		}
	}
}
void Reinsert_Mod(vector<Module>& blocks, Module* inptr)
{
	int choose = rand()%(blocks.size());
	while(&blocks[choose] == inptr)
	{
		choose = rand()%(blocks.size());
	}
	int lr = rand()%2;
	if(lr == 0)
	{
		if(blocks[choose].getlptr() == NULL)
		{
			blocks[choose].setlchild(inptr);
			(*inptr).setparent(&blocks[choose]);
		}		
		else
		{
			Module* block_tempptr = blocks[choose].getlptr();
			(*inptr).setlchild(block_tempptr);
			block_tempptr = (*inptr).getlptr();
			(*block_tempptr).setparent(inptr);
			blocks[choose].setlchild(inptr);
			(*inptr).setparent(&blocks[choose]);
		}
			
	}
	else
	{
		if(blocks[choose].getrptr() == NULL)
		{
			blocks[choose].setrchild(inptr);
			(*inptr).setparent(&blocks[choose]);
		}		
		else
		{
			Module* block_tempptr = blocks[choose].getrptr();
			(*inptr).setrchild(block_tempptr);
			block_tempptr = (*inptr).getrptr();
			(*block_tempptr).setparent(inptr);
			blocks[choose].setrchild(inptr);
			(*inptr).setparent(&blocks[choose]);
		}

	}
	
}
void Move(vector<Module>& blocks)
{
//	cout << "Choosed Moving" << endl;
	int index = rand()%blocks.size();
	if((blocks[index].getlptr() == NULL) && (blocks[index].getrptr() == NULL))	// Node degree 0
	{
		Module* temp_ptr = blocks[index].getpptr();
		blocks[index].setparent(NULL);
		if((*temp_ptr).getlptr() == &blocks[index])
		{
			(*temp_ptr).setlchild(NULL);
		}
		else if((*temp_ptr).getrptr() == &blocks[index])
		{
			(*temp_ptr).setrchild(NULL);
		}
		else
		{
			cout << "Error occur at Tree Delete!!!" << endl;
		}
		Reinsert_Mod(blocks, &blocks[index]);
	}
	else if((blocks[index].getlptr() != NULL) && (blocks[index].getrptr() != NULL))// Node degree 2
	{
		Module* temp = &blocks[index];
		int lr;
		while( ((*temp).getlptr() != NULL) || ((*temp).getrptr() != NULL) )
		{
//			cout << "!!" << endl;	
			if( ((*temp).getlptr() != NULL) && ((*temp).getrptr() != NULL) )
			{	
				Module* cptr;
				lr = rand()%2;
				if(lr == 0)
					cptr = (*temp).getlptr();	
				else
					cptr = (*temp).getrptr();	
				
				int temp_w = (*temp).getblock_w();
				(*temp).setblock_w((*cptr).getblock_w());
				(*cptr).setblock_w(temp_w);

				int temp_h = (*temp).getblock_h();
				(*temp).setblock_h((*cptr).getblock_h());
				(*cptr).setblock_h(temp_h);

				string temp_name = (*temp).getblock_name();
				(*temp).setblock_name((*cptr).getblock_name());
				(*cptr).setblock_name(temp_name);
				
				temp = cptr;
			}
			else if( ((*temp).getlptr() != NULL) && ((*temp).getrptr() == NULL) )
			{
				Module* cptr = (*temp).getlptr();	
				
				int temp_w = (*temp).getblock_w();
				(*temp).setblock_w((*cptr).getblock_w());
				(*cptr).setblock_w(temp_w);

				int temp_h = (*temp).getblock_h();
				(*temp).setblock_h((*cptr).getblock_h());
				(*cptr).setblock_h(temp_h);

				string temp_name = (*temp).getblock_name();
				(*temp).setblock_name((*cptr).getblock_name());
				(*cptr).setblock_name(temp_name);
				
				temp = cptr;
					
			}	
			else if( ((*temp).getlptr() == NULL) && ((*temp).getrptr() != NULL) )
			{
				Module* cptr = (*temp).getrptr();	
				
				int temp_w = (*temp).getblock_w();
				(*temp).setblock_w((*cptr).getblock_w());
				(*cptr).setblock_w(temp_w);

				int temp_h = (*temp).getblock_h();
				(*temp).setblock_h((*cptr).getblock_h());
				(*cptr).setblock_h(temp_h);

				string temp_name = (*temp).getblock_name();
				(*temp).setblock_name((*cptr).getblock_name());
				(*cptr).setblock_name(temp_name);
				
				temp = cptr;
			}
			else
				cout << "Never come here!! " << endl;
		}

		Module* temp_pptr = (*temp).getpptr();
		(*temp).setparent(NULL);
		if((*temp_pptr).getlptr() == temp)
		{
			(*temp_pptr).setlchild(NULL);
		}
		else if((*temp_pptr).getrptr() == temp)
		{
			(*temp_pptr).setrchild(NULL);
		}
		else
		{
			cout << "Error occur at Tree Delete!!!" << endl;
		}
		Reinsert_Mod(blocks, temp);

//		;
	}
	else	// Node degree 1
	{
		if(blocks[index].getlptr() != NULL)
		{
			if(blocks[index].getpptr() == NULL)
			{
				Module* temp_ptr = blocks[index].getlptr();
				(*temp_ptr).setparent(NULL);
				blocks[index].setlchild(NULL);
			}
			else
			{
				Module* temp_ptr1 = blocks[index].getlptr();
				Module* temp_ptr2 = blocks[index].getpptr();
				(*temp_ptr1).setparent(temp_ptr2);
				if((*temp_ptr2).getlptr() == &blocks[index])
				{
					(*temp_ptr2).setlchild(temp_ptr1);
					blocks[index].setparent(NULL);
					blocks[index].setlchild(NULL);
				}
				else if((*temp_ptr2).getrptr() == &blocks[index])
				{
					(*temp_ptr2).setrchild(temp_ptr1);
					blocks[index].setparent(NULL);
					blocks[index].setlchild(NULL);
				}
				else
				{
					cout << "Error in Delete Mod!!" << endl;
				}
			}
		}
		else if(blocks[index].getrptr() != NULL)
		{
			if(blocks[index].getpptr() == NULL)
			{
				Module* temp_ptr = blocks[index].getrptr();
				(*temp_ptr).setparent(NULL);
				blocks[index].setrchild(NULL);
			}
			else
			{
				Module* temp_ptr1 = blocks[index].getrptr();
				Module* temp_ptr2 = blocks[index].getpptr();
				(*temp_ptr1).setparent(temp_ptr2);
				if((*temp_ptr2).getlptr() == &blocks[index])
				{
					(*temp_ptr2).setlchild(temp_ptr1);
					blocks[index].setparent(NULL);
					blocks[index].setrchild(NULL);
				}
				else if((*temp_ptr2).getrptr() == &blocks[index])
				{
					(*temp_ptr2).setrchild(temp_ptr1);
					blocks[index].setparent(NULL);
					blocks[index].setrchild(NULL);
				}
				else
				{
					cout << "Error in Delete Mod!!" << endl;
				}
			}
			
		}
		else
		{
			cout << "Error occur at Tree Delete!!!" << endl;
		}
		Reinsert_Mod(blocks, &blocks[index]);
	}
}

void Setindex(vector<Module>& blocks)
{
	for(int i = 0; i < blocks.size();i++)
	{
		if(blocks[i].getlptr()!=NULL)
		{
			Module* temp = blocks[i].getlptr();
			blocks[i].setlindex(temp->getblock_index());
		}
		if(blocks[i].getrptr()!=NULL)
		{
			Module* temp = blocks[i].getrptr();
			blocks[i].setrindex(temp->getblock_index());
		}
		if(blocks[i].getpptr()!=NULL)
		{
			Module* temp = blocks[i].getpptr();
			blocks[i].setpindex(temp->getblock_index());
		}
	}
	
}
void Initialize_Floorplan(vector<Module>& blocks)
{
	cout << "Initializing Floorplan" << endl;

	for(int i = 0; i < blocks.size(); i++)
	{
		if(i != 0)
			Insert_Mod(blocks,i);
	}
	Setindex(blocks);
}

void Rotate(vector<Module>& blocks)
{
//	cout << "Choosed Rotation" << endl;

	int index = rand()%blocks.size();
	int w = blocks[index].getblock_w();
	int h = blocks[index].getblock_h();
	blocks[index].setblock_w(h);
	blocks[index].setblock_h(w);
}

void Switch(vector<Module>& blocks)
{
//	cout << "Choosed Switching" << endl;
	int num1 = rand()%blocks.size();
	int num2 = rand()%blocks.size();
	while(num1 == num2)
	{
		num2 = rand()%blocks.size();
	}

	int temp_w = blocks[num1].getblock_w();
	blocks[num1].setblock_w(blocks[num2].getblock_w());
	blocks[num2].setblock_w(temp_w);
	
	int temp_h = blocks[num1].getblock_h();
	blocks[num1].setblock_h(blocks[num2].getblock_h());
	blocks[num2].setblock_h(temp_h);

	string temp_name = blocks[num1].getblock_name();
	blocks[num1].setblock_name(blocks[num2].getblock_name());
	blocks[num2].setblock_name(temp_name);
}

double Count_HPWL(vector<Module>& blocks,vector<Terminal>& terminals,vector<Net>& nets)
{
	double HPWL = 0;
	for(int i = 0; i < blocks.size();i++)
	{
		blocks[i].setblock_centerx(blocks[i].getblock_x()+(blocks[i].getblock_w())/2);
		blocks[i].setblock_centery(blocks[i].getblock_y()+(blocks[i].getblock_h())/2);
	}
	for(int i = 0; i < nets.size(); i++)
	{
		double x_max = 0;
		double x_min = 100000000;
		double y_max = 0;
		double y_min = 100000000;
		vector<string> test =  nets[i].getconnect();
		for(int j = 0; j < test.size();j++)
		{
			int flag = 0;
			for(int k = 0; k < blocks.size();k++)
			{
				if(blocks[k].getblock_name()==test[j])
				{
					if(blocks[k].getblock_centerx()<x_min)
					{
						x_min = blocks[k].getblock_centerx();
					}
					if(blocks[k].getblock_centerx()>x_max)
					{
						x_max = blocks[k].getblock_centerx();
					}
					if(blocks[k].getblock_centery()<y_min)
					{
						y_min = blocks[k].getblock_centery();
					}
					if(blocks[k].getblock_centery()>y_max)
					{
						y_max = blocks[k].getblock_centery();
					}					
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				for(int k = 0; k < terminals.size(); k++)
				{
					if(terminals[k].getterminal_name() == test[j])
					{
						if(terminals[k].getterminal_x() < x_min)
						{
							x_min = terminals[k].getterminal_x();
						}
						if(terminals[k].getterminal_x() > x_max)
						{
							x_max = terminals[k].getterminal_x();
						}
						if(terminals[k].getterminal_y() < y_min)
						{
							y_min = terminals[k].getterminal_y();
						}
						if(terminals[k].getterminal_y() > y_max)
						{
							y_max = terminals[k].getterminal_y();
						}
						break;
					}
				}
			}
		}
		HPWL+=(x_max+y_max-x_min-y_min);
	}
	return HPWL;
}
void Perturb(vector<Module>& blocks)
{
	int op_rand = 0;
//	cout << "Perturb into a neighborhood floorplan" << endl;
	op_rand = (rand()%3)+1;

	switch(op_rand)
	{
	case 1:
		Rotate(blocks);
		break;
	case 2:
		Move(blocks);
		Setindex(blocks);
		break;
	case 3:
		Switch(blocks);
		break;
	}
}

double Count_Area(vector<Module>& blocks)
{
	int x_max = 0;
	int y_max = 0;
	double area;
	for(int i = 0; i < blocks.size();i++)
	{
		if(blocks[i].getblock_x()+blocks[i].getblock_w() > x_max)
		{
			x_max = blocks[i].getblock_x()+blocks[i].getblock_w();
		}
		if(blocks[i].getblock_y()+blocks[i].getblock_h() > y_max)
		{
			y_max = blocks[i].getblock_y()+blocks[i].getblock_h();
		}
	}
	area = x_max*y_max;
	
	return area;
}

double Costfunc(vector<Module>& blocks, vector<Terminal>& terminals, vector<Net>& nets,double alpha,double Anorm, double Wnorm, double w, double h)
{
	double area;
	double HPWL;
	double outline;
	double cost;

	double x_max = 0;
	double y_max = 0;
	for(int i = 0; i < blocks.size();i++)
	{
		if(blocks[i].getblock_x()+blocks[i].getblock_w() > x_max)
		{
			x_max = blocks[i].getblock_x()+blocks[i].getblock_w();
		}
		if(blocks[i].getblock_y()+blocks[i].getblock_h() > y_max)
		{
			y_max = blocks[i].getblock_y()+blocks[i].getblock_h();
		}
	}
	
	area = x_max*y_max;

	HPWL = Count_HPWL(blocks,terminals,nets);

	double costw = 0;
	double costh = 0;

	if(x_max > w)
	{
		costw = 100*(x_max-w)/w;
	}
	if(y_max > h)
	{
		costh = 100*(y_max-h)/h;
	}

	cost = alpha*area/Anorm + (1-alpha)*HPWL/Wnorm + costw+ costh + 50*abs(1-(x_max/y_max));
	return cost;
	
}

void StoreBest(vector<Module>& Best,vector<Module>& blocks)
{
	for(int i = 0; i < blocks.size(); i++)
	{
		Best[i].setblock_name(blocks[i].getblock_name());
		Best[i].setblock_x(blocks[i].getblock_x());
		Best[i].setblock_y(blocks[i].getblock_y());
		Best[i].setblock_w(blocks[i].getblock_w());
		Best[i].setblock_h(blocks[i].getblock_h());
	}
}

void PerturbBack(vector<Module>& blocks,vector<int>& left,vector<int>& right,vector<int>& parent,vector<int>& width,vector<int>& height,vector<string>& name)
{
	for(int i = 0; i < blocks.size();i++)
	{
		blocks[i].setlindex(left[i]);
		blocks[i].setrindex(right[i]);
		blocks[i].setpindex(parent[i]);
		blocks[i].setblock_w(width[i]);
		blocks[i].setblock_h(height[i]);
		blocks[i].setblock_name(name[i]);

		int l = blocks[i].getlindex();
		int r = blocks[i].getrindex();
		int p = blocks[i].getpindex();
		
		if(l == -1)
			blocks[i].setlchild(NULL);
		else
			blocks[i].setlchild(&blocks[l]);
		if(r == -1)
			blocks[i].setrchild(NULL);
		else
			blocks[i].setrchild(&blocks[r]);
		if(p == -1)
			blocks[i].setparent(NULL);
		else
			blocks[i].setparent(&blocks[p]);
		
	}
}

void Maintain(vector<Module>& blocks,vector<int>& left,vector<int>& right,vector<int>& parent,vector<int>& width,vector<int>& height,vector<string>& name)
{
	for(int i = 0; i < blocks.size(); i++)
	{
		if(blocks[i].getlptr()==NULL)
			left[i] = -1;
		else
			left[i] = blocks[i].getlchild().getblock_index();
		if(blocks[i].getrptr()==NULL)
			right[i] = -1;
		else
			right[i] = blocks[i].getrchild().getblock_index();
		if(blocks[i].getpptr()==NULL)
			parent[i] = -1;
		else
			parent[i] = blocks[i].getparent().getblock_index();
		width[i] = blocks[i].getblock_w();
		height[i] = blocks[i].getblock_h();
		name[i] = blocks[i].getblock_name();
	}
}

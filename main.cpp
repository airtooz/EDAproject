// b*tree program

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>
#include "utility.h"

using namespace std;
void Initialize_Floorplan(vector<Module>&);
void Packing(vector<Module>&);
void Put(vector<Module>&, Module*,vector<Contour>&);
void Insert_Mod(vector<Module>&, int);
void Reinsert_Mod(vector<Module>&, Module*);
void Perturb(vector<Module>&);
void Rotate(vector<Module>&);
void Switch(vector<Module>&);
void Move(vector<Module>&);
double Costfunc(vector<Module>&,vector<Terminal>&,vector<Net>&,double,double,double,double,double);
double Count_HPWL(vector<Module>&,vector<Terminal>&,vector<Net>&);
double Count_Area(vector<Module>&);
void StoreBest(vector<Module>&,vector<Module>&);
void plotBoxPLT( ofstream& stream, int &cnt, double x1, double y1, double x2, double y2, const string color );
void Setindex(vector<Module>&);
void PerturbBack(vector<Module>&,vector<int>&,vector<int>&,vector<int>&,vector<int>&,vector<int>&,vector<string>&);
void Maintain(vector<Module>& blocks,vector<int>& left,vector<int>& right,vector<int>& parent,vector<int>& width,vector<int>& height,vector<string>& name);

int main(int argc, char** argv)		// main function
{

//-------Initial parameters-------
for(int times = 0; times < 10; times++)
{
	double alpha = atof(argv[1]);		// the cost function parameter
	double Temperature;
	double InitialP = 0.99999999999;
	double epsillon = 0.01;
	double ratio = 0.85;
	double iter_num ;
	
//-------Initial parameters--------

//-------Clock Starts--------------
 
	AlgTimer t;
	t.Begin();

	srand(time(0));

//-------Clock Starts-------------

//-------Input Blocks and Terminals-------------------

	ifstream blocks_in(argv[2],ios::in);
	if(!blocks_in)
	{
		cerr << "blocks_in could not be opened!!!" << endl;
		exit(1);
	}

	ifstream term_in(argv[4],ios::in);
	if(!term_in)
	{
		cerr << "term_in could not be opened!!!" << endl;
		exit(1);
	}
	
	string discard;
	double hardarea = 0;
	double outline_w;
	double outline_h;
	int block_num;
	int terminal_num;
	vector <Module> blocks;
	vector <Terminal> terminals;

	for(int i = 0; i < 8; i++)
	{
		blocks_in >> discard;
	}
	blocks_in >> block_num;
	blocks_in >> discard;
	blocks_in >> discard;
	blocks_in >> terminal_num;


	for(int i = 0; i < block_num; i++)
	{
		Module b_temp;
		string bname;
		string discard;
		string info;
		int bw;
		int bh; 
		blocks_in >> bname;
		blocks_in >> discard;
		blocks_in >> discard;
		blocks_in >> discard;
		blocks_in >> discard;
		blocks_in >> discard;
		blocks_in >> discard;
		blocks_in >> discard;
		info = discard.substr(1,discard.length()-2);
		bw = atoi(info.c_str());
		blocks_in >> discard;
		info = discard.substr(0,discard.length()-1);
		bh = atoi(info.c_str());
		blocks_in >> discard;
		blocks_in >> discard;

		hardarea += (bw*bh);

		b_temp.setblock_name(bname);
		b_temp.setblock_w(bw);
		b_temp.setblock_h(bh);
		b_temp.setblock_index(i);
		blocks.push_back(b_temp);	 
	}

	outline_w = ceil(sqrt(hardarea*1.1)); // dead space 10%
	outline_h = outline_w;
	
	cout << outline_w << endl;

	for(int j = 0; j < block_num+1 ;j++)
	{
		term_in >> discard;
		term_in >> discard;
		term_in >> discard;
	}

	for(int i = 0; i < terminal_num; i++)
	{
		Terminal t_temp;
		string tname;
		int tx;
		int ty;
		term_in >> tname;
		term_in >> tx;
		term_in >> ty;
		t_temp.setterminal_name(tname);
		t_temp.setterminal_x(tx);
		t_temp.setterminal_y(ty);
		terminals.push_back(t_temp);	
	}

//-------Input Blocks and Terminals------------------


//-------Input Nets----------------------------------

	ifstream net_in(argv[3], ios::in);
	if(!net_in)
	{
		cerr << "net_in could not be opened!!!" << endl;
		exit(1);
	}

	vector<Net> nets;
	int net_num;

	net_in >> discard;
	net_in >> discard;
	net_in >> discard;
	net_in >> discard;
	net_in >> discard;
	net_in >> net_num;
	net_in >> discard;
	net_in >> discard;
	net_in >> discard;
	
	for(int i = 0; i < net_num; i++)
	{
		Net n_temp;
		int net_d;
		vector<string> net_con;
		net_in >> discard;
		net_in >> discard;
		net_in >> net_d;
		
		n_temp.setdegree(net_d);

		for(int j = 0; j < net_d; j++)
		{
			string net_con_temp;
			net_in >> net_con_temp;
			net_in >> discard;
			net_con.push_back(net_con_temp);
		}
		
		n_temp.setconnect(net_con);
		nets.push_back(n_temp);
		
	}

//-------Input Nets----------------------------------

	
	Initialize_Floorplan(blocks);
	vector<int> left;
	vector<int> right;
	vector<int> parent;
	vector<int> width;
	vector<int> height;
	vector<string> name;
	for(int i = 0; i < blocks.size(); i++)
	{
		left.push_back(blocks[i].getlindex());
		right.push_back(blocks[i].getrindex());
		parent.push_back(blocks[i].getpindex());
		width.push_back(blocks[i].getblock_w());
		height.push_back(blocks[i].getblock_h());
		name.push_back(blocks[i].getblock_name());
	}
//--------------Setting Initial Floorplan Parameters---------------------

//--------------Normalize Area and HPWL---------------------
	double Anorm = 0;
	double Wnorm = 0;
	for(int i = 0; i < blocks.size()*3; i++)
	{
		Perturb(blocks);
		Packing(blocks);
	
		Wnorm += Count_HPWL(blocks,terminals,nets);
		Anorm += Count_Area(blocks);
		PerturbBack(blocks,left,right,parent,width,height,name);
	}

	Anorm /= (block_num*3);
	Wnorm /= (block_num*3);
//--------------Normalize Area and HPWL---------------------

//--------------Initializing Temperature--------------------

	Packing(blocks);
	double InitialCost = Costfunc(blocks,terminals,nets,alpha,Anorm,Wnorm,outline_w,outline_h);
	cout << "Initial Cost is " << InitialCost << endl;

	int upcount = 0;
	double averageup = 0;
	
	for(int i = 0; i < blocks.size()*3; i++)
	{
		Perturb(blocks);
		Packing(blocks);
		double Cost = Costfunc(blocks,terminals,nets,alpha,Anorm,Wnorm,outline_w,outline_h);
		if(InitialCost < Cost)	// uphill move
		{
			upcount++;
			averageup += (Cost-InitialCost);
		}
		PerturbBack(blocks,left,right,parent,width,height,name);
	}
	if(upcount == 0)
		Temperature = -1/log(InitialP);
	else
	{
		averageup /= upcount;
		Temperature = -averageup/log(InitialP);
	}
	cout <<"Initial temperature is " << Temperature << endl;
	
//--------------Initializing Temperature--------------------




//---------------Simulated Annealing--------------------------

	Packing(blocks);
	double Cost_best = Costfunc(blocks,terminals,nets,alpha,Anorm,Wnorm,outline_w, outline_h);
	double Area_best = Count_Area(blocks);
	double HPWL_best = Count_HPWL(blocks,terminals,nets);
	vector<Module> Best;

	for(int i = 0; i < blocks.size(); i++)
	{
		Module temp;
		temp.setblock_name(blocks[i].getblock_name());
		temp.setblock_x(blocks[i].getblock_x());
		temp.setblock_y(blocks[i].getblock_y());
		temp.setblock_w(blocks[i].getblock_w());
		temp.setblock_h(blocks[i].getblock_h());
		
		Best.push_back(temp);
	}
	double CostNow;
	double CostPrev;
	double CostNext;
	double reject;
	Perturb(blocks);
	Packing(blocks);

	Maintain(blocks,left,right,parent,width,height,name);
	Perturb(blocks);
	PerturbBack(blocks,left,right,parent,width,height,name);
	
	iter_num = 100;

	do
	{
		reject = 0;
		for(int i = 0; i < iter_num; i++)
		{
			Packing(blocks);	// Floorplan S
			CostPrev = Costfunc(blocks,terminals,nets,alpha,Anorm,Wnorm,outline_w,outline_h);

			Perturb(blocks);
			Packing(blocks);	//Floorplan S'
			CostNext = Costfunc(blocks,terminals,nets,alpha,Anorm,Wnorm,outline_w,outline_h);
			
			if(CostNext <= CostPrev)
			{
				Maintain(blocks,left,right,parent,width,height,name);
				CostNow = CostNext;
			}
			else
			{
				double randnum = rand()%RAND_MAX;
				if(randnum <= exp((CostPrev-CostNext)/Temperature))
				{
					Maintain(blocks,left,right,parent,width,height,name);
					CostNow = CostNext;
				}
				else
				{
					PerturbBack(blocks,left,right,parent,width,height,name);
					Packing(blocks);
					CostNow = CostPrev;
					reject++;
				}
			}
			if(Cost_best > CostNow)
			{
				StoreBest(Best,blocks);
				Cost_best = CostNow;
				Area_best = Count_Area(blocks);
				HPWL_best = Count_HPWL(blocks,terminals,nets);
			}
		}
		Temperature = ratio*Temperature;
	}while((Temperature > epsillon));	// while not frozen and rejection rate low

	cout << "Best Cost is: "<<Cost_best<< endl;
	cout << "Resulting Area is: "<<Area_best<< endl;
	cout << "Resulting Wirelength is: "<<HPWL_best<< endl;
	cout << "Deadspace is: "<<((Area_best/hardarea)-1)*100 << " %" << endl;
//---------------Simulated Annealing--------------------------

	cout <<  "Runtime is: "<<t.End() <<endl;

//---------------Draw Best Floorplan--------------------------

	double x1=0, x2=outline_w*1.2, y1=0, y2=outline_h*1.2;

    	ofstream outfile( argv[5] , ios::out );

	outfile << "set title \"" << argv[4] << "\"" << endl;
    	outfile << "set size ratio -1" << endl;
    	outfile << "set nokey" << endl << endl;
    	outfile << "set xrange [" << x1 << ":" << x2 << "]" << endl;
    	outfile << "set yrange [" << y1 << ":" << y2 << "]" << endl;

    	int count = 1;
    	outfile << "# bounding box" << endl;
    	plotBoxPLT( outfile, count, 0, 0, x2, y2, "#FFE153" );	
	outfile << "# outline" << endl;
	plotBoxPLT( outfile, count, 0, 0, outline_w, outline_h, "#12FBA1");
	outfile << "# modules" << endl;
	for(size_t i=0; i<Best.size(); ++i)
	{
		plotBoxPLT( outfile, count, Best[i].getblock_x(), Best[i].getblock_y(), Best[i].getblock_x()+Best[i].getblock_w(), Best[i].getblock_y()+Best[i].getblock_h(), "#FE4F81" );
	}
   	outfile << "plot[:][:] '-' w l lt 3" << endl;
   	outfile << "0,0" << endl << "0,0" << endl;
   	outfile << "EOF" << endl;
   	outfile << "pause -1 'Press any key to close.'" << endl;
   	outfile.close();

//---------------Draw Best Floorplan--------------------------
}	
	return 0;

}

void plotBoxPLT( ofstream& stream, int &cnt, double x1, double y1, double x2, double y2, const string color )
{
    stream << "set object " << cnt << " rectangle from "
           << x1 << "," << y1 << " to " << x2 << "," << y2
	   << " lw 2 fillstyle transparent solid 0.5"
	   << " border rgb \"" <<  color << "\" fillcolor rgb  \"" <<  color << "\" behind" << endl;

    ++cnt;
}

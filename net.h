#ifndef _DEFINE_NET_
#define _DEFINE_NET_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Net
{
public:
	void setdegree(int);
	void setconnect(vector <string>);
	int getdegree(void);
	vector <string> getconnect(void);
private:
	int net_degree;
	vector <string> net_connect;
};

#endif

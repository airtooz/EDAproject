#include<iostream>
#include<vector>
#include<string>
#include"net.h"

using namespace std;

void Net::setdegree(int d)
{
	net_degree = d;
}
void Net::setconnect(vector <string> connect)
{
	net_connect = connect;
}
int Net::getdegree(void)
{
	return net_degree;
}
vector <string> Net::getconnect(void)
{
	return net_connect;
}

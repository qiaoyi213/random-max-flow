#include "jngen.h"
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

string numtostr(int num){
	stringstream ss;
	ss<<num;
	string res;
	ss >> res;
	return res;
}

int main(){
	int N, V, E, C;
	cout<<"Enter the total number of case: ";
	cin>>N;
	cout<<"Enter the maximum number of vertex: ";
	cin>>V;
	cout<<"Enter the maximum number of edge: ";
	cin>>E;
	cout<<"Enter the maximum cost: ";
	cin>>C;

	while(N--){
		ofstream out;
		out.open(numtostr(N) + ".in");
		out<<numtostr(V) + " " + numtostr(E)<<endl;
		Graph g = Graph::random(V,E).connected().g().shuffled();
		g.setEdgeWeights(Array::random(E,1,C));
		out<<g.add1()<<endl;
		out.close();
	}
}

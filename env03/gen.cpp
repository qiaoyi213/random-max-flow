#include "jngen.h"
#include<cmath>
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
int fullyconnect(int V){
	return (V*(V-1))/2;
}

int main(){
	int V,E,C;
	C = 5000;
	for(int N = 5;N <= 100;N++){
		for(int i=0;i<5;i++){
			ofstream out;
			out.open(numtostr(5*(N-5)+i) + ".in");
			V = 50;
			E = ceil(fullyconnect(V)*N/100);
			out<<numtostr(V) + " " + numtostr(E)<<endl;
			Graph g = Graph::random(V,E).connected().g().shuffled();
			g.setEdgeWeights(Array::random(E,1,C));
			out<<g.add1()<<endl;
			out.close();
		}
	}
}

#include<iostream>
#include<random>
#include<set>
#include<sstream>
#include<fstream>
#include<vector>
#include<queue>
#define MAX LLONG_MAX
#define int long long 
using namespace std;
typedef int Graph[55][55];
Graph C, R; //Capacity, Flow, Remain
int parent[55], flow[55];
int n, m;
int cost;
set<pair<int, int> > a_s;
int bfs(int s, int t){
	memset(parent, 0, sizeof(parent));	
	memset(flow, 0, sizeof(flow));
	queue<int> q;
	q.push(s);
	parent[s] = s;
	flow[s] = MAX;
	int current;
	while(!q.empty()){
		current = q.front();
		q.pop();
		for(int i=1;i<=n;i++){
			if(R[current][i] > 0 && parent[i] == 0){
				parent[i] = current;
				flow[i] = min(R[current][i], flow[current]);
				if(i == t){
					return flow[t];
				}
				q.push(i);
			}
		}
	}
	return 0;	
}
void edmonds_karp(int s, int t){
	memcpy(R, C, sizeof(C));
	while(1){
		int f = bfs(1,2);
		if(f == 0)break;
		int s = parent[2], t = 2; 
		while(s != t){
			R[s][t] -= f;
			t = s;
			s = parent[t];	
		}
	}

	for(int i=1;i<=n;i++){
		if(flow[i] > 0){
			for(int j=1;j<=n;j++){
				if(flow[j] == 0 && C[i][j] != 0){
					a_s.insert(make_pair(i,j));
					cost += C[i][j];
				}
			}
		}
	}
}
string numtostr(int num){
	stringstream ss;
	ss << num;
	string res;
	ss >> res;
	return res;
}
int32_t main(){
	for(int N=0;N<10000;N++){	
		clock_t a,b;
		ifstream in;
		ofstream out;
		in.open("test_data/" + numtostr(N) + ".in");
		out.open("preflow_ans/" + numtostr(N) + ".out");
		in>>n>>m;
		memset(R,0, sizeof(R));
		memset(C,0,sizeof(C));
		for(int i=0;i<m;i++){
			int a, b, c;
			in>>a>>b>>c;
			C[a][b] = c;
			C[b][a] = c;
		}
		cost = 0;
		a = clock();
		edmonds_karp(1,2);
		b = clock();
		out<<cost<<endl;
		out<<double(b-a)/CLOCKS_PER_SEC<<endl;
		for(auto e: a_s){
			out<<e.first<<" "<<e.second<<endl;
		}
		in.close();
		out.close();
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
typedef int Graph[55][55];
Graph C, R; //Capacity, Flow, Remain
int parent[55], flow[55];
int n, m;
int bfs(int s, int t){
	memset(parent, 0, sizeof(parent));	
	memset(flow, 0, sizeof(flow));
	queue<int> q;
	q.push(s);
	parent[s] = s;
	flow[s] = INT_MAX;
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
void fordFulkerson(int s, int t){
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
					cout<<i<<" "<<j<<endl;
				}
			}
		}
	}
	cout<<endl;
}
int main(){
	while(cin>>n>>m){
		if(n == 0 && m == 0)break;
		memset(R,0, sizeof(R));
		memset(C,0,sizeof(C));
		for(int i=0;i<m;i++){
			int a, b, c;
			cin>>a>>b>>c;
			C[a][b] = c;
			C[b][a] = c;
		}
		fordFulkerson(1,2);
	}
	return 0;
}

#include<iostream>
#include<random>
#include<set>
#define MAX 1e9
using namespace std;

class edge{
public:
	int u, v, c;
	edge(){};
	edge(int U, int V, int C){
		u = U;
		v = V;
		c = C;
	}
};
int parent[55], Rank[55];
int find(int node){
	if(node == parent[node]) return node;
	return parent[node] = find(parent[node]);
}
void Union(int u, int v){
	u = find(u);
	v = find(v);

	if(u != v){
		if(Rank[u] < Rank[v]){
			int temp = u;
			u = v;
			v = temp;
		}
		parent[v] = u;

		if(Rank[u] == Rank[v]){
			Rank[u]++;
		}
	}
}
int V,E;

int main(){
	mt19937 rng(random_device{}());
	while(cin>>V>>E){
		if(V == 0 && E == 0)break;
		edge *e = new edge[E];
		for(int i=0;i<E;i++){
			int a,b,c;
			cin>>a>>b>>c;
			e[i] = edge(a,b,c);
		}
		int times = 5000;
		int ans = MAX;
		set<pair<int, int> > a_s;
		while(times){
			int tmp = 0;
			for(int i=1;i<=V;i++){
				parent[i] = i;
				Rank[i] = 0;
			}
			set<pair<int, int> >s;
			int vertices = V;
			bool check[E];
			for(int i=0;i<E;i++)check[i] = 0;
			while(vertices > 2){
				int i = rand() % E;
				check[i] = 1;
				int set1 = find(e[i].u);
				int set2 = find(e[i].v);

				if(set1 != set2 && !((set1 == find(1) && set2 == find(2)) || (set1 == find(2) && set2 == find(1)))){
					Union(e[i].u, e[i].v);
					vertices--;
				}
				bool flag = 1;
				for(int j=0;j<E;j++){
					if(check[j] == 0){
						flag = 0;
						break;
					}
				}
				
				if(flag){
					break;
				}
			}
		
			for(int i=0;i<E;i++){
				int set1 = find(e[i].u);
				int set2 = find(e[i].v);
				if(set1 != set2){
					s.insert(make_pair(e[i].u, e[i].v));
					tmp += e[i].c;
				}
			}
			if(tmp < ans){
				a_s = s;
				ans = tmp;
			}
			times--;
		}
		cout<<ans<<endl;
		for(auto e:a_s){
			cout<<e.first<<" "<<e.second<<endl;
		}
		cout<<endl;
		
	}
}

#include<iostream>
#include<random>
#include<set>
#include<sstream>
#include<fstream>
#include<ctime>
#define MAX INT_MAX
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
string numtostr(int num){
	stringstream ss;
	ss<<num;
	string res;
	ss >> res;
	return res;
}
int V,E;

int32_t main(){
	mt19937 rng(random_device{}());
	for(int N=0;N<480;N++){
		clock_t a,b;
		ifstream in;
		ofstream out;
		in.open("test_data/" + numtostr(N) + ".in");
		out.open("random_ans_2500/" + numtostr(N) + ".out");
		in>>V>>E;
		edge *e = new edge[E];
		for(int i=0;i<E;i++){
			int a,b,c;
			in>>a>>b>>c;
			e[i] = edge(a,b,c);
		}
		int times = 2500;
		int ans = MAX;
		set<pair<int, int> > a_s;
		a = clock();
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
		b = clock();
		out<<ans<<endl;
		out<<double(b-a)/CLOCKS_PER_SEC<<endl;
		for(auto e:a_s){
			out<<e.first<<" "<<e.second<<endl;
		}
		out<<endl;
	}
	return 0;
}

#include <bits/stdc++.h>

using namespace std;
struct DSU{
	vector<int> e;
	void init(int n){e = vector<int>(n, -1);}
	int get(int x){return (e[x] < 0 ? x : e[x] = get(e[x]));}
	bool same(int x, int y){return get(x) == get(y);}
	int size(int x){return -e[get(x)];}
	bool unite(int x, int y){
		x = get(x), y = get(y); 
		if(x == y) return 0; 
		if(e[x] > e[y]) 
			swap(x, y);
		e[x] += e[y]; e[y] = x; 
		return 1;
	}
};	
struct edge{
	int u, v, w; 
};

int mst(vector<edge>& e, int n){
	sort(e.begin(), e.end(), [](edge& a, edge& b){
		if(a.w < b.w)
			return true; 

		return false;
	}); 
	DSU s;
	s.init(n); 
	int cost = 0; 
	for(auto& x : e){
		if(s.same(x.u, x.v)) continue; 
		s.unite(x.u, x.v);
		cost += x.w; 
	}

	return (s.size(0) == n ? cost : -1); 

}
int32_t main(){
	int n, w;
	cin >> n >> w; 

	vector<edge> edges; 

	for(int i = 0; i < w; i++){
		int u, v, W; 
		cin >> u >> v >> W;
		--u, --v;
		edges.push_back({u, v, W}); 

		cout << mst(edges, n) << '\n';
	}

	return 0; 
}
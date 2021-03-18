#include <bits/stdc++.h>

using namespace std;

struct UFDS{
	vector<int> e; 
	void init(int n){
		e = vector<int>(n, -1); 
	}

	int get(int x){
		return (e[x] < 0 ? x : e[x] = get(e[x])); 
	}

	bool same(int x, int y){
		return get(x) == get(y); 
	}
	bool unite(int x, int y){
		x = get(x), y = get(y); 
		if(x == y) return false; 

		if(e[x] > e[y])
			swap(x, y); 

		e[x] += e[y]; 
		e[y] = x; 
		return true; 
	}
}; 

struct edge{
	int u, v, w, idx;
};
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
		
	int n, m, k;
	cin >> n >> m >> k; 

	vector<edge> edges(m); 

	for(int i = 0; i < m; i++){
		cin >> edges[i].u >> edges[i].v >> edges[i].w;
		--edges[i].u; 
		--edges[i].v;
		edges[i].idx = i;
	}

	sort(edges.begin(), edges.end(), [](edge& a, edge& b){
		if(a.w > b.w) 
			return true; 
		return false; 
	}); 

	vector<UFDS> inherit(k); 

	for(int i = 0; i < k; i++)
		inherit[i].init(n); 

	vector<int> owner(m, -1); 
	for(auto& [u, v, w, idx] : edges){
		int lo = 0, hi = k - 1; 
		while(lo < hi){
			int mid = (lo + hi) >> 1; 
			if(inherit[mid].same(u, v)){
				lo = mid + 1; 
			}
			else{
				hi = mid;
			}
		}
		if(inherit[hi].same(u, v))
			continue;
		inherit[hi].unite(u, v); 
		owner[idx] = hi; 
	}

	for(int i = 0; i < m; i++)
		cout << owner[i] + 1 << '\n';
	return 0; 
}
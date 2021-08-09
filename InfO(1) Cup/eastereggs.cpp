#include <bits/stdc++.h>
#include "grader.h"
 
using namespace std;
	
const int MXN = 512;
vector<int> adj[MXN], ord;
 
void dfs(int node = 0, int par = -1){
	ord.push_back(node+1);
	for(int v : adj[node]){
		if(v == par)
			continue;
		dfs(v, node);
	}
}
 
int findEgg(int N, vector<pair<int, int>> edges){
	for(auto& i : adj) i.clear();
	ord.clear();
	for(auto& [u, v] : edges){
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
 
	dfs();
 
	int lo = 0, hi = N-1;
	while(lo < hi){
		int mid = (lo + hi + 1) >> 1;
		if(query(vector<int>(ord.begin(), ord.begin() + mid)))
			hi = mid - 1;
		else lo = mid;
	}
 
	return ord[lo];
}

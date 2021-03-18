#include "traffic.h"
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<int64_t> cur, child, mx; 
int64_t fans = 0; 

void dfs(int node, int par){
	for(int v : adj[node]){
		if(v == par)
			continue;
		dfs(v, node);
		mx[node] = max(mx[node], child[v]);
		child[node] += child[v];
	}
	mx[node] = max(mx[node], fans - child[node] - cur[node]);
	child[node] += cur[node]; 
}
int LocateCentre(int n, int p[], int s[], int d[]){
	adj.resize(n); 
	cur.resize(n); 
	child.resize(n); 
	mx.resize(n);
	for(int i = 0; i < n - 1; i++){
		adj[s[i]].push_back(d[i]);
		adj[d[i]].push_back(s[i]);
	}

	for(int i = 0; i < n; i++){
		cur[i] = p[i];
		fans += p[i];
	}

	dfs(0, 0);

	return min_element(mx.begin(), mx.end()) - mx.begin();
}	
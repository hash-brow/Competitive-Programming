#include "stations.h"
#include <bits/stdc++.h>

using namespace std;

void dfs(vector<vector<int>>& g, vector<int>& tin, int u, int p, int d, int& timer){
	if(!d) tin[u] = timer++;
	for(int v : g[u]) if(v != p){
		dfs(g, tin, v, u, d ^ 1, timer);
	}
	if(d) tin[u] = timer++;
}

vector<int> label(int n, int k, vector<int> u, vector<int> v){
	vector<vector<int>> g(n);
	for(int i = 0; i < n - 1; i++){
		g[u[i]].push_back(v[i]);
		g[v[i]].push_back(u[i]);
	}

	vector<int> tin(n);
	int timer = 0;

	dfs(g, tin, 0, 0, 0, timer);

	return tin;
}

int find_next_station(int s, int t, vector<int> c){
	int m = c.size(), i;
	if(s < c[0]){
		for(i = 0; i < m - 1; i++)
			if((i == 0 ? s : c[i-1]) < t && c[i] >= t)
				break;
	}
	else{
		for(i = m - 1; i > 0; --i)
			if((i + 1 == m ? s : c[i+1]) > t && c[i] <= t)
				break;
	}

	return c[i];
}
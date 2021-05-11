#include <bits/stdc++.h>

using namespace std;

int query (vector<int> V);

vector<vector<int>> g, d;
vector<int> tin;
int timer = 0;

void dfs(int node, int p, int idx){
	if(idx == 1) tin[node] = timer++;

	d[idx][node] = d[idx][p] + 1;

	for(int v : g[node]){
		if(v != p)
			dfs(v, node, idx);
	}
}

int findHiddenVertex(int n, vector<int> parents){
	g = vector<vector<int>> (n+1);
	d = vector<vector<int>>(n+1, vector<int>(n+1, -1));
	tin.resize(n+1);

	for(int i = 0; i < n-1; i++){
		g[parents[i]].push_back(i+2);
		g[i+2].push_back(parents[i]);
	}

	for(int i = 1; i <= n; i++)
		dfs(i, 0, i);

	vector<int> V;

	for(int i = 1; i <= n; i++)
		V.push_back(i);

	sort(V.begin(), V.end(), [&](int i, int j){
		return tin[i] < tin[j];
	});

	while(V.size() > 1){
		vector<int> Q;
		for(int i = 0; i < V.size() / 2; i++)
			Q.push_back(V[i]);

		sort(Q.begin(), Q.end(), [&](int i, int j){
			return tin[i] < tin[j]; 
		});

		int x = query(Q);

		if(x <= d[Q[0]][Q.back()]){
			V = Q;
		}
		else{
			Q.clear();
			for(int i = V.size() / 2; i < V.size(); i++)
				Q.push_back(V[i]);
			V = Q;
		}
	}

	return V[0];
}
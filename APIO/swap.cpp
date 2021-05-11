#include <bits/stdc++.h>

#ifndef LOCAL
#include "swap.h"
#endif

using namespace std;

// ******************** Constants ********************

const int MXN = 100000;
const int MXM = 200000;
const int MXS = 300000;
const int lg = 20;

// ******************** global variables ********************

vector<int> g[MXS];
int nxtnode = 0;

// ******************** LCA ********************

int up[lg][MXS], tin[MXS], tout[MXS], timer = 0;

void dfs(int node, int par){
	tin[node] = timer++;

	up[0][node] = par;
	for(int i = 1; i < lg; i++)
		up[i][node] = up[i-1][up[i-1][node]];

	for(int v : g[node]){
		if(v == par)
			continue;
		dfs(v, node);
	}

	tout[node] = timer;
}

inline bool isAncestor(int u, int v){
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v){
	if(isAncestor(u, v))
		return u;
	if(isAncestor(v, u))
		return v;

	for(int i = lg-1; i >= 0; --i)
		if(!isAncestor(up[i][u], v))
			u = up[i][u];

	return up[0][u];
}

// ******************** KRT ********************

vector<bool> has(MXS);
int par[MXS], val[MXS], degree[MXN];

void init(){
	for(int i = 0; i < MXS; i++)
		par[i] = i;
}

int get(int x){
	return (par[x] == x ? x : par[x] = get(par[x]));
}

void unite(int u, int v, int w){
	degree[u]++;
	degree[v]++;

	has[nxtnode] = (degree[u] >= 3 || degree[v] >= 3);

	u = get(u), v = get(v);

	if(u == v){
		g[nxtnode].push_back(u);
		par[u] = nxtnode;
		has[nxtnode] = 1;
		val[nxtnode] = w;

		nxtnode++;
		return;
	}

	g[nxtnode].push_back(u);
	g[nxtnode].push_back(v);
	val[nxtnode] = w;
	has[nxtnode] = has[nxtnode] | has[u] | has[v];
	par[u] = par[v] = nxtnode;

	nxtnode++;
	return;
}

int minup(int node){
	if(has[node] == 1)
		return node;

	for(int i = lg-1; i >= 0; --i)
		if(has[up[i][node]] == 0)
			node = up[i][node];

	if(has[up[0][node]] == 0) return -1;
	return up[0][node];
}
// ******************** ********************

void init(int N, int M, vector<int> U, vector<int> V, vector<int> W){
	vector<array<int, 3>> edges(M);
	for(int i = 0; i < M; i++)
		edges[i] = {W[i], U[i], V[i]};

	nxtnode = N;

	init();

	sort(edges.begin(), edges.end());

	for(auto& [w, u, v] : edges){
		unite(u, v, w);
	}

	dfs(nxtnode-1, nxtnode-1);
}

int getMinimumFuelCapacity(int X, int Y){
	int Z = lca(X, Y);
	Z = minup(Z);
	if(Z == -1) return -1;
	return val[Z];
}

#ifdef LOCAL
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int N, M;
	cin >> N >> M;

	vector<int> U(M), V(M), W(M);
	for(int i = 0; i < M; i++)
		cin >> U[i] >> V[i] >> W[i];

	init(N, M, U, V, W);

	int Q;
	cin >> Q;
	while(Q--){
		int X, Y;
		cin >> X >> Y;
		cout << getMinimumFuelCapacity(X, Y) << '\n';
	}

	return 0; 
}
#endif
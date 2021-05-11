#include <bits/stdc++.h>
#ifndef LOCAL
#include "factories.h"
#endif

using namespace std;

const int MXN = 500000;
const int lg = 20;
const int64_t INF = 1e18;

vector<int64_t> dist[MXN];

int par[MXN], sz[MXN], r[MXN];
int64_t best[MXN];

vector<array<int, 2>> g[MXN];

int hit[10*MXN], ptr = 0;

int dfs(int node, int p){
	sz[node] = 1;
 
	for(auto& [v, d] : g[node]){
		if(v == p)
			continue;
		sz[node] += dfs(v, node);
	}

 	return sz[node];
}

void comp(int node, int p){
	int64_t d = dist[node].back();
	for(auto& [v, di] : g[node]){
		if(!r[v] && v != p){
			dist[v].push_back(d+int64_t(di));
			comp(v, node);
		}
	}
}

void decompose(int node, int p){
	int inv = -1, ms = sz[node] >> 1;

	for(auto& [v, d] : g[node])
		if(!r[v] && sz[v] > ms){
			inv = v;
			break;
		}

	if(inv != -1){
		sz[node] -= sz[inv];
		sz[inv] += sz[node];
		return decompose(inv, p); 
	}

	r[node] = 1;
	par[node] = p;

	dist[node].push_back(0);
	comp(node, node);

	for(auto& [v, d] : g[node])
		if(!r[v])
			decompose(v, node); 
}

inline void update(int node){
	int v = node, pt = dist[node].size() - 1;
	while(v != -1){
		best[v] = min(best[v], dist[node][pt--]);
		hit[ptr++] = v;
		v = par[v];
	}
}

inline int64_t query(int node){
	int64_t ans = INF;
	int v = node, pt = dist[node].size() - 1;
	while(v != -1){
		ans = min(ans, best[v] + dist[node][pt--]);
		v = par[v];
	}
	return ans;
}

void Init(int n, int A[], int B[], int D[]){
	for(int i = 0; i < n-1; i++){
		g[A[i]].push_back({B[i], D[i]});
		g[B[i]].push_back({A[i], D[i]});
	}

	memset(par, -1, sizeof par);

	for(int i = 0; i < n; i++)
		best[i] = INF;

	dfs(0, 0);
	decompose(0, -1);
}

long long Query(int S, int X[], int T, int Y[]){
	ptr = 0;

	for(int i = 0; i < S; i++)
		update(X[i]);

	int64_t ans = INF;

	for(int i = 0; i < T; i++)
		ans = min(ans, query(Y[i]));

	for(int i = 0; i < ptr; i++)
		best[hit[i]] = INF;

	return ans;
}

#ifdef LOCAL
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 

	int N, Q;
	cin >> N >> Q;
	int A[N-1], B[N-1], D[N-1];

	for(int i = 0; i < N-1; i++){
		cin >> A[i] >> B[i] >> D[i];
	}

	Init(N, A, B, D);

	for(int i = 0; i < Q; i++){
		int S, T;
		cin >> S >> T;
		int X[S], Y[T];
		for(int j = 0; j < S; j++)
			cin >> X[j];
		for(int j = 0; j < T; j++)
			cin >> Y[j];

		cout << Query(S, X, T, Y) << '\n';
	}

	return 0; 
}
#endif
#include "Annalib.h"
#include <bits/stdc++.h>

using namespace std;

void dfs(vector<vector<int>>& g, int u, int p, vector<int>& t){
	for(int v : g[u]) if(v != p){
		if(v > u) // v -> u --> t[v] ^ t[u] = 1
			t[v] = 1 ^ t[u];
		else t[v] = t[u];

		dfs(g, v, u, t);
	}
}

void Anna(int K, int N, int T, int A[], int B[]){
	vector<vector<int>> g(N + 1);
	for(int i = 0; i < N - 1; i++){
		g[A[i]].push_back(B[i]);
		g[B[i]].push_back(A[i]);
	}

	vector<int> t(N + 1);
	t[T] = 0;

	dfs(g, T, T, t);

	// xor of flags is 1 if the edge needs to point towards min
	// xor of flags is 0 if the edge needs to point towards max

	for(int i = 1; i <= N; i++)
		Flag(i, t[i]);
}
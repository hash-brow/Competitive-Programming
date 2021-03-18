#include "dreaming.h"
#include <bits/stdc++.h>
 
using namespace std; 

const int MAXN = 1e5 + 5, INF = INT_MAX;  	
pair<int, int> root, leaf[2]; 
vector<pair<int, int>> adj[MAXN];
int ddist[MAXN][2]; 
bool vis[MAXN]; 
int comps[MAXN]; 
void dfs(int node, int p, int dist, int idx){
	vis[node] = 1; 
	leaf[idx] = max(leaf[idx], {dist, node}); 
	ddist[node][idx] = dist; 

	root = min(root, {max(ddist[node][0], ddist[node][1]), node}); 

	for(auto& [v, wt] : adj[node]){
		if(v == p) 
			continue; 

		dfs(v, node, dist + wt, idx); 
	}
}
int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
	for(int i = 0; i < M; i++){
		adj[A[i]].emplace_back(make_pair(B[i], T[i])); 
		adj[B[i]].emplace_back(make_pair(A[i], T[i])); 
	}
	int c = 0; 
	int max_d = INT_MIN; 
	for(int i = 0; i < N; i++){
		if(vis[i] == 1) 
			continue; 

		leaf[0] = leaf[1] = {INT_MIN, INT_MIN}; 

		dfs(i, i, 0, 0); 
		dfs(leaf[0].second, -1, 0, 1); 
		root = {INF, i}; 
		dfs(leaf[1].second, -1, 0, 0);
		max_d = max(max_d, leaf[0].first);
		comps[c++] = root.first; 
	}
	sort(comps, comps + c);
	if(c == 1)
		return max_d; 
	if(c == 2)
		return max(max_d, comps[0] + comps[1] + L); 
	return max({max_d, comps[c-1] + comps[c-2] + L, comps[c-2] + comps[c-3] + 2*L}); 
}
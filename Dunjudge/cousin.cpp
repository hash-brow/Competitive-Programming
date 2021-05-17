#include "cousin.h"
#include <bits/stdc++.h>

using namespace std; 

#define f first
#define s second

int n; 
vector<vector<int>> adj; 
vector<int> euler_tour;  
int timer, l; 
vector<vector<int>> up; 
vector<int> idx; 
vector<int> depth; 
vector<pair<int, int>> depth_range; 
void dfs(int node, int par){
	up[0][node] = par;
	depth[node] = depth[par] + 1; 
	for(int i = 1; i <= l; i++)
		up[i][node] = up[i-1][up[i-1][node]]; 

	for(int v : adj[node]){
		if(v == par) 
			continue; 
		dfs(v, node); 
	}
} 
int kthpar(int node, int k){
	for(int i = 0; i <= l; i++)
		if(k & (1 << i))
			node = up[i][node]; 
	return node; 
}
void preprocess(int root){
	l = log2(n); 
	up.assign(l+1, vector<int>(n));	
	depth.resize(n); 
	timer = 0; 
	depth[0] = -1; 
	dfs(root, root); 
}
void init(int N, int P[]) {
	n = N; 
	adj.resize(n); 
	for(int i = 1; i < n; i++){
		adj[P[i]].push_back(i); 
	}

	preprocess(0); 

	queue<int> q; 
	q.push(0); 
	timer = 0; 
	euler_tour.resize(n); 
	idx.resize(n); 
	depth_range.assign(n, {-1, -1}); 
	while(!q.empty()){
		int node = q.front(); 
		q.pop(); 
		if(depth_range[depth[node]].f == -1) depth_range[depth[node]].f = timer;
		depth_range[depth[node]].s = timer;
		euler_tour[timer++] = node; 
		idx[node] = timer - 1; 
		for(int v : adj[node])
			q.push(v); 
	}
}

int count_cousins(int X, int K) {
	int req = kthpar(X, K); 
	int k = K; 
	int cur = idx[X]; 
	for(int jump = depth_range[depth[X]].s - idx[X]; jump >= 1; jump >>= 1){
		while(true){
			if(cur + jump > depth_range[depth[X]].s) 
				break; 
			if(kthpar(euler_tour[cur + jump], k) == req)
				cur += jump; 
			else break; 
		}
	}
	int end = cur; 

	cur = idx[X]; 

	for(int jump = idx[X] - depth_range[depth[X]].f; jump >= 1; jump >>= 1){
		while(true){
			if(cur - jump < depth_range[depth[X]].f || depth[euler_tour[cur - jump]] < k) 
				break; 
			if(kthpar(euler_tour[cur - jump], k) == req)
				cur -= jump; 
			else break;
		}
	}
	return end - cur;
}

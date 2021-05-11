#include <bits/stdc++.h>
#ifndef LOCAL
#include "crocodile.h"
#endif

using namespace std;

const int64_t INF = 1e18;

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]){
	vector<array<int, 2>> g[N];
	for(int i = 0; i < M; i++){
		int u = R[i][0], v = R[i][1];
		g[u].push_back({v, L[i]});
		g[v].push_back({u, L[i]});
	}

	int64_t D[N][2]; 
	int vis[N];

	priority_queue< array<int64_t, 2>, vector<array<int64_t, 2>>, greater<array<int64_t, 2>> > pq;

	for(int i = 0; i < N; i++){
		D[i][0] = D[i][1] = INF;
		vis[i] = 0;
	}

	for(int i = 0; i < K; i++){
		int64_t v = P[i];
		D[v][0] = D[v][1] = 0;
		pq.push({0, v});
	}

	while(!pq.empty()){
		auto [d, node] = pq.top();
		pq.pop();
		if(vis[node] == 1)
			continue;
		++vis[node];
		for(auto& [v, dx] : g[node]){
			int64_t nx = d + int64_t(dx);
			if(nx <= D[v][0]){
				D[v][1] = D[v][0];
				D[v][0] = nx;
				if(D[v][1] != INF)
					pq.push({D[v][1], v});
			}
			else if(nx <= D[v][1]){
				D[v][1] = nx;
				pq.push({D[v][1], v});
			}
		}
	}

	return D[0][1];
}

#ifdef LOCAL
int32_t main(){
	int N, M, K;
	cin >> N >> M >> K;

	int R[M][2], L[M], P[K];
	for(int i = 0; i < M; i++){
		cin >> R[i][0] >> R[i][1] >> L[i];
	}
	for(int i = 0; i < K; i++){
		cin >> P[i];
	}

	cout << travel_plan(N, M, R, L, K, P) << '\n';
	return 0;
}
#endif
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, m;
	cin >> n >> m;

	vector<vector<array<int, 2>>> adj(n);
	vector<set<int>> jump(n);
	vector<array<int, 2>> info(m);
	int src, dest;
	for(int i = 0; i < m; i++){
		int b, p;
		cin >> b >> p;
		info[i] = {b, p};
		jump[b].insert(p);
		if(i == 0) src = b;
		if(i == 1) dest = b;
	}
 	
 	for(int b = 0; b < n; b++){
 		for(int p : jump[b]){
 			for(int j = b+p; j < n; j += p){
				adj[b].push_back({j, (j-b)/p});
				if(jump[j].count(p)) break;
			}
			for(int j = b-p; j >= 0; j -= p){
				adj[b].push_back({j, (b-j)/p});
				if(jump[j].count(p)) break;
			}
 		}
 	}

	vector<int> dist(n, INF);
	dist[src] = 0;
	priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> pq;
	pq.push({0, src});
 
	while(!pq.empty()){
		auto [d, node] = pq.top();
		pq.pop();
		for(auto& [v, nd] : adj[node]){
			if(dist[v] <= dist[node] + nd)
				continue;
			dist[v] = dist[node] + nd;
			pq.push({dist[v], v});
		}
	}
	
	cout << (dist[dest] == INF ? -1 : dist[dest]) << '\n';

	return 0; 
}

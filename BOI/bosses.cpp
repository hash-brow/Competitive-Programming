#include <bits/stdc++.h>

using namespace std;

const int MXN = 5000;
vector<int> g[MXN];
vector<bool> vis;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n;

	for(int i = 0; i < n; i++){
		int k;
		cin >> k;
		for(int j = 0; j < k; j++){
			int x;
			cin >> x;
			g[x-1].push_back(i);
		}
	}

	int64_t ans = 1e16;
	for(int i = 0; i < n; i++){
		int64_t cost = 0; 
		queue<array<int, 2>> q;
		q.push({i, 1});
		vis.assign(n, 0);
		vis[i] = 1;
		while(!q.empty()){
			int u = q.front()[0], d = q.front()[1];
			q.pop();
			cost += int64_t(d);
			for(int v : g[u]){
				if(!vis[v]){
					vis[v] = 1;
					q.push({v, d+1});
				}
			}
		}
		for(int v = 0; v < n; v++) if(!vis[v]) cost = 1e16;
		ans = min(ans, cost);
	}

	cout << ans << '\n';
	return 0;
}
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<int> cost, lead, sum;
vector<multiset<int>> q; 
int64_t ans = 0;
int m;

void add(int u, int v){
	if(q[u].size() < q[v].size()){
		swap(q[u], q[v]);
		swap(sum[u], sum[v]);
	}

	for(int x : q[v]){
		if(sum[u] + x <= m){
			q[u].insert(x);
			sum[u] += x;
			continue;
		}
		auto it = q[u].end();
		--it;
		if(*it > x){
			sum[u] -= (*it);
			sum[u] += x;
			q[u].erase(it);
			q[u].insert(x);
		}
	}
}

void dfs(int node){
	if(sum[node] + cost[node] <= m){
		q[node].insert(cost[node]);
		sum[node] += cost[node];
	}
	for(int v : adj[node]){
		dfs(v);
		add(node, v);
	}
	ans = max(ans, int64_t(lead[node])*int64_t(q[node].size()));
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n >> m;

	adj.resize(n), cost.resize(n), lead.resize(n), q.resize(n), sum.resize(n);

	for(int i = 0; i < n; i++){
		int x;
		cin >> x >> cost[i] >> lead[i];
		--x;
		if(x == -1) continue;
		adj[x].push_back(i);
	}

	dfs(0);

	cout << ans << '\n';
	return 0; 
}

#include <bits/stdc++.h>

using namespace std;

const int INF = 2000000000;

vector<vector<array<int, 2>>> g, ng, ngt;
vector<int> tin, low, onstk, st;
int timer = 0, cur = 0;
vector<int> comp;

void tarjan(int node){
	tin[node] = low[node] = timer++;
	st.push_back(node);
	onstk[node] = 1;

	for(auto& [v, w] : g[node]){
		if(tin[v] == -1){
			tarjan(v);
			low[node] = min(low[node], low[v]);
		}
		else if(onstk[v])
			low[node] = min(low[node], tin[v]);
	}

	if(low[node] == tin[node]){
		while(1){
			int v = st.back();
			comp[v] = cur;
			st.pop_back();
			onstk[v] = 0;
			if(v == node)
				break;
		}
		cur++;
	}
}

vector<int> timein, timeout, depth;
vector<int> dist;
vector<int> cycle, ans;

void dfs(int node, int par, int weight){
	depth[node] = depth[par] + weight;
	timein[node] = timer++;

	for(auto& [v, w] : ng[node]){
		if(timein[v] >= 0 && timeout[v] == -1){
			cycle.push_back(depth[node] - depth[v] + w);
		}
		else if(timein[v] >= 0 && timeout[v] >= 0){
			cycle.push_back({dist[v] + depth[node] + w});
		}
		else if(timein[v] == -1)
			dfs(v, node, w);
	}

	timeout[node] = timer;
}

void dijkstra(int node){
	dist[node] = 0;
	priority_queue<array<int, 2>> pq;
	pq.push({0, node});

	while(!pq.empty()){
		auto [d, u] = pq.top();
		pq.pop();

		d *= -1;

		if(dist[u] < d)
			continue;

		for(auto& [v, di] : ngt[u]){
			if(dist[v] > dist[u] + di){
				dist[v] = dist[u] + di;
				pq.push({-dist[v], v}); 
			}
		}
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	cin >> n >> m;
	g.resize(n);
	tin.resize(n, -1), low.resize(n, -1);
	onstk.resize(n, 0);
	comp.resize(n, -1);

	vector<array<int, 3>> edge;

	for(int i = 0; i < m; i++){
		int x, y, l;
		cin >> x >> y >> l;
		--x, --y;
		g[x].push_back({y, l});
		edge.push_back({x, y, l});
	}

	for(int i = 0; i < n; i++)
		if(tin[i] == -1)
			tarjan(i);

	ng.resize(n), ngt.resize(n);

	for(auto [x, y, l] : edge){
		if(comp[x] == comp[y]){
			ng[x].push_back({y, l});
			ngt[y].push_back({x, l});
		}
	}

	timein.resize(n, -1);
	timeout.resize(n, -1);
	depth.resize(n, 0);
	timer = 0;
	dist.resize(n, INF);
	ans.resize(cur);

	for(int i = 0; i < n; i++)
		if(timein[i] == -1){
			dijkstra(i);
			dfs(i, i, 0);

			ans[comp[i]] = 0;
			for(int v : cycle)
				ans[comp[i]] = gcd(ans[comp[i]], v);

			cycle.clear();

		}

	for(int i = 0; i < n; i++)
		cout << (ans[comp[i]] ? ans[comp[i]] : -1) << '\n';

	return 0;
}
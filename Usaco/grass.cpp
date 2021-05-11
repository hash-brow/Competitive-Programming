#include <bits/stdc++.h>

using namespace std;

const int MXN = 100000;
const int INF = 1000000000;

vector<int> g[MXN], scc[MXN], sccr[MXN];
array<int, 2> edge[MXN];

int comp[MXN], tin[MXN], low[MXN], sz[MXN], idx[MXN];

vector<bool> onstk(MXN, 0);
int cur = 0, timer = 0;

vector<int> st;

void tarjan(int node){
tin[node] = low[node] = timer++;
	st.push_back(node);
	onstk[node] = 1;

	for(int v : g[node]){
		if(tin[v] == -1){
			tarjan(v);
			low[node] = min(low[node], low[v]);
		}
		else if(onstk[v])
			low[node] = min(low[v], low[node]);
	}

	if(tin[node] == low[node]){
		while(1){
			int v = st.back();
			st.pop_back();
			onstk[v] = 0;
			comp[v] = cur;
			sz[cur]++;
			if(node == v)
				break;
		}
		cur++;
	}
}

vector<int> ord;
vector<bool> vis(MXN, 0);

void dfs(int node){
	vis[node] = 1;
	for(int v : scc[node]){
		if(vis[v])
			continue;
		dfs(v);
	}
	ord.push_back(node);
}

int dp[MXN];

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	freopen("grass.in", "r", stdin);
	freopen("grass.out", "w", stdout);

	int n, m;
	cin >> n >> m;

	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		edge[i] = {u, v};
	}

	memset(tin, -1, sizeof tin);
	memset(low, -1, sizeof low);

	for(int i = 0; i < n; i++)
		if(tin[i] == -1)
			tarjan(i);

	for(int i = 0; i < m; i++){
		int u = edge[i][0], v = edge[i][1];
		u = comp[u], v = comp[v];
		if(u == v)
			continue;
		scc[u].push_back(v);
		sccr[v].push_back(u);
 	}

	for(int i = 0; i < cur; i++)
		if(!vis[i])
			dfs(i);

	reverse(ord.begin(), ord.end());

	int N = ord.size();
	for(int i = 0; i < N; i++)
		idx[ord[i]] = i;

	vector<int> dp(N, -INF);

	int pos = idx[comp[0]];
	dp[pos] = 0;

	for(int i = pos-1; i >= 0; --i){
		int node = ord[i];
		for(int v : scc[node]){
			dp[i] = max(dp[i], dp[idx[v]] + sz[node]);
		}
	}

	int ans = 0;

	for(int i = pos; i < N; i++){
		int node = ord[i];
 		for(int v : sccr[node])
			if(idx[v] >= pos){
				dp[i] = max(dp[i], dp[idx[v]] + sz[node]);
			}

		for(int v : sccr[node]){
			if(idx[v] <= pos){
				ans = max(ans, dp[i] + dp[idx[v]] + sz[ord[pos]]);
			}
		}
	}

	cout << max(ans, sz[comp[0]]) << '\n';
	return 0; 
}
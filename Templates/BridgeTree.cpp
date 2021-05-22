const int MXN = 1000000;

vector<vector<int>> bridgeTree;
int C;

vector<array<int, 2>> g[MXN];
array<int, 2> edges[MXN];

vector<bool> vis(MXN), is(MXN);

int tin[MXN], low[MXN];
int timer = 0;

void dfs(int u, int p, int id){
	tin[u] = low[u] = timer++;
	vis[u] = 1;

	for(auto& [v, idx] : g[u]){
		if(v == p)
			continue;
		if(vis[v]){
			low[u] = min(low[u], tin[v]);
		}
		else{
			dfs(v, u, idx);
			low[u] = min(low[v], low[u]);
			if(low[v] > tin[u])
				is[idx] = 1;
		}
	}
}

void findBridges(int N){
	for(int i = 0; i < N; i++){
		vis[i] = 0;
		tin[i] = low[i] = -1;
	}
	timer = 0;

	for(int i = 0; i < N; i++){
		if(!vis[i])
			dfs(i, i, -1);
	}
}

vector<int> ng[MXN];
int comp[MXN];

void dfs2(int node, int c){
	comp[node] = c;
	for(int v : ng[node]){
		if(comp[v] == 0)
			dfs2(v, c);
	}
}

void Compress(int N, int M){
	for(int i = 0; i < M; i++)
		if(!is[i]){
			ng[edges[i][0]].push_back(edges[i][1]);
			ng[edges[i][1]].push_back(edges[i][0]);
		}

	int c = 1;

	for(int i = 0; i < N; i++)
		if(comp[i] == 0)
			dfs2(i, c++);

	for(int i = 0; i < N; i++)
		comp[i]--;

	C = c-1;
	
	bridgeTree.resize(C);
	for(int i = 0; i < M; i++){
		auto [u, v] = edges[i];
		if(comp[u] != comp[v]){
			bridgeTree[comp[u]].push_back(comp[v]);
			bridgeTree[comp[v]].push_back(comp[u]);
		}
	}
}
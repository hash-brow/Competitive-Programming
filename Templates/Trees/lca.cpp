const int MXN = 50000;
const int lg = 15;

vector<int> adj[MXN];

struct LCA{
	int up[lg][MXN];
	int tin[MXN], tout[MXN];
	int timer = 0;

	LCA(){
		dfs()
	}

	void dfs(int node = 0, par = 0){
		tin[node] = timer++;

		up[0][node] = par;
		for(int i = 1; i < lg; i++)
			up[i][node] = up[i-1][up[i-1][node]];

		for(int v : adj[node]){
			if(v == par)
				continue;
			dfs(v, node);
		}

		tout[node] = timer++;
	}

	bool isAncestor(int u, int v){
		return tin[u] <= tin[v] && tout[u] >= tout[v];
	}

	int lca(int u, int v){
		if(isAncestor(u, v))
			return u;
		if(isAncestor(v, u))
			return v;

		for(int i = lg-1; i >= 0; --i){
			if(!isAncestor(up[i][u], v))
				u = up[i][u];
		}

		return up[0][u]
	}
};

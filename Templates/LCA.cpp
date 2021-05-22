const int MXN = 100000;
const int MXK = 20;

vector<int> g[MXN];

struct LCA{
	int up[MXK][MXN];
	int tin[MXN], tout[MXN];
	int timer = 0;

	LCA(int root){
		dfs(root, root);
	}

	void dfs(int node, int par){
		tin[node] = timer++;

		up[0][node] = par;
		for(int i = 1; i < MXK; i++)
			up[i][node] = up[i-1][up[i-1][node]];

		for(int v : g[node]){
			if(v != par)
				dfs(v, node);
		}

		tout[node] = timer;
	}

	bool isAncestor(int u, int v){
		return tin[u] <= tin[v] && tout[u] >= tout[v];
	}

	int lca(int u, int v){
		if(isAncestor(u, v))
			return u;
		if(isAncestor(v, u))
			return v;

		for(int i = MXK-1; i >= 0; --i)
			if(!isAncestor(up[i][u], v))
				u = up[i][u];

		return up[0][u];
	}
};
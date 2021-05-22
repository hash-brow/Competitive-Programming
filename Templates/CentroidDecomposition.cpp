vector<int64_t> dist[MXN];

int par[MXN], sz[MXN], r[MXN];

int dfs(int node, int p){
	sz[node] = 1;
 
	for(auto& [v, d] : g[node]){
		if(v == p)
			continue;
		sz[node] += dfs(v, node);
	}

 	return sz[node];
}

void comp(int node, int p){
	int64_t d = dist[node].back();
	for(auto& [v, di] : g[node]){
		if(!r[v] && v != p){
			dist[v].push_back(d+int64_t(di));
			comp(v, node);
		}
	}
}

void decompose(int node, int p){
	int inv = -1, ms = sz[node] >> 1;

	for(auto& [v, d] : g[node])
		if(!r[v] && sz[v] > ms){
			inv = v;
			break;
		}

	if(inv != -1){
		sz[node] -= sz[inv];
		sz[inv] += sz[node];
		return decompose(inv, p); 
	}

	r[node] = 1;
	par[node] = p;

	dist[node].push_back(0);
	comp(node, node);

	for(auto& [v, d] : g[node])
		if(!r[v])
			decompose(v, node); 
}
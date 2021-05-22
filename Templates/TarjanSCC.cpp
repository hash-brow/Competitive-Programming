int comp[MXN], tin[MXN], low[MXN], sz[MXN];

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
vector<int> order, component;
vector<bool> used;

void dfs(int node){
	used[node] = true;
	for(int v : adj[node]){
		if(used[v]) continue;
		dfs(v);
	}
	order.push_back(node);
}

void comp(int node){
	used[node] = true;
	for(int v : adjr[node]){
		if(used[v]) continue;
		comp(v);
	}
	component.push_back(v);
}

void scc(int n){
	used.assign(n, 0);
	for(int i = 0; i < n; i++){
		if(used[i]) continue;
		dfs(i);
	}

	reverse(order.begin(), order.end());

	used.assign(n, 0);

	for(int i = 0; i < n; i++){
		int v = order[i];
		if(used[v]) continue;
		comp(v);
		for(int x : component)
			cout << x << ' ';
		component.clear();
	}
}
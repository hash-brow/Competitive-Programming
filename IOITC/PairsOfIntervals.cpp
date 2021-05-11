#include <bits/stdc++.h>

using namespace std;

vector<int> c;
vector<bool> vis;
vector<vector<int>> g;
bool bad = false;
void dfs(int node, int col){
	c[node] = col;
	vis[node] = 1;

	for(int v : g[node]){
		if(vis[v] && c[v] == col){
			bad = true;
		}
		if(!vis[v])
			dfs(v, col^1);
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n;
	c.assign(2*n, -1), vis.resize(2*n, 0), g.resize(2*n);

	vector<int> Discrete;
	vector<array<int, 4>> a(2*n);
	for(int i = 0; i < 2*n; i += 2){
		for(int x = 0; x < 2; x++){
			for(int j = 0; j < 2; j++){
				cin >> a[i+x][j];
				Discrete.push_back(a[i+x][j]);
			}
			a[i+x][3] = x;
			a[i+x][2] = i >> 1;
		}
	}

	sort(Discrete.begin(), Discrete.end());
	Discrete.erase(unique(Discrete.begin(), Discrete.end()), Discrete.end());

	for(int i = 0; i < 2*n; i += 2){
		for(int x = 0; x < 2; x++){
			for(int j = 0; j < 2; j++)
				a[i+x][j] = lower_bound(Discrete.begin(), Discrete.end(), a[i+x][j]) - Discrete.begin();
		}
	}

	int mxs = Discrete.size();
	vector<vector<int>> position(mxs);
	for(int i = 0; i < n; i++){
		for(int x = 0; x < 2; x++)
			position[a[2*i+x][0]].push_back(2*i+x);
		g[2*i].push_back(2*i+1);
		g[2*i+1].push_back(2*i);
	}

	for(vector<int>& x : position){
		for(int i = 1; i < x.size(); i++){
			g[x[i]].push_back(x[i-1]);
			g[x[i-1]].push_back(x[i]);
		}
	}

	for(int i = 0; i < 2*n; i++){
		if(!vis[i])
			dfs(i, 0);
	}

	for(int i = 0; i < n; i++){
		if(c[2*i] == -1 && c[2*i+1] == -1){
			cout << "No\n";
			return 0;
		}
	}
	if(bad){
		cout << "No\n";
		return 0;
	}
	cout << "Yes\n";
	for(int i = 0; i < n; i++){
		if(c[2*i] == 1)
			cout << 1 << ' ';
		else cout << 2 << ' ';
	}

	return 0;
}
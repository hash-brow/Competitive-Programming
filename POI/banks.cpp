#include <bits/stdc++.h>

using namespace std;

vector<bool> found;
vector<int> l[1000000];
int col[1000000];

int cycle_start;

bool dfs(int node){
	col[node] = 1;

	for(int v : l[node]){
		if(col[v] == 1){
			cycle_start = v;
			return true;
		}
		if(dfs(v))
			return true;
	}
	col[node] = 2;

	return false;
}

void mark(int node){
	if(found[node])
		return;
	found[node] = 1;
	for(int v : l[node])
		mark(v);
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 

	int n;
	cin >> n;

	found.resize(n);

	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		--x;
		l[x].emplace_back(i);
	}

	int ans = 0;

	for(int i = 0; i < n; i++){
		cycle_start = -1;
		if(!found[i] && col[i] == 0 && dfs(i)){
			mark(cycle_start);
			ans++;
		}
	}

	cout << ans << '\n';
	return 0; 
}
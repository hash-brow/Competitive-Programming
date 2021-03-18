#include <bits/stdc++.h>

using namespace std;

struct dsu{
	vector<int> e;
	dsu(int n){
		e.resize(n, -1);
	}

	int get(int x){
		return (e[x] < 0 ? x : e[x] = get(e[x]));
	}

	int sz(int x){
		return -e[get(x)];
	}

	bool unite(int x, int y){
		x = get(x), y = get(y);
		if(x == y)
			return 0;

		if(e[x] > e[y])
			swap(x, y);
		e[x] += e[y];
		e[y] = x;

		return 1;
	}
};

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, m;
	cin >> n >> m;

	int mat[n][n];

	memset(mat, 0, sizeof mat);

	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		mat[u][v] = mat[v][u] = 1;
	}	

	int ans = 0;

	for(int i = 0; i < n; i++)
		for(int j = i+1; j < n; j++)
			for(int k = j+1; k < n; k++){
				if(mat[i][j] || mat[i][k] || mat[j][k])
					continue;
				ans++;
			}

	cout << ans << '\n';
	return 0; 
}
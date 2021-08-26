#include <bits/stdc++.h>

using namespace std;

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
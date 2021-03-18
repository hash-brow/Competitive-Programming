#include <bits/stdc++.h>

using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, m, k;
	cin >> n >> m >> k;

	int mat[n][m];
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> mat[i][j];	

	vector<int64_t> path[2][m];
	path[0][0].emplace_back(mat[0][0]);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(i == 0 && j == 0)
				continue;
			if(i == 0){
				path[i&1][j] = path[i&1][j-1];
				for(int64_t &x : path[i&1][j])
					x += 1LL*mat[i][j];
				continue;
			}

			if(j == 0){
				path[i&1][j] = path[(i-1)&1][j];
				for(int64_t &x : path[i&1][j])
					x += 1LL*mat[i][j];
				continue;
			}
			path[i&1][j].clear();
			int l = 0, r = 0, sz = 0; 
			int s1 = path[(i-1)&1][j].size(), s2 = path[i&1][j-1].size();
			while(l < s1 && r < s2 && sz < k){
				if(path[(i-1)&1][j][l] > path[i&1][j-1][r]){
					path[i&1][j].emplace_back(path[(i-1)&1][j][l] + 1LL*mat[i][j]);
					sz++;
					l++;
				}
				else{
					path[i&1][j].emplace_back(path[i&1][j-1][r] + 1LL*mat[i][j]);
					sz++;
					r++;
				}
			}
			while(l < s1 && sz < k){
				path[i&1][j].emplace_back(path[(i-1)&1][j][l] + 1LL*mat[i][j]);
				sz++;
				l++;
			}
			while(r < s2 && sz < k){
				path[i&1][j].emplace_back(path[i&1][j-1][r] + 1LL*mat[i][j]);
				sz++;
				r++;
			}
		}
	}
	cout << path[(n-1)&1][m-1].back() << '\n';
	return 0; 
}
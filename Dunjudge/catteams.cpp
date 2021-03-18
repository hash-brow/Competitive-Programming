#include <bits/stdc++.h>

using namespace std;

struct SparseTable{
	int L = 15; 
	int stmin[16][20001], stmax[16][20001];
	int log[20001];

	void init(int e[], int n){
		log[1] = 0; 
		for(int i = 2; i <= n; i++)
			log[i] = log[i>>1] + 1;

		for(int i = 1; i <= n; i++)
			stmin[0][i] = stmax[0][i] = e[i]; 

		for(int j = 1; j <= L; j++){
			for(int i = 1; i + (1 << j) <= n+1; i++){
				stmin[j][i] = min(stmin[j-1][i], stmin[j-1][i+(1<<(j-1))]);
				stmax[j][i] = max(stmax[j-1][i], stmax[j-1][i+(1<<(j-1))]);
			}
		}
	}

	int query(int l, int r){
		int j = log[r-l+1];
		int mx = max(stmax[j][l], stmax[j][r-(1<<j)+1]);
		int mn = min(stmin[j][l], stmin[j][r-(1<<j)+1]);

		return mx - mn;
	}
} S;

int dp[2][20001]; 
void f(int l, int r, int optl, int optr, int k){
	if(l > r) 
		return; 
	int mid = (l + r) >> 1; 
	pair<int, int> best = {-1e9, -1}; 
	for(int x = optl; x <= min(optr, mid); x++){
		int cur = dp[k^1][x-1] + S.query(x, mid);
		best = max(best, {cur, x});	
	}
	dp[k][mid] = best.first;
	f(l, mid - 1, optl, best.second, k); 
	f(mid + 1, r, best.second, optr, k);
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 

	int n, K;
	cin >> n >> K; 

	int e[n+1]; 
	for(int i = 1; i <= n; i++)
		cin >> e[i]; 
	S.init(e, n);

	memset(dp, 0, sizeof(dp));
	for(int i = 0; i <= n; i++)
		dp[0][i] = -1e9;
	
	dp[0][0] = 0;

	for(int i = 1; i <= K; i++){
		f(1, n+1, 1, n+1, i&1);

		dp[i&1][0] = -1e9;

		for(int j = 0; j <= n; j++)
			dp[(i-1)&1][j] = -1e9;
	}
	cout << dp[K&1][n] << '\n'; 
	return 0; 
}
#include <bits/stdc++.h>

using namespace std;

const int64_t mod = 1000000007;

int64_t dp[3001][3001];

int64_t f(int64_t row, int64_t col){
	if(row < 0 || col < 0)
		return 0;
	if(row == 0 || col == 0) return 1;
	if(dp[row][col] != -1)
		return dp[row][col];
	
	int64_t val = f(row, col-1);
	(val += row*4*f(row-1, col-1)) %= mod;
	(val += row*(col-1)*f(row-1, col-2)) %= mod;
	(val += row*(row-1)/2*f(row-2, col-1)) %= mod;

	return dp[row][col] = val;
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int h, w;
	cin >> h >> w;

	memset(dp, -1, sizeof dp);

	cout << (f(h, w) - 1 + mod) % mod << '\n';

	return 0; 
}
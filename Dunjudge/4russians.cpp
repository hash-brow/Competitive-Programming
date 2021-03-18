#include <bits/stdc++.h>

using namespace std;

const int64_t INF = 1e18;

#define dbg(x) cout << "[" << #x << ": " << x << "] ";

int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;

	int64_t s[n], c[n+2];
	c[0] = 0;
	c[n+1] = 0;
	for(int i = 1; i <= n; i++)
		cin >> c[i];
	for(int i = 0; i < n; i++)
		cin >> s[i];

	int64_t dp[n+1][k+1][2];

	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= k; j++)
			dp[i][j][0] = dp[i][j][1] = -INF;

	dp[0][0][0] = 0;
	for(int i = 0; i <= n; i++)
		dp[i][0][0] = 0;
	int64_t ans = 0; 
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= min(i, k); j++){
			dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1] - c[i]*c[i-1]);
			dp[i][j][1] = max(dp[i-1][j-1][1] + s[i-1], dp[i-1][j-1][0] + s[i-1] - c[i]*c[i-1]);
		}

	for(int i = 0; i <= k; i++)
		ans = max({ans, dp[n][i][0], dp[n][i][1]});
	cout << ans << '\n';

	return 0;
}

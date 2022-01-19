#include <bits/stdc++.h>
 
using namespace std;
 
const int64_t INF = 1e16;
 
template<typename T> 
void smin(T &a, T b){
	a = min(a, b);
}
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n; 
	int64_t l; 
	cin >> n >> l; 
 
	vector<int64_t> pos(n+2), t(n+2);
 
	for(int i = 1; i <= n; i++)
		cin >> pos[i];
 
	for(int i = 1; i <= n; i++)
		cin >> t[i];
 
	t[0] = 0;
	pos[0] = 0;
	pos[n+1] = l;
	t[n+1] = 0; 
	int64_t dp[n+2][n+2][2][n+2];
	for(int i = 0; i < n + 2; i++)
		for(int j = 0; j < n + 2; j++)
			for(int k = 0; k < n + 2; k++)
				dp[i][j][0][k] = dp[i][j][1][k] = INF; 
 
	dp[0][n+1][0][0] = dp[0][n+1][1][0] = 0;
	for(int i = 0; i <= n; i++){
		for(int j = n+1; j > i + 1; --j){
			for(int k = 0; k < n; k++){
				int64_t min_time = min(dp[i][j][0][k]+pos[i+1]-pos[i], dp[i][j][1][k]+l-pos[j]+pos[i+1]);
				smin(dp[i+1][j][0][k+(min_time<=t[i+1] ? 1 : 0)], min_time);
				min_time = min(dp[i][j][0][k]+l-pos[j-1]+pos[i], dp[i][j][1][k]+pos[j]-pos[j-1]);
				smin(dp[i][j-1][1][k+(min_time<=t[j-1] ? 1 : 0)], min_time);
			}
		}
	}
 
	int ans = 0; 
	for(int i = 0; i <= n+1; i++)
		for(int j = 0; j <= n+1; j++)
			for(int k = 0; k <= n+1; k++)
				for(int z = 0; z < 2; z++)
					if(dp[i][j][z][k] <= 1000000000){
						ans = max(ans, k);
					}
 
	cout << ans << '\n';
	return 0; 
}

#include <bits/stdc++.h>
 
using namespace std;
 
const int MXN = 301;
const int INF = 1e9;
 
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, m, k;
	cin >> n >> m >> k;
 
	vector<int> a(n), b(m);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	for(int i = 0; i < m; i++)
		cin >> b[i];
 
	if(*min_element(a.begin(), a.end()) < k){
		cout << "Impossible\n";
		return 0;
	}
 
	vector<int> dp(MXN*MXN, -INF);
	dp[0] = 0;
 
	for(int i = 0; i < m; i++){
		for(int W = MXN*MXN - 1; W >= b[i]; --W)
			dp[W] = max(dp[W], dp[W-b[i]] + min(b[i], n));
	}
 
	int sum = accumulate(a.begin(), a.end(), 0);
	int ans = INF;
	for(int W = sum; W < MXN*MXN; W++)
		if(dp[W] >= n*k)
			ans = min(ans, W - sum);
 
	cout << (ans != INF ? to_string(ans) : "Impossible") << '\n';
	return 0; 
}
#include <bits/stdc++.h>

using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n;

	vector<int> dp(n+1);
	dp[0] = 1;
	for(int i = 5; i <= n; i++)
		for(int j = i; j <= n; j++)
			dp[j] += dp[j-i];

	cout << dp[n] << '\n';	
	return 0; 
}
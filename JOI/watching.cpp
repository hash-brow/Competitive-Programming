#include <bits/stdc++.h>

using namespace std;
	
const int MXN = 2001;

int dp[MXN][MXN], a[MXN];

int n, p, q;

bool check(int w){
	memset(dp, 0, sizeof dp);

	for(int i = 1; i <= n; i++){
		int l = 1, r = 1;
		while(a[i] - a[l] >= w) l++;
		while(a[i] - a[r] >= 2*w) r++;

		for(int j = 0; j <= p; j++)
			if(j == 0) dp[i][j] = dp[r-1][j] + 1;
			else dp[i][j] = min(dp[l-1][j-1], dp[r-1][j] + 1);
	}

	return dp[n][p] <= q;
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	cin >> n >> p >> q;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	p = min(p, n);
	sort(a+1, a+n+1);

	int lo = 1, hi = 1000000001;
	while(lo < hi){
		int mid = (lo + hi) >> 1;
		if(check(mid))
			hi = mid;
		else lo = mid + 1;
	}

	cout << lo << '\n';
	return 0; 
}
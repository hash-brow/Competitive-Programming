#include <bits/stdc++.h>

using namespace std;

const int bits = 45;
const int MXN = 2001;
const int INF = 1e9;
int64_t pref[MXN];
int A, B, N;

bool check(int64_t mask){
	vector<int> dp(N+1, INF);
	dp[0] = 0;
	for(int i = 1; i <= N; i++){
		for(int j = 0; j < i; ++j){
			if((mask | (pref[i] - pref[j])) != mask) continue;
			dp[i] = min(dp[i], dp[j] + 1);
		}
	}

	return dp[N] <= B;
}

bool check(int64_t mask, bool f){
	vector<vector<bool>> dp(N+1, vector<bool>(N+1, 0));
	dp[0][0] = 1;

	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= i; j++)
			for(int k = 0; k < i; k++)
				if(dp[k][j-1] && (mask | (pref[i] - pref[k])) == mask)
					dp[i][j] = 1;
	}

	for(int i = A; i <= B; i++)
		if(dp[N][i]) return 1;
	return 0;
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 

	cin >> N >> A >> B;

	for(int i = 1; i <= N; i++){
		cin >> pref[i];
		pref[i] += pref[i-1];
	}

	int64_t ans = (1LL << bits) - 1;

	for(int bit = bits - 1; bit >= 0; --bit){
		int64_t red = (1LL << bit);
		if(A == 1){
			if(check(ans^red)) ans ^= red;
			continue;
		}
		if(check(ans^red, 0)) ans ^= red;
	}	

	cout << ans << '\n';
	return 0; 
}
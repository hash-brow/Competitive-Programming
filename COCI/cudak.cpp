#include <bits/stdc++.h>
using namespace std;

int64_t dp[17][136][2];
int S;
int64_t A, B;
int64_t l[16];

int64_t rec(int pos, int sum, int f, int64_t X){
	if(sum < 0) return 0;
	if(pos == 16){
		return dp[pos][sum][f] = (sum == 0 ? 1 : 0);
	}

	if(dp[pos][sum][f] != -1) return dp[pos][sum][f];
	
	int64_t res = 0, L;
	
	L = (!f ? (X / l[pos]) % 10 : 9);
	
	for(int dgt = 0; dgt <= L; dgt++){
		res += rec(pos + 1, sum - dgt, (f || (dgt < L)), X);
	}

	return dp[pos][sum][f] = res;
}
int64_t solve(int64_t X){
	memset(dp, -1, sizeof dp);
	return rec(0, S, 0, X);
}

int main() {
	cin >> A >> B >> S;
	
	l[15] = 1;
	for(int i = 14; i >= 0; --i) l[i] = 10*l[i+1];
	cout << solve(B) - solve(A - 1) << '\n';
	
	int64_t lo = A, hi = B, ans = -1;
	
	while(lo <= hi){
		int64_t mid = (lo + hi) >> 1;
		if(solve(mid) - solve(A - 1) > 0){
			ans = mid;
			hi = mid - 1;
		}
		else lo = mid + 1;
	}
	
	cout << ans << '\n';
	return 0;
}

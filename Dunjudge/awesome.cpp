#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
	int N, C;
	cin >> N >> C;
	
	int pref[2][C + 1];
	memset(pref, 0, sizeof pref);
	for(int i = 0; i <= C; i++)
		pref[0][i] = 1;
		
	int ans = 0;
	
	for(int i = 1; i <= N; i++){
		int t = (i & 1);
		int o = t ^ 1;
		for(int j = 0; j <= C; j++){
			pref[t][j] = ((pref[o][j] - (i > j ? 0 : pref[o][j - i])) % MOD + MOD) % MOD;
			ans = pref[t][j];
			if(j) pref[t][j] = (pref[t][j] + pref[t][j-1]) % MOD;
		}
	}
	
	cout << ans << '\n';
	return 0;
}
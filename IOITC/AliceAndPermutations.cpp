#include <bits/stdc++.h>

using namespace std;

const int MXN = 100001;
const int mod = 1e9 + 7;

vector<int64_t> fact(MXN);

int64_t bin(int64_t a, int64_t b){
	int64_t res = 1;
	while(b){
		if(b&1) (res *= a) %= mod;
		b >>= 1;
		(a *= a) %= mod;
	}
	return res;
}

void solve(){
	int n, k;
	cin >> n >> k;

	if(k >= n){
		return;
		cout << fact[n] << '\n';
	}

	cout << (fact[k]*bin(k+1, n-k))%mod << '\n';
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	fact[0] = 1;
	for(int64_t i = 1; i < MXN; i++)
		fact[i] = (fact[i-1]*i) % mod;
	int t;
	cin >> t;
	while(t--)
		solve();

	return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int64_t mod = 1e9 + 7;

struct BIT{
	vector<int64_t> bit;
	int n;

	BIT(int N){
		this->n = N;
		bit.assign(n+1, 0);
	}
	int64_t sum(int r){
		int64_t ret = 0;
		for(; r >= 1; r = (r&(r+1)) - 1)
			ret += bit[r];
		return ret;
	}
	int64_t sum(int l, int r){
		return sum(r) - sum(l-1);
	}
	void add(int i, int64_t v){
		for(; i <= n; i = i|(i+1))
			bit[i] += v;
	}
};

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int64_t n;
	cin >> n; 
	vector<int64_t> a(n), d(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
		d[i] = a[i];
	}

	sort(d.begin(), d.end());
	for(auto& i : a)
		i = lower_bound(d.begin(), d.end(), i) - d.begin() + 1;

	vector<int64_t> fact(n+1);
	fact[0] = 1;
	for(int64_t i = 1; i <= n; i++)
		(fact[i] = fact[i-1]*i) %= mod;

	BIT D(n);
	int64_t ans = 0; 
	for(int64_t i = 0; i < n; i++){
		int64_t taken = D.sum(0, a[i]-1);
		(ans += ((a[i]-taken-1)*fact[n-i-1]) % mod) %= mod;
		D.add(a[i], 1);
	}

	cout << (ans + 1) % mod << '\n';
	return 0; 
}
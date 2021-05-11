#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int64_t mod1 = 6637466716955509;
const int64_t mod2 = 2062256311;
const int64_t mod3 = 82439290328347;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int N, M;
	cin >> N >> M;

	vector<int64_t> pref1(N+1), pref2(N+1), pref3(N+1);
	
	for(int i = 0; i < M; i++){
		int u, v;
		cin >> u >> v;
		int64_t r = rng() % mod1;
		(pref1[u] += r) %= mod1;
		(pref1[v] -= r - mod1) %= mod1;
		r = rng() % mod2;
		(pref2[u] += r) %= mod2;
		(pref2[v] -= r - mod2) %= mod2;
		r = rng() % mod3;
		(pref3[u] += r) %= mod3;
		(pref3[v] -= r - mod3) %= mod3;
	}

	int64_t ans = 0;
	int64_t cur1 = 0, cur2 = 0, cur3 = 0;
	map<array<int64_t, 3>, int64_t> freq;

	for(int i = 0; i <= N; i++){
		(pref1[i] += mod1) %= mod1;
		(pref2[i] += mod2) %= mod2;
		(pref3[i] += mod3) %= mod3;

		(cur1 += pref1[i]) %= mod1;
		(cur2 += pref2[i]) %= mod2;
		(cur3 += pref3[i]) %= mod3;

		ans += freq[{cur1, cur2, cur3}]++;
	}

	cout << ans << '\n';
	return 0;
}
// #define _GLIBCXX_DEBUG
// #pragma GCC optimize "trapv"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <chrono>

// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

using namespace std;
using namespace __gnu_pbds;
using namespace chrono;

#define pb push_back 
#define f first
#define s second
#define min3(a, b, c) min(min(a, b), c)
#define max3(a, b, c) max(max(a, b), c)
#define all(v) v.begin(), v.end()

typedef long long ll;
typedef double ld;
typedef long double lld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<pii> vpi;
typedef vector<pll> vpl;

template <class T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

const int INF = 1e9;
// const ll INF = 1e18;
const ll mod = 1000000007;
// const ll mod = 998244353;

void solve(int tc){
	int n;
	cin >> n;

	vi d(n-1);

	for(int i = 0; i < n-1; i++)
		cin >> d[i];	

	vi pref(n);
	pref[0] = 0;

	for(int i = 0; i < n-1; i++)
		pref[i+1] = pref[i] + d[i];

	int posl = 1 - *min_element(all(pref)), posr = n - *max_element(all(pref));

	if(posl != posr || posl > n || posr < 1){
		cout << -1 << '\n';
		return;
	}

	vi ans(n);
	ans[0] = posl;

	for(int i = 1; i < n; i++)
		ans[i] = ans[i-1] + d[i-1];

	for(auto &x : ans)
		cout << x << ' ';
}

int main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	#ifdef LOCAL
		auto begin = high_resolution_clock::now();
	#endif

    int tc = 1;
    // cin >> tc; 
    for (int t = 0; t < tc; t++) solve(t);
    
    #ifdef LOCAL 
    	auto end = high_resolution_clock::now();
    	cout << fixed << setprecision(4) << "Execution Time: " << duration_cast<duration<double>>(end - begin).count() << "seconds" << endl;
    #endif
	return 0;
}
// #define _GLIBCXX_DEBUG
// #pragma GCC optimize "trapv"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

using namespace std;
using namespace __gnu_pbds;

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
	int h, w;
	cin >> h >> w;

	vvi mat(h, vi(w));

	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
			cin >> mat[i][j];

	vi d = {-1, 0, 1};
	for(int i = 1; i < h; i++){
		for(int j = 0; j < w; j++){
			int del = 0;
			for(int x : d){
				if(j + x < w && j + x > 0)
					del = max(del, mat[i-1][j+x]);
			}
			mat[i][j] += del;
		}	
	}

	int ans = 0; 
	for(int i = 0; i < w; i++)
		ans = max(ans, mat[h-1][i]);

	cout << ans << '\n';
}

int main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	
	int tc = 1;
	// cin >> tc;
	for (int t = 0; t < tc; t++) solve(t);

	return 0;
}
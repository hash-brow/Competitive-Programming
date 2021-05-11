//#define _GLIBCXX_DEBUG
//#pragma GCC optimize "trapv"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// #pragma GCC target ("avx2")
// #pragma GCC optimization ("O3")
// #pragma GCC optimization ("unroll-loops")
// #pragma optimization_level 3
// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")


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
//const ll INF = 1e18;
const ll mod = 1000000007;
// const ll mod = 998244353;

void solve(int tc){
	int n, k;
	cin >> n >> k;
	vl t(n);

	for(int i = 0; i < n; i++)
		cin >> t[i];

	//turn on and off exactly k times. first start -> t[0], last close -> t[n-1]+1;
	//initial idea -> greedy 
	//sort the elements by adjacent differences and turn of the stove for each of the first k biggest diff

	vector<pair<ll, pair<int, int>>> dif(n-1);

	for(int i = 0; i < n-1; i++){
		dif[i].f = t[i+1] - t[i] - 1;
		dif[i].s = {i, i+1}; 
	}

	sort(all(dif));

	ll dur = 0;

	for(int i = 0; i < n-k; i++){
		dur += dif[i].f;
	}
	dur += n;

	cout << dur << "\n";
}

int main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	
	int tc = 1;
	//cin >> tc;
	for (int t = 0; t < tc; t++) solve(t);

	return 0;
}
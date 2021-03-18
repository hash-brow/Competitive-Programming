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
	int r, c, m;
	cin >> r >> c >> m; 

	vector<string> mat(r);

	for(int i = 0; i < r; i++)
		cin >> mat[i];

	// vector<vector<bool>> grid(r, vector<bool>(c));
	vector<bitset<501>> grid(r); 
	for(int i = 0; i < r; i++)
		for(int j = 0; j < c; j++)
			grid[i][j] = (mat[i][j] == '.' ? 1 : 0); 

	string s;
	cin >> s;

	vector<bitset<501>> dp[2]; 
	// cout << 'x' << '\n';
	dp[0].resize(r), dp[1].resize(r); 
	for(int row = 0; row < r; row++)
		dp[0][row] = grid[row]; 

	for(int i = 0; i < m; i++){
		if(s[i] == 'N')
			for(int row = 1; row < r; row++)
				dp[(i+1)%2][row-1] = (dp[i%2][row]&grid[row-1]&grid[row]); 
		if(s[i] == 'W')
			for(int row = 0; row < r; row++)
				dp[(i+1)%2][row] = ((dp[i%2][row] >> 1)&grid[row]);
		if(s[i] == 'E')
			for(int row = 0; row < r; row++)
				dp[(i+1)%2][row] = ((dp[i%2][row] << 1)&grid[row]); 
		if(s[i] == 'S')
			for(int row = 0; row < r-1; row++)
				dp[(i+1)%2][row+1] = (dp[i%2][row]&grid[row+1]&grid[row]); 
		if(s[i] == '?'){
			for(int row = 1; row < r; row++)
				dp[(i+1)%2][row-1] |= (dp[i%2][row]&grid[row-1]&grid[row]); 
			for(int row = 0; row < r; row++)
				dp[(i+1)%2][row] |= ((dp[i%2][row] << 1)&grid[row]);
			for(int row = 0; row < r; row++)
				dp[(i+1)%2][row] |= ((dp[i%2][row] >> 1)&grid[row]); 
			for(int row = 0; row < r-1; row++)
				dp[(i+1)%2][row+1] |= (dp[i%2][row]&grid[row+1]&grid[row]); 
		}

		for(int row = 0; row < r; row++)
			dp[i&1][row] = bitset<501>(0); 
	}

	int ans = 0; 
	for(int i = 0; i < r; i++)
		ans += dp[m%2][i].count(); 

	cout << ans << '\n';
}

int main(){
	// ios_base::sync_with_stdio(NULL);
	// cin.tie(NULL);
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
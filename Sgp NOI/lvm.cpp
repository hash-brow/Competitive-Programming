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
	int n;
	cin >> n;

	vector<pair<string, int>> a(n);

	for(int i = 0; i < n; i++){
		cin >> a[i].f;
		if(a[i].f == "PUSH" || a[i].f == "IFZERO")
			cin >> a[i].s;
		else{
			a[i].s = -1;
		}
	}

	stack<int> s;
	vi reg;	
	int i = 0;
	while(true){
		// cout << i << ' ';
		if(a[i].f == "PUSH"){
			s.push(a[i].s);
			i++;
		}
		else if(a[i].f == "STORE"){
			reg.pb(s.top());
			s.pop();
			i++;
		}
		else if(a[i].f == "LOAD"){
			// cout << reg.size() << '\n';
			// s.push(reg[0]);
			s.push(reg.back());
			i++;
		}
		else if(a[i].f == "PLUS"){
			int m = s.top();
			s.pop();
			m += s.top();
			s.pop();
			s.push(m);
			i++;
		}
		else if(a[i].f == "TIMES"){
			int m = s.top();
			s.pop();
			m *= s.top();
			s.pop();
			s.push(m);
			i++;
		}
		else if(a[i].f == "IFZERO"){
			if(s.top() == 0)
				i = a[i].s;
			else
				i++;
			s.pop();
		}
		else if(a[i].f == "DONE"){
			break;
		}
	}	

	cout << s.top() << '\n';
	// while(!s.empty()){
		// cout << s.top() << '\n';
		// s.pop();
	// }
}

int main(){
	// ios_base::sync_with_stdio(NULL);
	// cin.tie(NULL);
	
	int tc = 1;
	// cin >> tc;
	for (int t = 0; t < tc; t++) solve(t);

	return 0;
}
/*
14
PUSH 5
STORE
LOAD
LOAD
PUSH -1
PLUS
STORE
LOAD
IFZERO 13
LOAD
TIMES
PUSH 0
IFZERO 3
DONE
*/
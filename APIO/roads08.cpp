#include <bits/stdc++.h>
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
*/

using namespace std;
// using namespace __gnu_pbds;
using namespace chrono;

// mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
/*
template <class T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
*/

//***************** CONSTANTS *****************



//***************** GLOBAL VARIABLES *****************

int cnt = 0, cc, k;

//***************** AUXILIARY STRUCTS *****************

struct DSU{
	vector<int> e;
	int cc; 
	DSU(int N){
		e.resize(N, -1);
		cc = N;
	}
	int get(int x){
		return (e[x] < 0 ? x : e[x] = get(e[x]));
	}
	bool unite(int x, int y){
		x = get(x), y = get(y);
		if(x == y)
			return 0;
		if(e[x] > e[y])
			swap(x, y);
		--cc;
		e[x] += e[y];
		e[y] = x;
		return 1;
	}

	void reset(int N){
		e = vector<int> (N, -1);
		cc = N;
	}
};

//***************** MAIN BODY *****************

/*
add all the red edges first
add as many blue edges as required
reset
add blue edges from step 2
add the rest of the blue edges arbitrarily till cnt is k
then add the red edges to finish things off
*/

void solve(){
	int N, M;
	cin >> N >> M >> k;

	vector<array<int, 3>> blueedge, rededge;

	DSU D(N);

	for(int i = 0; i < M; i++){
		int u, v, c;
		cin >> u >> v >> c;
		--u, --v;

		if(c){ 
			rededge.push_back({u, v, 0});
			D.unite(u, v);
		}
		else blueedge.push_back({u, v, 0});
	}

	if(D.cc > k + 1){
		cout << "no solution\n";
		return;
	}

	int r = D.cc;

	for(auto& [u, v, s] : blueedge){
		if(D.unite(u, v)){
			s = 1;
			cnt++;
		}
	}

	assert(cnt == r - 1);

	D.reset(N);

	for(auto& [u, v, s] : blueedge)
		if(s){
			D.unite(u, v);
		}

	for(auto& [u, v, s] : blueedge){
		if(!s && D.unite(u, v)){
			cnt++;
			s = 1;
		}
		if(cnt == k)
			break;
	}

	if(cnt < k){
		cout << "no solution\n";
		return;
	}

	for(auto& [u, v, s] : rededge)
		if(D.unite(u, v))
			s = 1;

	for(auto& [u, v, s] : blueedge)
		if(s)
			cout << u + 1 << ' ' << v + 1 << ' ' << 0 << '\n';

	for(auto& [u, v, s] : rededge)
		if(s)
			cout << u + 1 << ' ' << v + 1 << ' ' << 1 << '\n';
}

//***************** *****************

int32_t main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);

	#ifdef LOCAL
		auto begin = high_resolution_clock::now();
	#endif

	int tc = 1;
	// cin >> tc; 
	for (int t = 0; t < tc; t++)
		solve();

	#ifdef LOCAL 
		auto end = high_resolution_clock::now();
		cout << fixed << setprecision(4);
		cout << "Execution Time: " << duration_cast<duration<double>>(end - begin).count() << "seconds" << endl;
	#endif

	return 0;
}

/*
If code gives a WA, check for the following : 
1. I/O format

2. Are you clearing all global variables in between tests if multitests are a thing

3. Can you definitively prove the logic
*/
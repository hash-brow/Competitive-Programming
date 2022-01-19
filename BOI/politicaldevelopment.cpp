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

const int MXN = 50000;

//***************** GLOBAL VARIABLES *****************

set<int> g[MXN];
int D[MXN];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	int N, K;
	cin >> N >> K;

	priority_queue<array<int, 2>> pq;

	int sum = 0;

	for(int i = 0; i < N; i++){
		cin >> D[i];
		sum += D[i];
		for(int _ = 0; _ < D[i]; _++){
			int x;
			cin >> x;
			g[i].insert(x);
		}
		pq.push({-D[i], i});
	}

	assert(sum <= 2*N*K);
	
	int ans = 1;

	while(!pq.empty()){
		auto [deg, u] = pq.top();
		pq.pop();
		deg *= -1;

		if(deg != D[u])
			continue;

		vector<int> t(D[u]);
		int ptr = 0;
		for(int v : g[u]) t[ptr++] = v;

		for(int mask = 1; mask < (1 << deg); mask++){
			vector<int> vec;
			for(int i = 0; i < deg; i++)
				if((mask >> i) & 1)
					vec.push_back(t[i]);

			int k = vec.size();
			bool ok = true;

			for(int i = 0; i < k && ok; i++)
				for(int j = i + 1; j < k && ok; j++)
					if(g[vec[i]].find(vec[j]) == g[vec[i]].end()){
						ok = false;
						break;
					}

			if(ok) ans = max(ans, k + 1);
		}

		for(int v : g[u]){
			g[v].erase(u);
			D[v]--;
			pq.push({-D[v], v});
		}
	}

	cout << ans << '\n';
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

4. If the code gives an inexplicable TLE, and you are sure you have the best possible complexity,
use faster io
*/
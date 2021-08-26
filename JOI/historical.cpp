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

const int MXN = 100'000;
const int B = 320;

//***************** GLOBAL VARIABLES *****************

int64_t X[MXN], ans[MXN], block[B], cnt[B][MXN], val[MXN];
array<int, 3> query[MXN];
int L[B], R[B], num, c[MXN], belong[MXN];
int N;

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void add(int idx){
	for(int i = 0; i <= belong[idx]; i++){
		cnt[i][c[idx]] += X[idx];
		block[i] = max(block[i], cnt[i][c[idx]]);
	}

	for(int j = L[belong[idx]]; j <= idx; j++)
		if(X[j] == X[idx])
			val[j] += X[idx];
}

int64_t answer(int l, int r){
	int64_t ret = 0;
	for(int i = belong[l] + 1; i < belong[r]; i++)
		ret = max(ret, block[i]);

	int temp[MXN];
	memset(temp, 0, sizeof temp);
	int cur = belong[l];

	for(int i = L[cur]; i <= min(R[cur], r); i++){
		// cout << cur << ' ' << cnt[cur][c[i]] << '\n'; 
		val[i] = cnt[cur][c[i]] - temp[c[i]] * X[i];
		temp[c[i]]++;

		if(i >= l) ret = max(ret, val[i]);
		// cout << ret << '\n';
	}

	for(int i = max(l, L[belong[r]]); i <= r; i++){
		ret = max(ret, val[i]);
		// cout << ret << '\n';
	}

	return ret;
}

void solve(){
	int Q;
	cin >> N >> Q;

	vector<int> discrete;

	for(int i = 0; i < N; i++){
		cin >> X[i];
		discrete.push_back(X[i]);
	}

	sort(discrete.begin(), discrete.end());
	discrete.erase(unique(discrete.begin(), discrete.end()), discrete.end());

	for(int i = 0; i < N; i++)
		c[i] = lower_bound(discrete.begin(), discrete.end(), X[i]) - discrete.begin();

	for(int i = 0; i < Q; i++){
		auto& [l, r, idx] = query[i];
		cin >> l >> r;
		--l, --r;
		idx = i;
	}

	sort(query, query + Q, [](array<int, 3> a, array<int, 3> b){
		return a[1] < b[1];
	});
	
	num = N / B;

	for(int i = 0; i < num; i++){
		L[i] = i * B;
		R[i] = (i + 1) * B - 1;
		if(i == num - 1) R[i] = N - 1;
		for(int j = L[i]; j <= R[i]; j++)
			belong[j] = i;
	}

	int ptr = 0;

	for(int _ = 0; _ < Q; _++){
		auto [l, r, idx] = query[_];
		while(ptr <= r){
			add(ptr++);
			// cout << "val: ";
			// for(int i = 0; i < N; i++)
			// 	cout << val[i] << ' ';
			// cout << '\n';
		}

		ans[idx] = answer(l, r);
		// cout << "val: ";
		// for(int i = 0; i < N; i++)
		// 	cout << val[i] << ' ';
		// cout << '\n';
	}

	for(int i = 0; i < Q; i++) cout << ans[i] << '\n';
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
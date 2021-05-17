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

#ifndef LOCAL
const int MXN = 200003;
#endif
#ifdef LOCAL
const int MXN = 2000;
#endif

//***************** GLOBAL VARIABLES *****************

int N, Q;

//***************** AUXILIARY STRUCTS *****************

int t[MXN << 2];
map<int, int> cnt[MXN];

void build(int v, int tl, int tr){
	if(tl == tr){
		t[v] = 1;
		return;
	}

	int tm = (tl + tr) >> 1;

	build(v << 1, tl, tm);
	build(v << 1|1, tm + 1, tr);

	t[v] = t[v << 1] + t[v << 1|1]; 
}

void update(int v, int tl, int tr, int pos, int x, int c){
	if(tl == tr){
		cnt[tl][x] += c;
		if(cnt[tl][x] == 0)
			cnt[tl].erase(x);
		t[v] = (cnt[tl].empty());
		return;
	}

	int tm = (tl + tr) >> 1;
	if(pos <= tm)
		update(v << 1, tl, tm, pos, x, c);
	else
		update(v << 1|1, tm + 1, tr, pos, x, c);

	t[v] = t[v << 1] + t[v << 1|1];
}

void update(int p, int x, int c) { update(1, 1, N, p, x, c); }

int query(int v, int tl, int tr, int l, int r){
	if(l > r)
		return 0;

	if(tl == l && tr == r)
		return t[v];

	int tm = (tl + tr) >> 1;

	return query(v << 1, tl, tm, l, min(tm, r)) + query(v << 1|1, tm + 1, tr, max(l, tm + 1), r);
}

int query(int l, int r) { return query(1, 1, N, l, r); }

//***************** MAIN BODY *****************

void solve(){
	cin >> N >> Q;

	build(1, 1, N);
	for(int i = 0; i < Q; i++){
		int type;
		cin >> type;
		if(type == 1){
			int l, r, x;
			cin >> l >> r >> x;	
			update(l, x, 1);
			if(r < N) update(r + 1, x, -1);
		}
		else{
			int l, r;
			cin >> l >> r;
			cout << (query(l + 1, r) >= r - l ? 1 : 0) << '\n';
		}
	}
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
	solve();

	#ifdef LOCAL 
		auto end = high_resolution_clock::now();
		cout << fixed << setprecision(4);
		cout << "Execution Time: " << duration_cast<duration<double>>(end - begin).count() << "seconds" << endl;
    #endif

	return 0;
}
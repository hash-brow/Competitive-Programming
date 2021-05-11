#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

struct dsu{
	vector<int> e;
	vector<ordered_set<int>> pbds; 
	int64_t total = 0;

	dsu(int Q, vector<int>& a, vector<int>& section){
		e.resize(Q+1, -1);
		pbds.resize(Q+1);

		for(int i = 0; i <= Q; i++){
			for(int l = section[i]+1; l <= section[i+1]; l++){
				total += int64_t(pbds[i].size() - pbds[i].order_of_key(a[l]));
				pbds[i].insert(a[l]);
			}
		}
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
		e[x] += e[y];

		for(int i : pbds[y]){
			total += int64_t(x < y ? pbds[x].size() - pbds[x].order_of_key(i) : pbds[x].order_of_key(i));
		}

		for(int i : pbds[y])
			pbds[x].insert(i);
		
		e[y] = x;
		return 1;
	}
};

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int N, Q;
	cin >> N >> Q;

	vector<int> A(N+1);
	for(int i = 1; i <= N; i++)
		cin >> A[i];

	vector<array<int, 2>> query(Q);
	vector<int> section(Q+2);
	section[0] = 0, section[Q+1] = N;

	for(int i = 0; i < Q; i++){
		cin >> query[i][0];
		section[i+1] = query[i][0];
	}

	sort(section.begin(), section.end());

	for(int i = 0; i < Q; i++){
		query[i][1] = lower_bound(section.begin(), section.end(), query[i][0]) - section.begin();
	}

	dsu D(Q, A, section);

	vector<int64_t> ans(Q);

	for(int i = Q-1; i >= 0; --i){		
		ans[i] = D.total;
		D.unite(query[i][1]-1, query[i][1]);
	}

	for(int i = 0; i < Q; i++)
		cout << ans[i] << '\n';
	return 0; 
}
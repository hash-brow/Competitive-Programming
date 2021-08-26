#include <bits/stdc++.h>

using namespace std;

const int B = 320;

struct BIT{
	vector<int> tree;
	int N;

	BIT(int n){
		N = n;
		tree.resize(N+1);
	}

	void upd(int pos, int val){
		for(; pos <= N; pos += (pos&(-pos)))
			tree[pos] += val;
	}

	int sum(int pos){
		int sum = 0;
		for(; pos > 0; pos -= (pos&(-pos)))
			sum += tree[pos];
		return sum;
	}

	int sum(int l, int r){
		return sum(r) - sum(l-1);
	}
};

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, q;
	cin >> n >> q;

	vector<int> a(n+1);
	vector<int> discrete(n+1);

	for(int i = 1; i <= n; i++){
		cin >> a[i];
		discrete[i] = a[i];
	}

	sort(discrete.begin(), discrete.end());
	discrete.erase(unique(discrete.begin(), discrete.end()), discrete.end());
	for(int i = 1; i <= n; i++)
		a[i] = lower_bound(discrete.begin(), discrete.end(), a[i]) - discrete.begin();

	vector<array<int, 3>> query(q);

	for(int i = 0; i < q; i++){
		auto& [l, r, idx] = query[i];
		cin >> l >> r;
		idx = i;
	}	

	sort(query.begin(), query.end(), [&](const array<int, 3>& A, const array<int, 3>& b){
		if(A[0] / B != b[0] / B)
			return A < b;
		return (A[0] / B & 1) ? (A[1] < b[1]) : (A[1] > b[1]);
	});

	BIT bit(n);
	// auto [l, r, id] = query[0];
	int64_t ans = 0;
	int l = 1, r = 0;
	/*for(int i = l; i <= r; i++){
		ans += bit.sum(a[i]+1, n);
		bit.upd(a[i], 1);
	}*/

	vector<int64_t> answer(q);
	for(auto& [ql, qr, idx] : query){
		// cout << ql <<  ' ' << qr << ' ' << idx << ' ';
		while(l > ql){
			l--;
			ans += (int64_t)bit.sum(1, a[l] - 1);
			bit.upd(a[l], 1);
		}
		while(r < qr){
			r++;
			bit.upd(a[r], 1);
			ans += (int64_t)bit.sum(a[r] + 1, n);
		}
		while(l < ql){
			ans -= (int64_t)bit.sum(1, a[l] - 1);
			bit.upd(a[l], -1);
			l++;
		}
		while(r > qr){
			ans -= (int64_t)bit.sum(a[r]+1, n);
			bit.upd(a[r], -1);
			r--;
		}
		// cout << ans << '\n';
		answer[idx] = ans;
	}

	for(int64_t i : answer)
		cout << i << '\n';
	return 0; 
}
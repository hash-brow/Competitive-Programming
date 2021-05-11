#include <bits/stdc++.h>

using namespace std;

priority_queue<int> lpq;
priority_queue<int, vector<int>, greater<int>> rpq;
int64_t L, R;

void insert(int x) {
	int median = (lpq.size() ? lpq.top() : 1000000001);
	if (x <= median) {
		lpq.push(x);
		L += x;
	} else {
		rpq.push(x);
		R += x;
	}

	if (rpq.size() + 1 < lpq.size()) {
		int nxt = lpq.top();
		lpq.pop();
		rpq.push(nxt);
		L -= nxt;
		R += nxt;
	} else if (lpq.size() < rpq.size()) {
		int nxt = rpq.top();
		rpq.pop();
		lpq.push(nxt);
		R -= nxt;
		L += nxt;
	}
}

int64_t pref[100001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int k, n;
	int64_t same = 0;
	vector<array<int, 2>> v = {{0, 0}};

	cin >> k >> n;
	
	for(int i = 0; i < n; i++) {
		char a, b;
		int x, y;
		cin >> a >> x >> b >> y;
		if (a == b) same += abs(x - y);
		else v.push_back({x, y});
	}
	
	sort(v.begin(), v.end(), [](array<int, 2>&a, array<int, 2>&b){
		return (a[0] + a[1] < b[0] + b[1]);
	});
	
	n = v.size() - 1;
	same += n;

	L = R = 0;
	for(int i = 1; i < n + 1; i++) {
		insert(v[i][0]);
		insert(v[i][1]);
		pref[i] = R - L;
	}

	int64_t ans = pref[n];

	if (k == 2) {
		while (lpq.size()) lpq.pop();
		while (rpq.size()) rpq.pop();
		L = R = 0;

		for(int i = n; i; i--) {
			insert(v[i][0]);
			insert(v[i][1]);
			ans = min(ans, R - L + pref[i - 1]);
		}
	}
	cout << same + ans;
	return 0;
}
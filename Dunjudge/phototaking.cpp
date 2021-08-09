#include <bits/stdc++.h>
using namespace std;

const int MXN = 10000000;

int64_t P[MXN + 2];

inline int64_t readInt() {
	int64_t x = 0;
	char ch = getchar_unlocked();
	while (ch < '0' || ch > '9') ch = getchar_unlocked();
	while (ch >= '0' && ch <= '9'){
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar_unlocked();
	}
	return x;
}

int main() {
	int N; int64_t S;
	N = readInt(); S = readInt();
	P[0] = 0;
	for(int i = 1; i <= N; i++){
		P[i] = readInt();
		P[i] += P[i-1];
	}
	P[N+1] = 1'000'000'000'000;
	int64_t ans = 0;
	int fwd = 1;
	for(int i = 1; i <= N; i++){
		while(fwd <= N && P[i-1] + S >= P[fwd]) fwd++;
		ans += (fwd - i);
	}
	
	cout << ans << '\n';
	
	return 0;
}
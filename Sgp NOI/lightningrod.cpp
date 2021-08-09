#include <bits/stdc++.h>
using namespace std;

inline int readInt() {
	int x = 0;
	char ch = getchar_unlocked();
	while (ch < '0' || ch > '9') ch = getchar_unlocked();
	while (ch >= '0' && ch <= '9'){
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar_unlocked();
	}
	return x;
}

int X[10000000], Y[10000000];
inline bool covers(int i, int j){
	if(abs(X[i] - X[j]) <= Y[i] - Y[j]) 
		return true;

	return false;
}
int main(){
	int n = readInt();
	for(int i = 0; i < n; i++) {
		X[i] = readInt();
		Y[i] = readInt();
	}
	
	// stack<int> r;
	vector<int> r;
	r.push_back(0); 
	for(int i = 1; i < n; i++){
		if(covers(r.back(), i)) continue;

		while(!r.empty() && covers(i, r.back())) 
			r.pop_back();

		r.push_back(i);
	}
		
		cout << r.size() << '\n'; 
	return 0;
}

#include "dna.h"
#include <bits/stdc++.h>

using namespace std;

const int MXN = 100000;
int cnt[MXN][3][3];
int cur[3][3];

void init(string a, string b) {
	map<char, int> mp;
	mp['A'] = 0, mp['T'] = 1, mp['C'] = 2;

	int N = a.size();
	for(int i = 0; i < N; i++){
		if(i) for(int j = 0; j < 3; j++)
			for(int k = 0; k < 3; k++)
				cnt[i][j][k] = cnt[i-1][j][k];

		cnt[i][mp[a[i]]][mp[b[i]]]++;
	}
}

int get_distance(int l, int r) {
	auto get_inv = [&](int x, int y){
		return cnt[r][x][y] - (l ? cnt[l-1][x][y] : 0);
	};

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			cur[i][j] = get_inv(i, j);

	int ans = 0;

	for(int i = 0; i < 3; i++){
		int j = (i + 1) % 3;
		int x = min(cur[i][j], cur[j][i]);
		cur[j][i] -= x, cur[i][j] -= x;
		ans += x;
	}

	bool pos = 1;
	for(int i = 0; i < 3; i++) pos &= (cur[i][(i + 1)%3] == cur[0][1]);
	for(int i = 0; i < 3; i++) pos &= (cur[(i + 1)%3][i] == cur[1][0]);

	if(!pos) return -1;
	return ans + 2*(cur[0][1] + cur[1][0]);
}

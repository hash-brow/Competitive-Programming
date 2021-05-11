#include <bits/stdc++.h>
#include "secret.h"

using namespace std;

const int MXN = 1005;

int st[10][MXN], mask[MXN], a[MXN], n;

void dnc(int l, int r, int lev){
	if(l == r)
		return;

	int mid = (l+r)>>1;

	st[lev][mid] = a[mid];
	st[lev][mid+1] = a[mid+1];

	for(int i = mid-1; i >= l; --i)
		st[lev][i] = Secret(a[i], st[lev][i+1]);

	for(int i = mid+2; i <= r; i++)
		st[lev][i] = Secret(st[lev][i-1], a[i]);

	for(int i = mid+1; i <= r; i++)
		mask[i] ^= (1 << lev);

	dnc(l, mid, lev+1), dnc(mid+1, r, lev+1);
}

void Init(int N, int A[]){
	for(int i = 0; i < N; i++)
		a[i] = A[i];
	dnc(0, N-1, 0);
}

int Query(int L, int R){
	if(L == R)
		return a[L];
	int level = __builtin_ctz(mask[L]^mask[R]);
	return Secret(st[level][L], st[level][R]);
}
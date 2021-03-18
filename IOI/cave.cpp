#include <bits/stdc++.h>
#include "cave.h"

using namespace std;

const int MXN = 5001;
int n;
int fincolorswitch[MXN], q[MXN], door[MXN];
vector<bool> found(MXN);

bool open(int last, int looking){
	return (last == -1) | (last > looking);
}

void dnc(int leftSwitch, int rightSwitch, int targetDoor, int color){
	if(leftSwitch == rightSwitch){
		door[leftSwitch] = targetDoor;
		fincolorswitch[leftSwitch] = color;
		found[leftSwitch] = 1;
		return;
	}

	memset(q, 0, sizeof q);
	int mid = (leftSwitch + rightSwitch) >> 1;

	for(int i = leftSwitch; i <= mid; i++)
		q[i] = color;
	for(int i = mid+1; i <= rightSwitch; i++)
		q[i] = color^1;

	for(int i = 0; i < n; i++)
		if(found[i])
			q[i] = fincolorswitch[i];

	if(open(tryCombination(q), targetDoor))
		dnc(leftSwitch, mid, targetDoor, color);
	else dnc(mid+1, rightSwitch, targetDoor, color);
}

int getCol(int cur){
	memset(q, 0, sizeof q);
	for(int i = 0; i < n; i++)
		if(found[i])
			q[i] = fincolorswitch[i];

	int ans = tryCombination(q);
	if(open(ans, cur)) return 0;

	return 1;
}

void exploreCave(int N){
	n = N;

	for(int i = 0; i < n; i++){
		int col = getCol(i);
		dnc(0, n-1, i, col);
	}

	answer(fincolorswitch, door);
}
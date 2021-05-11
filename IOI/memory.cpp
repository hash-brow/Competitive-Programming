#include <bits/stdc++.h>
#include "memory.h"
#include "grader.h"

using namespace std;

const int N = 50;

void play(){
	int a[N+1];
	for(int i = 1; i <= N; i++)
		a[i] = faceup(i);

	for(int i = 1; i <= N; i++)
		for(int j = i+1; j <= N; j++)
			if(a[i] == a[j]){
				faceup(i);
				faceup(j);
			}

	return;
}
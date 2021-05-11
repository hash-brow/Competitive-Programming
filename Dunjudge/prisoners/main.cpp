#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "prisoner.h"
#include "swapper.h"

using namespace std;

int N;
int boxes[3000];
int tboxes[3000];
int n_swaps = 0;
int n_saved = 0;
int n_boxes_opened = 0;
int current_prisoner;

void swapKeys(int a, int b) {
	int t = boxes[a];
	boxes[a] = boxes[b];
	boxes[b] = t;
	n_swaps++;
	if (n_swaps>100) {
		fprintf(stderr, "Too many swaps!\n");
		exit(0);
	}
	return;
}

int openBox(int x) {
	if (boxes[x]==current_prisoner) {
		n_saved++;
		current_prisoner = -1;
	}
	n_boxes_opened++;
	if (n_boxes_opened>N) {
		fprintf(stderr, "Too many boxes opened!\n");
		exit(0);
	}
	return boxes[x];
}

int main () {
	scanf("%d", &N);
	for (int i = 0; i < 2*N; i++) {
		scanf("%d", &boxes[i]);
		tboxes[i] = boxes[i];
	}

	swapper(N,tboxes);
	
	for (int i = 0; i < 2*N; i++) {
		current_prisoner = i;
		n_boxes_opened = 0;
		prisoner(N,current_prisoner);
	
	}
	double frac_saved = ((double)n_saved) / ((double)(2*N));
	double score = (frac_saved*frac_saved) / (double)max(1,n_swaps);
	printf("Score: %lf\nSaved %d prisoners using %d swaps.\n", score, n_saved, n_swaps);
	return 0;
}

const int MXN = 1000001;
 
char s[MXN];
int up[20][MXN], D[MXN], p[MXN];
int idx = 0, c = 0;
 
void Init(){}
 
void TypeLetter(char L){
	s[++idx] = L;
	up[0][idx] = p[c];
	D[idx] = D[p[c]] + 1;
	p[++c] = idx;
	for(int i = 1; i < 20; i++) up[i][idx] = up[i-1][up[i-1][idx]];
}
 
void UndoCommands(int U){
	++c;
	p[c] = p[c-U-1];
}
 
char GetLetter(int P){
	int v = p[c]; 
	++P;
	for(int i = 19; i >= 0; --i) if((D[v] - P) & (1 << i)) v = up[i][v];
	return s[v];
}

const int MXN = 100000;
const int MXK = 20;

int st[MXK][MXN], mask[MXN], a[MXN], n;

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
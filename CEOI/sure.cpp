#include <bits/stdc++.h>

using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n;

	vector<double> a(n+1), b(n+1);
	for(int i = 1; i <= n; i++){
		cin >> a[i] >> b[i];
	}

	sort(a.rbegin(), a.rend() - 1);
	sort(b.rbegin(), b.rend() - 1);

	double sa = 0, sb = 0, ans = 0;
	int ia = 1, ib = 1;
	for(int i = 1; i <= 2*n; i++){
		if(ia == n+1)
			sb += b[ib++];
		else if(ib == n+1)
			sa += a[ia++];
		else{
			if(sa > sb)
				sb += b[ib++];
			else sa += a[ia++];
		}
		ans = max(ans, min(sa, sb) - i);
	}

	cout << fixed << setprecision(4) << ans << '\n';
	return 0; 
}
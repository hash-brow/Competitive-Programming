#include <bits/stdc++.h>
using namespace std;
int main() {
    int x, n;
    cin >> x >> n;
    
    int avail = x;
    for(int i = 0; i < n; i++){
        int use;
        cin >> use;
        avail = avail - use + x;
    }
    
    cout << avail << '\n';
}
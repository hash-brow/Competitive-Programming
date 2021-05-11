#include <bits/stdc++.h>

using namespace std;

const int MXA = 2000001;
const int MXN = 100000;
const int P = 148933;

const int INF = 1000000000;

vector<int> idx(MXA), spf(MXA);
vector<bool> isp(MXA, 1);
int counter = 0;

void sieve(){
    isp[0] = isp[1] = 0;
    idx[0] = idx[1] = -1;
    for(int i = 2; i < MXA; i++){
        if(!isp[i])
            continue;
        idx[i] = counter++;
        spf[i] = i;
        if(i*1LL*i >= MXA)
            continue;
        for(int j = i*i; j < MXA; j += i){
            spf[j] = i;
            isp[j] = 0;
        }
    }
}

vector<vector<int>> g, gr;
vector<bool> vis(MXN, 0), c(MXN, -1);
vector<int> temp[2];
int m[2];
bool bad = false;

void dfs(int node, int col){
    temp[col].push_back(node);
    vis[node] = 1;
    m[col] = min(m[col], node);
    c[node] = col;
    for(int v : g[node]){
        if(vis[v] && c[v] == col){
            bad = true;
        }
        if(!vis[v])
            dfs(v, col^1);
    }
}

void solve(){
    g.clear(), gr.clear();
    temp[0].clear(), temp[1].clear();
    vis.assign(MXN, 0);
    c.assign(MXN, -1);
    
    bad = false;

    int n;
    cin >> n;
    vector<int> a(n);

    g.resize(n), gr.resize(P);
    
    for(int i = 0; i < n; i++){
        cin >> a[i];
        int v = a[i];
        while(v > 1){ 
            int ori = spf[v];
            gr[idx[ori]].push_back(i);
            while(v > 1 && v % ori == 0){
                v /= ori;
            }
        }
    }

    for(int i = 0; i < P; i++){
        if(gr[i].size() > 2){
            cout << -1 << '\n';
            return;
        }
    }

    vector<int> ans;

    for(int i = 0; i < P; i++){
        if(gr[i].size() == 2){
            g[gr[i][0]].push_back(gr[i][1]);
            g[gr[i][1]].push_back(gr[i][0]);
        }
    }

    for(int i = 0; i < n; i++){
        if(vis[i] == 1)
            continue;

        temp[0].clear(); m[0] = INF;
        temp[1].clear(); m[1] = INF;

        dfs(i, 0);

        if(temp[0].size() > temp[1].size() || (temp[0].size() == temp[1].size() && m[0] < m[1])){
            for(int v : temp[0])
                ans.push_back(v);
        }
        else{
            for(int v : temp[1]){
                ans.push_back(v);
            }
        }
    }
    if(bad){
        cout << -1 << '\n';
        return;
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for(int v : ans)
        cout << v+1 << ' ';
    
    cout << "\n"; 
}

int32_t main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
    
    sieve();
    int t;
    cin >> t;
    while(t--){
        solve();
    }

    return 0; 
}
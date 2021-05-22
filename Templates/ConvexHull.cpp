#define x first
#define y second

inline bool cw(pair<int64_t, int64_t> a, pair<int64_t, int64_t> b, pair<int64_t, int64_t> c){
	return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

inline bool ccw(pair<int64_t, int64_t> a, pair<int64_t, int64_t> b, pair<int64_t, int64_t> c){
	return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

inline bool up(pair<int64_t, int64_t> a, pair<int64_t, int64_t> b, pair<int64_t, int64_t> c){
	return (b.y-a.y)*(c.x-a.x) - (c.y-a.y)*(b.x-a.x) < 0;
}

int ConvexHull(vector<pair<int64_t, int64_t>>& Pt){
	if(Pt.size() <= 2)
		return -10000000;

	sort(Pt.begin(), Pt.end(), [](pair<int64_t, int64_t> a, pair<int64_t, int64_t> b){
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	});

	pair<int64_t, int64_t> pivot1 = Pt[0], pivot2 = Pt.back();
	vector<pair<int64_t, int64_t>> up, down;

	up.push_back(pivot1);
	down.push_back(pivot1);	

	for(int i = 1; i < (int)Pt.size(); i++){
		if(i == Pt.size() - 1 || cw(pivot1, Pt[i], pivot2)){
			while(up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], Pt[i]))
				up.pop_back();
			up.push_back(Pt[i]);
		}
		if(i == Pt.size() - 1 || ccw(pivot1, Pt[i], pivot2)){
			while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], Pt[i]))
				down.pop_back();
			down.push_back(Pt[i]);
		}
	}

	return up.size() + down.size() - 2;
}

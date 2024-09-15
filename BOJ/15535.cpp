#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

map<int, pair<int, int> > pt;
vector<int> xc,mn,mx;
long long area[100010];

long long ccw(long long a, long long b, long long c, long long d, long long e, long long f)
{
	return a * (d - f) + c * (f - b) + e * (b - d);
}

long long ccw(pair<long long, long long> a, pair<long long, long long> b, pair<long long, long long> c)
{
	return ccw(a.first,a.second,b.first,b.second,c.first,c.second);
}

int main()
{
	int N; scanf ("%d",&N);
	for (int i=0;i<N;i++){
		int x,y; scanf ("%d %d",&x,&y);
		if (pt.count(x)){
			auto &p = pt[x];
			p.first = min(p.first,y);
			p.second = max(p.second,y);
		}
		else pt[x] = {y,y};
	}

	N = pt.size();
	for (auto &p : pt){
		xc.push_back(p.first);
		mn.push_back(p.second.first);
		mx.push_back(p.second.second);
	}

	for (int k=0;k<2;k++){
		vector<pair<long long, long long> > upp,low;
		int us = 0, ls = 0; long long ar = 0;
		for (int i=0;i<N;i++){
			if (k) area[N-i-1] += ar;

			while (us >= 2 && ccw(upp[us-2],upp[us-1],{xc[i],mx[i]}) >= 0){
				us--;
				ar -= (upp[us].second + upp[us-1].second) * (upp[us].first - upp[us-1].first);
				upp.pop_back();
			}
			upp.push_back({xc[i],mx[i]});
			if (us > 0){
				ar += (upp[us].second + upp[us-1].second) * (upp[us].first - upp[us-1].first);
			}
			us++;

			while (ls >= 2 && ccw(low[ls-2],low[ls-1],{xc[i],mn[i]}) <= 0){
				ls--;
				ar += (low[ls].second + low[ls-1].second) * (low[ls].first - low[ls-1].first);
				low.pop_back();
			}
			low.push_back({xc[i],mn[i]});
			if (ls > 0){
				ar -= (low[ls].second + low[ls-1].second) * (low[ls].first - low[ls-1].first);
			}
			ls++;

			if (!k) area[i] += ar;
		}

		reverse(xc.begin(),xc.end());
		reverse(mn.begin(),mn.end());
		reverse(mx.begin(),mx.end());
		for (auto &x : xc) x = -x;
	}

	long long ans = area[0];
	for (int i=0;i<N;i++) if (ans > area[i]) ans = area[i];
	printf ("%lld\n",(ans+1)/2);

	return 0;
}
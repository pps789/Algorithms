#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

/*
	Verify: https://www.acmicpc.net/problem/2150
	Complexity: O(V+E)
	Usage:
		TarjanScc();
		TarjanScc::init(int size);
		TarjanScc::g[u].push_back(v);
		TarjanScc::process();
		TarjanScc::scc;
*/

class TarjanScc{
public:
	vector<vector<int> > g;
	vector<int> scc;
	int sccCount;
	int vCount;

	vector<int> lowlink;
	stack<int> st;

	void init(int size){
		g.resize(size);
		for (auto& v : g) v.clear();
	}

	int dfs(int v){
		int ret = lowlink[v] = ++vCount;
		st.push(v);

		for (int u : g[v])
			if (lowlink[u] == -1)
				ret = min(ret, dfs(u));
			else if (scc[u] == -1)
				ret = min(ret, lowlink[u]);

		if (ret == lowlink[v]){
			++sccCount;
			while (1){
				int t = st.top(); st.pop();
				scc[t] = sccCount;
				if (t == v) break;
			}
		}

		return lowlink[v] = ret;
	}

	void process(){
		sccCount = vCount = -1;
		lowlink = scc = vector<int>(g.size(), -1);
		st = {};

		for (int i = 0; i < g.size(); i++)
			if (scc[i] == -1)
				dfs(i);
	}
};
#include<vector>
#include<stack>
#include<algorithm>
#include<tuple>
using namespace std;

/*
	Verify: https://www.acmicpc.net/problem/11281
	Complexity: O(N+M)
	Usage:
		TwoSAT();
		TwoSAT::init(int size);
		TwoSAT::add(int u, int v);
		TwoSAT::imply(int u, int v);
		pair<bool, vector<bool> > TwoSAT::process();
*/

class TwoSAT{
public:
	int n;
	vector<vector<int> > g;
	vector<int> scc;
	int sccCount;
	int vCount;

	vector<int> lowlink;
	stack<int> st;

	void init(int size){
		n = size;
		g.resize(size * 2);
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

	void get_scc(){
		sccCount = vCount = -1;
		lowlink = scc = vector<int>(g.size(), -1);
		st = {};

		for (int i = 0; i < g.size(); i++)
			if (scc[i] == -1)
				dfs(i);
	}

	static inline int neg(int v){
		return v ^ 1;
	}

	static inline int push(int v){
		if (v > 0) return 2 * v - 1;
		else return neg(2 * (-v) - 1);
	}

	static inline int pop(int v){
		return (v + 1) >> 1;
	}

	void imply(int u, int v){
		// insert " u->v "
		u = push(u), v = push(v);
		g[u].push_back(v);
		g[neg(v)].push_back(neg(u));
	}

	void add(int u, int v){
		// insert " u or v "
		u = push(u), v = push(v);
		g[neg(u)].push_back(v);
		g[neg(v)].push_back(u);
	}

	pair<bool, vector<bool> > process(){
		// <feasible, should be true, should be false>
		get_scc();
		pair<bool, vector<bool> > ret(true, vector<bool>(n + 1));

		for (int i = 1; i <= n; i++) {
			if (scc[push(i)] == scc[neg(push(i))]){
				ret.first = false;
				return ret;
			}
			else if (scc[push(i)] < scc[neg(push(i))]){
				ret.second[i] = true;
			}
		}
		return ret;
	}
};
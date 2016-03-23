#include<vector>
using namespace std;

/*
Verify: https://www.acmicpc.net/problem/9248
Complexity: O(n)
Usage:
    LCP(const vector<Ty> &str, const vector<int> &suffix_array)
    LCP::process();
    LCP::lcp;
 */

template <typename Ty>
class LCP{
public:
    const vector<int> &sa;
    const vector<Ty> &str;
    vector<int> lcp;

    LCP(const vector<Ty> &_str, const vector<int> &_sa): str(_str), sa(_sa) {}

    void process(){
        int n = sa.size();
        lcp.resize(n);
        vector<int> sa_inv(n);

        for(int i = 0; i < n; i++)
            sa_inv[sa[i]] = i;

        int l = 0;
        for(int i = 0; i < n; i++){
            if(sa_inv[i] > 0){
                int j = sa[sa_inv[i] - 1];
                while(i + l < n && j + l < n && str[i + l] == str[j + l]) l++;
                lcp[sa_inv[i]] = l;
                if(l > 0) l--;
            }
        }
    }
};

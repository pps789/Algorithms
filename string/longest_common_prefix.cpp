#include<vector>
using namespace std;

/*
Verify: https://www.acmicpc.net/problem/9248
Complexity: O(n)
Usage:
    Longest_Common_Prefix(const SuffixArray &suffix_array)
    Longest_Common_Prefix::process();
    Longest_Common_Prefix::LCP;
 */

template <typename Ty>
class LongestCommonPrefix{
public:
    const vector<int> &sa;
    const vector<Ty> &str;
    vector<int> LCP;

	LongestCommonPrefix
		(const SuffixArray &_sa) : sa(_sa.SA), str(_sa.str) {}

    void process(){
        int n = sa.size();
		LCP.resize(n);
        vector<int> sa_inv(n);

        for(int i = 0; i < n; i++)
            sa_inv[sa[i]] = i;

        int l = 0;
        for(int i = 0; i < n; i++){
            if(sa_inv[i] > 0){
                int j = sa[sa_inv[i] - 1];
                while(i + l < n && j + l < n && str[i + l] == str[j + l]) l++;
				LCP[sa_inv[i]] = l;
                if(l > 0) l--;
            }
        }
    }
};

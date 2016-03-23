#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

/*
Verify: http://www.spoj.com/problems/SARRAY/
Complexity: O(nlogn)
Usage:
	SuffixArray(Ty* s, int size);
	SuffixArray::process();
	SuffixArray::SA;
*/

template<typename Ty>
class SuffixArray{
public:
	vector<Ty> str;
	vector<int> SA;
	SuffixArray(const Ty* s, int size){
		str = vector<Ty>(size);
		for (int i = 0; i < size; i++) str[i] = s[i];
	}

	void process(){
		int n = str.size();
		SA.resize(n);
		for (int i = 0; i < n; i++) SA[i] = i;
		sort(SA.begin(), SA.end(), [&](int i, int j){ return str[i] < str[j]; });

		vector<int> bucket(n), tmp(n), bucket_cnt(n), tmp_bucket(n);
		int t = 0;
		for (int i = 0; i < n; i++){
			bucket[SA[i]] = t;
			if (i < n - 1 && str[SA[i + 1]] != str[SA[i]]) t = i + 1;
		}
		for (int T = 1; T < n; T <<= 1){
			for (int i = n - T; i < n; i++){
				int b = bucket[i];
				tmp[b + bucket_cnt[b]] = i;
				bucket_cnt[b]++;
			}
			for (int i = 0; i < n; i++){
				int id = SA[i] - T;
				if (id >= 0){
					int b = bucket[id];
					tmp[b + bucket_cnt[b]] = id;
					bucket_cnt[b]++;
				}
			}
			t = 0;
			for (int i = 0; i < n; i++){
				tmp_bucket[tmp[i]] = t;
				if (i < n - 1 && (bucket[tmp[i + 1]] != bucket[tmp[i]] || tmp[i] >= n - T || bucket[tmp[i + 1] + T] != bucket[tmp[i] + T]))
					t = i + 1;
			}
			swap(SA, tmp); swap(bucket, tmp_bucket);
			fill(bucket_cnt.begin(), bucket_cnt.end(), 0);
		}
	}
};

#include<cstdio>
char buff[111111];

int main(){
	scanf("%s", buff);
	int n = strlen(buff);
	SuffixArray<char> sa(buff, n);

	sa.process();
	for (int i = 0; i < n; i++) printf("%d\n", sa.SA[i]);
}

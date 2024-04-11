#include <bits/stdc++.h>
 
using namespace std;
 
class Solution {
public:
    int get(int layer, vector <int> &nums, vector <vector <int> > &precompute, vector <vector <int> > &suff, vector <vector <int> > &pref, vector <vector <int> > &startIdx, vector <int> &lg, int l, int r, int ll, int rr, int init = 0) {
        if (ll >= rr) return nums[ll];
        if (ll + 1 >= rr) return nums[ll] | nums[rr];
        int b = lg[r - l];
        while ((ll - l) / b == (rr - l) / b) { //add binary search or use better indexation
            l += (ll - l) / b * b;
            if (r > l + b) r = l + b;
            b = lg[r - l];
            layer++;
        }
        int ans = init; //block[layer]
        ans |= pref[layer][ll];
        ans |= suff[layer][rr];
        int wl = (ll - l) / b + 1, wr = (rr - l) / b - 1;
        if (wl <= wr) {
            int where = startIdx[layer][l], m = (r - l) / b;
            int w = lg[wr - wl + 1];
            //accurately
            int idx = m * w - (w >= 2 ? ((1 << (w - 1)) - 1) : 0);
            //ans |= precompute[layer][where + idx + (rr / b - 1) - (ll / b + 1)];
            //ans |= precompute[layer][where + ll / b + 1]
            ans |= precompute[layer][where + idx + wl];
            //ans |= precompute[layer][where + rr / b - 1    - t]
            ans |= precompute[layer][where + idx + wr - (1 << w) + 1];
            //cout << ' ' << ans << '\n';
            //if ((rr - l) / b - 1 - (1 << w) + 1 < (ll - l) / b + 1) while (true);
        }
        return ans;
    }
    void build(vector <int> &nums, vector <vector <int> > &precompute, vector <vector <int> > &suff, vector <vector <int> > &pref, vector <vector <int> > &startIdx, vector <int> &lg, vector <int> &ptr, int layer, int l, int r, int init = 0) {
        if (l + 1 >= r) return;
        int b = lg[r - l];
        int m = (r - l) / b;
        startIdx[layer][l] = ptr[layer];
        ptr[layer] += m * b + 2;//
        //if (ptr[layer] >= precompute[layer].size()) cout << "FUCK\n";
        for (int it = l; it < r; it += b) {
            int ll = it, rr = min(r, it + b);
            //startIdx[layer][ll] = ptr[layer]++;
            for (int i = ll; i < rr; ++i) {
                suff[layer][i] = nums[i];
                if (i > ll) suff[layer][i] |= suff[layer][i - 1];
                //precompute[[(it - l) / b * (n / b)] |= nums[i];
            }
            for (int i = rr - 1; i >= ll; --i) {
                pref[layer][i] = nums[i];
                if (i + 1 < rr) pref[layer][i] |= pref[layer][i + 1];
            }
        }
        int where = startIdx[layer][l];
        //(n/b)*(n/b+1)/2 [x; y] -> x*(n/b)+y-x
        //[m] [m-1] [m-2] .. [m-2^x] [m-x] ..
        for (int w = 0; (1 << w) <= m; ++w) {
            for (int i = 0; i + (1 << w) - 1 < m; ++i) {
                int idx = m * w + i - (w >= 2 ? ((1 << (w - 1)) - 1) : 0);
                //if (idx > m * b + 1) while(true);
                precompute[layer][where + idx] = (w == 0 ? pref[layer][l + i * b] :
                    precompute[layer][where + m * (w - 1) - (w >= 2 ? ((1 << (w - 2)) - 1) : 0) + i] | 
                    precompute[layer][where + m * (w - 1) - (w >= 2 ? ((1 << (w - 2)) - 1) : 0) + i + (1 << (w - 1))]);
                //for (int j = i + 1; j < m; ++j) { //geniucos's suggested using sparse-table here but finding indices are tough
                //    precompute[layer][where + idx + j - i] = precompute[layer][where + idx + (j - i - 1)] | pref[layer][l + j * b];
                //}
            }
        }
        for (int i = 0; i < m; ++i) {
            if (min(r, l + (i + 1) * b) - (l + i * b) > 1) {
                build(nums, precompute, suff, pref, startIdx, lg, ptr, layer + 1, l + i * b, min(r, l + (i + 1) * b), init);
            }
        }
    }
    int minimumSubarrayLength(vector<int>& nums, int k) {
        const int D = 5, overhead = 3; //2^(2^D)
        int N = (int)nums.size();
        vector <vector <int> > precompute(D + 1, vector <int>(N *2 + overhead));
        vector <vector <int> > suff(D + 1, vector <int>(N + 1)), pref(D + 1, vector <int>(N + 1));
        vector <vector <int> > startIdx(D + 1, vector <int> (N));
        vector <int> lg(N + 1), ptr(D + 1, 0);
        for (int i = 1; i <= N; ++i) {
            lg[i] = lg[i - 1] + ((1 << (lg[i - 1] + 1)) <= i);
        }
        build(nums, precompute, suff, pref, startIdx, lg, ptr, 0, 0, N, 0);
        int ans = N + 1;
        for (int i = 0, j = -1; i < N; ++i) {
            if (j < i - 1) j = i - 1;
            for (; j + 1 < N && get(0, nums, precompute, suff, pref, startIdx, lg, 0, N, i, j + 1) < k; ++j);
            if (j + 1 < N && get(0, nums, precompute, suff, pref, startIdx, lg, 0, N, i, j + 1) >= k) ans = min(ans, j + 1 - i + 1);
        }
        return ans > N ? -1 : ans;
    }
} sol;
 
int main() {
	vector <int> tmp = {2, 1, 8};
	cout << sol.minimumSubarrayLength(tmp, 10) << '\n';
	return 0;
}

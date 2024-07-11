#include <stdio.h>
#include <stdlib.h>

/*
Time complexity analysis:
We scan each tollgate into the costs array: n tollgates -> O(n)
For each element, costliest possible operation is calculating the cost of the last c tollgates ('skip'), so O(c) (other operations are constant here)
Overall: O(n*c)
*/

long long min(long long a, long long b) {
	return a < b ? a : b;
}
 
int main(void) {
	long long h, c, n;
	scanf("%lld %lld\n", &h, &c);
	scanf("%lld\n", &n);
	long long len = h + c;
	long long costs[len]; // stores the costs of passing through tollgates
	long long dp[len]; // stores the optimal cost of paying/skipping through tollgates ending at each index up to n
	costs[0] = 0;
	dp[0] = 0;
	long long pay, skip, prevDp;
	for (long long i = 1; i < n + 1; i++) { 
		scanf("%lld\n", &costs[i % len]); // scan each tollgates' cost into the costs array (only keep last h+c)
		if (i < h) {
			dp[i % len] = costs[i % len] + dp[(i-1) % len]; // no option but to pay all for the first h-1 tollgates
		} else {
			// at this point we can choose either to pay or skip this tollgate
			pay = dp[(i - 1) % len] + costs[i % len]; // if we pay, the cost is the optimal cost (stored in dp) at the previous tollgate plus the cost of the current tollgate
			// if we skip, then we must have skipped the last h - 1 tollgates also (since current tollgate is last) and hence paid the c tollgates prior to that.
			skip = 0; // calculating cost of paying the c tollgates prior to skipping
			for (long long j = i - h - c + 1; j < i - h + 1; j++) {
				if (j > 0)
					skip += costs[j % len];
			}
			prevDp = (i - h - c > 0) ? dp[i % len] : 0; // any rule-following combination of paying/skipping possible before that, so we consult dp[i - h - c] to find optimal cost until then
			dp[i % len] = min(pay, prevDp + skip); // current optimal cost is min of both options (paying vs skipping current)
		}
	}
	printf("%lld\n", dp[n % len]); // optimal cost at last tollgate
}

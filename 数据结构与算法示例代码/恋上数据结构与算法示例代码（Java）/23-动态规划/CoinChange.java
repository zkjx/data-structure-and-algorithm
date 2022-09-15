package com.mj;

public class CoinChange {

	public static void main(String[] args) {
		System.out.println(coins5(41, new int[] {1, 5, 25, 20}));
		// fib(40)
		
		// dp(i) 第i项斐波那契数
		// dp(i) = dp(i - 1) + dp(i - 2)
		
		// dp(41) = 凑够41需要的最少硬币数量 = min { dp(40), dp(36), dp(16), dp(21) } + 1
		// dp(41 - 1) = dp(40) = 凑够40需要的最少硬币数量
		// dp(41 - 5) = dp(36) = 凑够36需要的最少硬币数量
		// dp(41 - 25) = dp(16) = 凑够16需要的最少硬币数量
		// dp(41 - 20) = dp(21) = 凑够21需要的最少硬币数量
		// min { dp(40), dp(36), dp(16), dp(21) } + 1
	}

	static int coins5(int n, int[] faces) {
		if (n < 1 || faces == null || faces.length == 0) return -1;
		int[] dp = new int[n + 1];
		for (int i = 1; i <= n; i++) {
			int min = Integer.MAX_VALUE;
			for (int face : faces) {
				if (i < face) continue;
				int v = dp[i - face];
				if (v < 0 || v >= min) continue;
				min = v;
			}
			if (min == Integer.MAX_VALUE) {
				dp[i] = -1;
			} else {
				dp[i] = min + 1;
			}
		}
		return dp[n];
	}

	static int coins4(int n) {
		if (n < 1) return -1;
		int[] dp = new int[n + 1];
		// faces[i]是凑够i分时最后那枚硬币的面值
		int[] faces = new int[dp.length];
		for (int i = 1; i <= n; i++) {
			int min = dp[i - 1];
			faces[i] = 1;

			if (i >= 5 && dp[i - 5] < min) {
				min = dp[i - 5];
				faces[i] = 5;
			}
			if (i >= 20 && dp[i - 20] < min) {
				min = dp[i - 20];
				faces[i] = 20;
			}
			if (i >= 25 && dp[i - 25] < min) {
				min = dp[i - 25];
				faces[i] = 25;
			}
			dp[i] = min + 1;
			print(faces, i);
		}
//		print(faces, n);
		return dp[n];
	}
	
	static void print(int[] faces, int n) {
		System.out.print("[" + n + "] = ");
		while (n > 0) {
			System.out.print(faces[n] + " ");
			n -= faces[n];
		}
		System.out.println();
	}
	
	/**
	 * 递推（自底向上）
	 */
	static int coins3(int n) {
		if (n < 1) return -1;
		int[] dp = new int[n + 1];
		for (int i = 1; i <= n; i++) {
			int min = dp[i - 1];
			if (i >= 5) min = Math.min(dp[i - 5], min);
			if (i >= 20) min = Math.min(dp[i - 20], min);
			if (i >= 25) min = Math.min(dp[i - 25], min);
			dp[i] = min + 1;
		}
		return dp[n];
	}
	
	/**
	 * 记忆化搜索（自顶向下的调用）
	 */
	static int coins2(int n) {
		if (n < 1) return -1;
		int[] dp = new int[n + 1];
		int[] faces = {1, 5, 20, 25};
		for (int face : faces) {
			if (n < face) break;
			dp[face] = 1;
		}
		return coins2(n, dp);
	}
	
	static int coins2(int n, int[] dp) {
		if (n < 1) return Integer.MAX_VALUE;
		if (dp[n] == 0) {
			int min1 = Math.min(coins2(n - 25, dp), coins2(n - 20, dp));
			int min2 = Math.min(coins2(n - 5, dp), coins2(n - 1, dp));
			dp[n] = Math.min(min1, min2) + 1;
		}
		return dp[n];
	}
	
	/**
	 * 暴力递归（自顶向下的调用，出现了重叠子问题）
	 */
	static int coins1(int n) {
		if (n < 1) return Integer.MAX_VALUE;
		if (n == 25 || n == 20 || n == 5 || n == 1) return 1;
		int min1 = Math.min(coins1(n - 25), coins1(n - 20));
		int min2 = Math.min(coins1(n - 5), coins1(n - 1));
		return Math.min(min1, min2) + 1;
	}
}

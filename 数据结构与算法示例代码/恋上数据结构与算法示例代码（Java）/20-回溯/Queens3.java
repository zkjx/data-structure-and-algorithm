package com.mj;

public class Queens3 {

	public static void main(String[] args) {
		// 01111101 n
		//&11111011  ~00000100
		// 01111001
		
		
		//&00100000 v
//		int n = 125;
//		for (int i = 0; i < 8; i++) {
//			int result = n & (1 << i);
//			System.out.println(i + "_" + (result != 0));
//		}
//		int col = 7;
//		int result = n & (1 << col);
//		System.out.println(result != 0);
		
//		System.out.println(Integer.toBinaryString(n));
		
		// TODO Auto-generated method stub
		new Queens3().place8Queens();
	}
	
	/**
	 * 数组索引是行号，数组元素是列号
	 */
	int[] queens;
	/**
	 * 标记着某一列是否有皇后
	 */
	byte cols;
	/**
	 * 标记着某一斜线上是否有皇后（左上角 -> 右下角）
	 */
	short leftTop;
	/**
	 * 标记着某一斜线上是否有皇后（右上角 -> 左下角）
	 */
	short rightTop;
	/**
	 * 一共有多少种摆法
	 */
	int ways;
	
	void place8Queens() {
		queens = new int[8];
		place(0);
		System.out.println("8皇后一共有" + ways + "种摆法");
	}
	
	/**
	 * 从第row行开始摆放皇后
	 * @param row
	 */
	void place(int row) {
		if (row == 8) {
			ways++;
			show();
			return;
		}
		
		for (int col = 0; col < 8; col++) {
			int cv = 1 << col;
			if ((cols & cv) != 0) continue;
			
			int lv = 1 << (row - col + 7);
			if ((leftTop & lv) != 0) continue;
			
			int rv = 1 << (row + col);
			if ((rightTop & rv) != 0) continue;
			
			queens[row] = col;
			cols |= cv;
			leftTop |= lv;
			rightTop |= rv;
			place(row + 1);
			cols &= ~cv;
			leftTop &= ~lv;
			rightTop &= ~rv;
		}
	}
	
	void show() {
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				if (queens[row] == col) {
					System.out.print("1 ");
				} else {
					System.out.print("0 ");
				}
			}
			System.out.println();
		}
		System.out.println("------------------------------");
	}
}

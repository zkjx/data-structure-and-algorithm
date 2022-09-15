package com.mj.sort.cmp;

import com.mj.sort.Sort;

public class BubbleSort3<T extends Comparable<T>> extends Sort<T> {

	@Override
	protected void sort() {
		for (int end = array.length - 1; end > 0; end--) {
			int sortedIndex = 1;
			for (int begin = 1; begin <= end; begin++) {
				// if (array[begin] < array[begin - 1]) {
				if (cmp(begin, begin - 1) < 0) {
					swap(begin, begin - 1);
					sortedIndex = begin;
				}
			}
			end = sortedIndex;
		}
	}

}

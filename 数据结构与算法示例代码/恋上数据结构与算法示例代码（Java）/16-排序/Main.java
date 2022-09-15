package com.mj;

import java.util.Arrays;

import com.mj.sort.CountingSort;
import com.mj.sort.RadixSort;
import com.mj.sort.Sort;
import com.mj.sort.cmp.BubbleSort3;
import com.mj.sort.cmp.HeapSort;
import com.mj.sort.cmp.InsertionSort3;
import com.mj.sort.cmp.MergeSort;
import com.mj.sort.cmp.QuickSort;
import com.mj.sort.cmp.SelectionSort;
import com.mj.sort.cmp.ShellSort;
import com.mj.tools.Asserts;
import com.mj.tools.Integers;

@SuppressWarnings({"rawtypes", "unchecked", "unused"})
public class Main {

	public static void main(String[] args) {
		Integer[] array = {7, 3, 5, 8, 6, 7, 4, 5};
		
		testSorts(array, 
//				new RadixSort()
//				new InsertionSort1(),
//				new InsertionSort2(),
				new InsertionSort3(),
				new SelectionSort(), 
				new HeapSort(), 
				new MergeSort(),
				new BubbleSort3(),
				new QuickSort(),
				new ShellSort()
				);
	}
	
	static void testSorts(Integer[] array, Sort... sorts) {
		for (Sort sort : sorts) {
			Integer[] newArray = Integers.copy(array);
			sort.sort(newArray);
			Asserts.test(Integers.isAscOrder(newArray));
		}
		Arrays.sort(sorts);
		
		for (Sort sort : sorts) {
			System.out.println(sort);
		}
	}
	
//	static void selectionSort(Integer[] array) {
//		for (int end = array.length - 1; end > 0; end--) {
//			int maxIndex = 0;
//			for (int begin = 1; begin <= end; begin++) {
//				if (array[maxIndex] <= array[begin]) {
//					maxIndex = begin;
//				}
//			}
//			int tmp = array[maxIndex];
//			array[maxIndex] = array[end];
//			array[end] = tmp;
//		}
//		
//		// 8 10 9 10 
//	}
//	
//	static void bubbleSort1(Integer[] array) {
//		for (int end = array.length - 1; end > 0; end--) {
//			for (int begin = 1; begin <= end; begin++) {
//				if (array[begin] < array[begin - 1]) {
//					int tmp = array[begin];
//					array[begin] = array[begin - 1];
//					array[begin - 1] = tmp;
//				}
//			}
//		}
//	}
//	
//	static void bubbleSort2(Integer[] array) {
//		for (int end = array.length - 1; end > 0; end--) {
//			boolean sorted = true;
//			for (int begin = 1; begin <= end; begin++) {
//				if (array[begin] < array[begin - 1]) {
//					int tmp = array[begin];
//					array[begin] = array[begin - 1];
//					array[begin - 1] = tmp;
//					sorted = false;
//				}
//			}
//			if (sorted) break;
//		}
//	}
//
//	static void bubbleSort3(Integer[] array) {
//		for (int end = array.length - 1; end > 0; end--) {
//			// sortedIndex的初始值在数组完全有序的时候有用
//			int sortedIndex = 1;
//			for (int begin = 1; begin <= end; begin++) {
//				if (array[begin] < array[begin - 1]) {
//					int tmp = array[begin];
//					array[begin] = array[begin - 1];
//					array[begin - 1] = tmp;
//					sortedIndex = begin;
//				}
//			}
//			end = sortedIndex;
//		}
//	}
}

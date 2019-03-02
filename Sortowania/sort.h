#ifndef SORT_H
#define SORT_H

#include <cstdlib>

void BubbleSort( int* pTab, int nSize );
void SelectSort( int* pTab, int nSize );
void InsertionSort( int* pTab, int nSize );
void MixedBubbleSort( int* pTab, int nSize );
void HalfInsertionSort( int* pTab, int nSize );
void HeapSort( int* pTab, int nSize );
void MergeSort( int* pTab, int* pTemp, int nSize, int l, int p );
void QuickSort( int* pTab, int nSize );
void NaturalSort( int* pTab, int nSize );
//void QuickSort( int*pTab, int nSize, int l, int p );




#endif
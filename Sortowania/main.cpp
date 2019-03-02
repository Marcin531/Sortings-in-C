
//Celem dzialania programu jest posortowanie tablicy na rozne sposoby i pomiar czasu sortowania
//The purpose of this program is to sort arrays in diffrent ways and to measure the time of sorting

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <memory.h>
#include "sort.h"

//#define MAXSTACK 10000
#define PRINT 100
//#define _DEBUG_

void InitTab( int** pTab, int nSize );
void PrintTab( int* pTab, int nSize );
void CopyTab( int** source, int** destination, int nSize );
int CreateTab( int** pTab, int nSize );


typedef void( *pFunction )(int*, int);


int main( int argc, char* argv[] )
{

	pFunction pFSort[] = { BubbleSort, InsertionSort,SelectSort, MixedBubbleSort,HalfInsertionSort,HeapSort,QuickSort };
	const char* sortName[] = { "BubbleSort", "InsertionSort", "SelectSort", "MixedBubbleSort", "HalfInsertionSort", "HeapSort", "QuickSort", "MergeSort","NaturalSort" };
	
	clock_t cTime;			  

	if( argc != 2 )
	{
		printf( "Nalezy podac nazwe programu i ilosc elementow do posortowania" );
	}
	int nSize = atoi( argv[1] );//podawanie rozmiaru z wiersza polecenien
	

	//int nSize;

	//printf( "Podaj rozmiar tablicy: " );
	//scanf( "%d", &nSize );
	
	if( nSize < 0 )
	{
		perror( "BAD ARRAY SIZE" );
	}

#define MAXSTACK nSize

//!!!!
	int* pTab = NULL;
	if( !CreateTab( &pTab, MAXSTACK ) )
	{
		perror( "Nie udalo sie utworzyc macierzy" );
	}

	InitTab( &pTab, MAXSTACK );

#ifdef _DEBUG_
	printf( "ORYGINAL: \n" );
	PrintTab( pTab, PRINT );
#endif
	
	int* pTabCpy = NULL;

	if( !CreateTab( &pTabCpy, MAXSTACK ) )
	{
		perror( "Nie udalo sie utworzyc macierzy pTabCpy" );
	}


	int amountOfSortFunction = sizeof( pFSort ) / sizeof( pFunction );//wyliczenie rozmiaru tabicy pFunction
	int i;

	for( i = 0; i < amountOfSortFunction; i++ )
	{
		CopyTab( &pTab, &pTabCpy, MAXSTACK );
		cTime = clock();	//rozpoczecie odliczania czasu
		(pFSort[i](pTabCpy, MAXSTACK));
		printf( "%s : %.0f ms\n", sortName[i], (double)((clock() - cTime)) );

#ifdef _DEBUG_		
		PrintTab( pTabCpy, PRINT );
#endif
	}
	//MERGESORT


	
	int* pTempTab = NULL;//tablica pomocnicza dla MergeSorta
	int left = 0;	// indeks pierwszego wyrazu w tablicy
	int right = MAXSTACK - 1;//indeks ostatniego wyrazu w tablicy  

	if( !CreateTab( &pTempTab, MAXSTACK ) )
	{
		perror( "Nie udalo sie utworzyc macierzy pTempTab" );
	}	
	
	CopyTab( &pTab, &pTabCpy, MAXSTACK );
	CopyTab( &pTab, &pTempTab, MAXSTACK );

	cTime = clock();
	MergeSort( pTabCpy, pTempTab, MAXSTACK, left, right );
	printf( "%s : %.0f ms\n", sortName[i], (double)((clock() - cTime)) );

	CopyTab( &pTab, &pTabCpy, MAXSTACK );
	cTime = clock();
	NaturalSort( pTabCpy, MAXSTACK);
	printf( "%s : %.0f ms\n", sortName[i+1], ( double ) ( ( clock() - cTime ) ) );

#ifdef _DEBUG_		
	PrintTab( pTabCpy, PRINT );
#endif

	free( pTempTab );
	free( pTab );
	free( pTabCpy );
	return 0;
}

int CreateTab( int** pTab, int nSize )
{
	*pTab = (int*)malloc( sizeof( int )*nSize );

	if( !(*pTab) )
	{
		perror( "ERROR-BAD MEMORY ALLOCATION!!!" );
		return 0;
	}
	memset( *pTab, 0, sizeof( int )*nSize );
	return 1;
}


void InitTab( int** pTab, int nSize )
{
	srand( time( NULL ) );
	for( int i = 0; i < nSize; i++ )
		*(*pTab+i) = rand() % MAXSTACK;
}

void PrintTab( int* pTab, int nSize )
{
	if( !pTab ) printf( "Tablica jest pusta\n" );
	else
	{
		for( int i = 0; i < nSize; i++ )
		{
			printf( "%d\t ", *pTab++ );
			if( !((i + 1) % 10) )printf( "\n" );
		}
	}
}

void CopyTab( int** source, int** destination, int nSize )
{
	memcpy( *destination, *source, sizeof( int )*nSize );
}



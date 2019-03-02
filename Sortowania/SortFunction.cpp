#include "sort.h"




void Przesianie( int* pTab, int l, int p );
void Sort( int*pTab, int l, int p );
void CopySerie( int* t, int* i, int* tmp, int* j, int nLast );
bool copy( int* t, int* i, int* tmp, int* j, int nLast );

void BubbleSort( int* pTab, int nSize )
{
	int temp;
	for( int i = 0; i < nSize; i++ )
	{
		for( int j = nSize - 1; j > i; j-- )
		{
			if( pTab[j - 1] > pTab[j] )
			{
				temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
			}
		}
	}
}

void InsertionSort( int* pTab, int nSize )
{
	int temp;
	int j;
	for( int i = 0; i < nSize; i++ )
	{
		temp = pTab[i];
		j = i - 1;
		while( temp < pTab[j] )
		{
			pTab[j + 1] = pTab[j--];
		}
		pTab[j + 1] = temp;
	}
}

void SelectSort( int* pTab, int nSize )
{
	int temp;
	int min;
	for( int i = 0; i < nSize - 1; i++ )
	{
		min = pTab[i];
		temp = i;
		for( int j = i + 1; j < nSize; j++ )
		{
			if( pTab[j] < min )
			{
				min = pTab[j];
				temp = j;
			}
		}

		pTab[temp] = pTab[i];
		pTab[i] = min;
	}


}

void MixedBubbleSort( int* pTab, int nSize )//b¹belkowe mieszane
{
	int temp;
	int l = 1;
	int k = nSize - 1;
	int p = nSize - 1;


	do
	{
		for( int j = p; j >= l; j-- )
		{
			if( pTab[j - 1] > pTab[j] )
			{
				temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}
		}
		l = k + 1;
		for( int j = l; j <= p; j++ )
		{
			if( pTab[j - 1] > pTab[j] )
			{
				temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}
		}

		p = k - 1;
	} while( l <= p );

}

void HalfInsertionSort( int* pTab, int nSize )
{
	int temp, l, p, m;
	for( int i = 1; i < nSize; i++ )
	{
		temp = pTab[i];
		l = 0;
		p = i - 1;
		while( l <= p )
		{
			m = (l + p) / 2;
			if( temp < pTab[m] )
				p = m - 1;
			else
				l = m + 1;
		}
		for( int j = i - 1; j >= l; j-- )
			pTab[j + 1] = pTab[j];
		pTab[l] = temp;
	}
}




void HeapSort( int* pTab, int nSize )
{
	int l = 0;
	int p = nSize - 1;
	int temp;

//	Przesianie( pTab, l, p );										 

	for( l = nSize / 2 ; l >= 0; l-- )
		Przesianie( pTab, l, p );

	for( p = nSize-1; p > 0; p-- )
	{
		temp = pTab[p];
		pTab[p] = pTab[0];
		pTab[0] = temp;
		Przesianie( pTab, 0, p-1 );
	}


}

void Przesianie( int* pTab, int l, int p )
{
	if( l == p ) return;
	int i = l;
	int j = 2 * i+1;
	int temp = pTab[i];
	while( j <= p )
	{
		if( j < p )
			if( pTab[j] < pTab[j + 1] ) j++;

		if( temp >= pTab[j] ) break;
		pTab[i] = pTab[j];
		i = j;
		j = 2 * i+1;
	}
	pTab[i] = temp;

}

void MergeSort( int* pTab, int* pTemp, int nSize, int l, int p )
{
	int middle = (l + p + 1) / 2;
	int i1, i2;


	if( middle - l > 1 ) MergeSort( pTab, pTemp, nSize, l, middle - 1 );
	if( p - middle > 0 ) MergeSort( pTab, pTemp, nSize, middle, p );
	i1 = l;
	i2 = middle;
	for( int i = l; i <= p; i++ )
		pTemp[i] = ((i1 == middle) || ((i2 <= p) && (pTab[i1] > pTab[i2]))) ? pTab[i2++] : pTab[i1++];
	for( int i = l; i <= p; i++ )
		pTab[i] = pTemp[i];
}


void QuickSort( int* pTab, int nSize )
{
	Sort( pTab, 0, nSize - 1 );
}

void Sort( int*pTab, int l, int p )
{
	int i = l;
	int j = p;
	int temp = pTab[(l + p) / 2];
	int stemp;
	do
	{
		while( pTab[i] < temp ) i++;
		while( temp < pTab[j] ) j--;
		if( i <= j )
		{
			stemp = pTab[i];
			pTab[i] = pTab[j];
			pTab[j] = stemp;
			i++;
			j--;
		}
	} while( i <= j );
	if( l < j ) Sort( pTab, l, j );
	if( i < p ) Sort( pTab, i, p );

}

void NaturalSort( int* t, int nSize )
{
	int k = 0; // indeks tab numer 2
	int j = 0; // indeks tab numer 1
	int i = 0; // indeks tablicy glownej
	int series = 0; // Jedna seria bedzie oznaczac, ze tablica jest w calosci posortowana.

	int* tmp1 = ( int* ) malloc( nSize * sizeof( int ) );
	int* tmp2 = ( int* ) malloc( nSize * sizeof( int ) );

	do
	{

		j = 0; // Ustawiam indeksy tablic na pierwsze ich elementy.
		k = 0;
		i = 0;

		// Faza rozdzielania.
		while( i < nSize ) // Rozdzielanie zakonczy sie, kiedy indeks i osiagnie wartosc nSize - 1.
		{
			while( i < nSize - 1 && t[i] <= t[i + 1] ) // Dopoki elementy sa posortowane, kopiuj je z tablicy glownej do tab numer 1.
				tmp1[j++] = t[i++];
			tmp1[j++] = t[i++]; // Dokopiowanie jednego elementu          1 3 7' 3 ...           1 < 3; 3 < 7; [[7]] < 3       

			while( i < nSize - 1 && t[i] <= t[i + 1] ) // Kopiowanie do t numer 2.
				tmp2[k++] = t[i++];

			if( i < nSize )
				tmp2[k++] = t[i++];
		}


		int t1_len = j; // Dlugosc tab pom 1.
		int t2_len = k; // Dlugosc tab pom 2.

		series = 0;  // Dla kazdego laczenia liczba serii bedzie inna, wiec trzeba ja wyzerowac. Zeruje indeksy wszystkich tablic.
		j = 0;
		k = 0;
		i = 0;

		// Przenoszenie elementow z tab pomocniczych do tablicy glownej.
		while( ( j < t1_len ) && ( k < t2_len ) ) // Dopoki nie zostanie osiagniety koniec tasmy pomocniczej.
		{
			bool seriesEnd = false;
			while( !seriesEnd )
			{
				if( tmp1[j] <= tmp2[k] ) // Porownywanie elementow serii w dwoch tasmach.          1 4 7' 3 9 11' 5 8 10' 4 5 6'
				{
					seriesEnd = copy( t, &i, tmp1, &j, t1_len ); // Kopiuj dopoki nie skonczy sie seria.
					if( seriesEnd )
						CopySerie( t, &i, tmp2, &k, t2_len ); // Kiedy skonczyla sie seria, dopisz pozostale elementy drugiej serii
				}
				else
				{
					seriesEnd = copy( t, &i, tmp2, &k, t2_len );
					if( seriesEnd )
						CopySerie( t, &i, tmp1, &j, t1_len );
				}
			}
			series++; // Zwieksza liczbe serii za kazdym razem, kiedy porownane sa dwie serie.
		}

		while( j < t1_len ) // W przypadku, gdy jedna z tasm osiagnela swoj koniec, nalezy przekopiowac pozostale serie w tasmie drugiej. 
		{				   // Jesli serie sie polacza, to moze zostac wiecej niz jedna seria w tasmie 2.
			CopySerie( t, &i, tmp1, &j, t2_len );
			series++;
		}
		while( k < t2_len )
		{
			CopySerie( t, &i, tmp2, &k, t2_len );
			series++;
		}



	} while( series != 1 ); // Seria == 1 oznacza, ze tablica jest posortowana.	
	free( tmp1 );
	free( tmp2 );
}

void CopySerie( int* t, int* i, int* tmp, int* j, int nLast )
{
	bool end = false; // Seria bedzie zawierac przynajmniej jeden element. 
	do
	{
		end = copy( t, i, tmp, j, nLast );
	} while( !end );
}

bool copy( int* t, int* i, int* tmp, int* j, int nLast )
{
	t[( *i )++] = tmp[( *j )++];
	if( *j == nLast )
		return true;
	return tmp[*j - 1] > tmp[*j]; // Patrzenie w przod.   
}
/*void QuickSort( int*pTab, int nSize, int l, int p )
{						   
	int i = l;
	int j = p;
	int temp = pTab[(l + p) / 2];
	int stemp;
	do
	{
		while( pTab[i] < temp ) i++;
		while( temp < pTab[j] ) j--;
		if( i <= j )
		{
			stemp = pTab[i];
			pTab[i] = pTab[j];
			pTab[j] = stemp;
			i++;
			j--;
		}
	} while( i <= j );
	if( l < j ) QuickSort( pTab, nSize,l, j );
	if( i < p ) QuickSort( pTab,nSize, i, p );

}

*/



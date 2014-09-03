void insertion_sort( int* array, int size )
{
  int i = 0;
  for(; i < size; ++i )
  {
    for( int j = 0; j < i; ++j )
    {
      if( array[j] > array[i] )
      {
        int target = array[i];
        for( int k = i; k > j; --k )
        {
          array[k] = array[k-1];
        }
        array[j] = target;
        break;
      }
    }
  }
}


#include <cstdio>
int main()
{
  int a[10] ={1,30,2,15,24,66,18,7,9,0};
  for( int i = 0; i < 10; ++i )
  {
    printf("%d ", a[i]);
  }
  printf("\n");
  insertion_sort( a, 10 );
  for( int i = 0; i < 10; ++i )
  {
    printf("%d ", a[i]);
  }
  printf("\n");
  return 0;
}

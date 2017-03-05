#include "answer01.h"
#include "stdio.h"
/* Return the largest partial sum of the array */
/* int array[] = { 1, 4, -1, 6, -5, 4} */
/* the (i,j)-th partial sum is the sum from array[i] through array[j], i<=j */
/* the (0,0)-(0,5)-th partial sums are 1, 5, 4, 10, 5, 9 */
/* the (1,1)-(1,5)-th partial sums are 4, 3, 9, 4, 8 */
/* the (2,2)-(2,5)-th partial sums are -1, 5, 0, 4 */
/* the (3,3)-(3,5)-th partial sums are 6, 1, 5 */
/* the (4,4)-(4,5)-th partial sums are -5, -1 */
/* the (5,5)-th partial sum is 4 */
/* the largest partial sum of the array is therefore 10 */
/* if the len is 0, the largest partial sum is 0 */
/* you may assume that array is NULL when len is 0 */
/* but is non-NULL and correct when len is > 0 */
/* you may also assume that none of the partial sums will cause an overflow */

int largest_partial_sum(int * array, int len)
{
   int index;
   int index2;
   int Sum =0;
   int largest = array[0];
   if (len == 0)
   {
     return 0;
   }
   for(index = 0; index < len; index++)
   {
     Sum = 0;
     for(index2 = index; index2 < len; index2++)

   	   if (largest < (array[index2] + Sum))
	   {
          largest = array[index2]+Sum;
	   }
       Sum = array[index2] + Sum;
     }
   }
   return largest;
}

/* Return the largest difference of the array */
/* int array[] = { 1, 4, -1, 6, -5, 4} */
/* the largest difference is 6 - (-5) = 11 */
/* if the len is 0, the largest difference is 0 */
/* if the len is 1, the largest difference is also 0 */
/* you may assume that array is NULL when len is 0 */
/* but is non-NULL and correct when len is > 0 */
/* you may assume that the largest difference will not cause an overflow */

int largest_difference(int * array, int len)
{
   int index;
   int largest = array[0];
   int Diff;
   int Smallest = array[0];
   if (len == (0 | 1))
   { 
     return 0;
   }
   for(index = 1 ; index < len; index++)
   { 
     if (largest < array[index])
	 {
	   largest = array[index];
	 }
     if (Smallest > array[index]) 
     {
	   Smallest = array[index];
	 }
   }
  Diff = largest - Smallest;
 return Diff;
}

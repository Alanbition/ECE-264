#include "answer02.h"
#include "pe02_aux.h"
// the function performs numerical integration of the function
// double function_to_be_integrated(double) over the 
// range lower_limit to upper_limit using the mid-point rule
//
// The range is divided into n_intervals uniform intervals, where the
// left-most interval has a left boundary of lower_limit and the 
// right-most interval has a right boundary of upper_limit (assuming 
// lower_limit <= upper_limit).  
// If lower_limit >= upper_limit, the right-most interval has a right 
// boundary of lower_limit and the left-most interval has a left boundary
// of upper_limit.
// 
// The mid-point rule is used to perform the integration for each interval.
// In the mid-point rule, the integration is approximated by using the
// area of a rectangle, where the height of the rectange is obtained by
// function_to_be_integrated(mid-point of the interval).  The width of
// the rectangle is (interval boundary closer to upper_limit - interval
// boundary closer to lower_limit).  Note that width could be negative
// if upper_limit < lower_limit
//
// The integral is the sum of the integration over all intervals
//
// The caller function has to make sure that n_intervals >= 1
// Therefore, this function may assume that n_intervals >= 1
//
double mid_point_numerical_integration(double lower_limit, double upper_limit, int n_intervals)
{
   double integral = 0.0;
   double a = lower_limit;
   double b = upper_limit;
   double a_b = (b-a)/n_intervals;
   double index;
   if (b < a)
   {
   	for ( index = a + a_b/2; index > b; index = index + a_b)
   {
    	integral = integral + a_b * function_to_be_integrated(index); 
   }
   }
   else
   {
	for ( index = a + a_b/2; index < b; index = index + a_b)
   {
    	integral = integral + a_b * function_to_be_integrated(index); 
   }
   }
   return integral;
}

// the function performs numerical integration of the function
// double function_to_be_integrated(double) over the 
// range lower_limit to upper_limit using the trapezoidal rule
//
// The range is divided into n_intervals uniform intervals, where the
// left-most interval has a left boundary of lower_limit and the 
// right-most interval has a right boundary of upper_limit (assuming 
// lower_limit <= upper_limit).  
// If lower_limit >= upper_limit, the right-most interval has a right 
// boundary of lower_limit and the left-most interval has a left boundary
// of upper_limit.
// 
// The trapezoidal rule is used to perform the integration for each interval.
// In the trapezoidal rule, the integration is approximated by the area of 
// a trapezoid, where the heights of the parallel boundaries of the trapezoid
// are obtained by 
// function_to_be_integrated(left boundary of the interval) and 
// function_to_be_integrated(right boundary of the interval).  
// The width of the trapezoid is (interval boundary closer to upper_limit - 
// interval boundary closer to lower_limit).  Note that width could be negative
// if upper_limit < lower_limit
// the area of a trapezoid is the average of the two heights multiplied by
// the width
//
// The integral is the sum of the integration over all intervals
//
// The caller function has to make sure that n_intervals >= 1
// Therefore, this function may assume that n_intervals >= 1
//
double trapezoidal_numerical_integration(double lower_limit, double upper_limit, int n_intervals)
{
   double integral = 0.0;
   double a = lower_limit;
   double b = upper_limit;
   int n = n_intervals;
   double a_b = (b-a)/n;
   if (b < a)
   {
     for (double index = a; index > b ; index = index + a_b)
   {
      integral = integral + (function_to_be_integrated(index) + function_to_be_integrated(index + a_b)) * a_b / 2;

 
   }
   }
   else
   {
   for (double index = a; index < b ; index = index + a_b)
   {
      integral = integral + (function_to_be_integrated(index) + function_to_be_integrated(index + a_b)) * a_b / 2;

	}


}
   return integral;
}

#include <math.h>
// do not change this part, if you do, your code may not compile
//
/* test for structure defined by student */
#ifndef NTEST_STRUCT 
#include "answer01.h"
#else 
#include "answer01_key.h"
#endif /* NTEST_STRUCT */
//
// do not change above this line, if you do, your code may not compile

// IF YOU HAVE TO declare and define more functions, do so between this line

// and this line

#ifndef NTEST_SIMPSON
// Given intg_arg, this function performs numerical integration of 
// the function intg_arg.func_to_be_integrated over the range
// intg_arg.lower_lilmit to intg_arg.upper_limit
// 
// The range is divided into intg_arg.n_intervals uniform intervals, where the
// left-most interval has a left boundary of intg_arg.lower_limit and the 
// right-most interval has a right boundary of intg_arg.upper_limit (assuming 
// intg_arg.lower_limit <= intg_arg.upper_limit).  
// If intg_arg.lower_limit >= intg_arg.upper_limit, the right-most interval 
// has a right boundary of intg_arg.lower_limit and the left-most interval has 
// a left boundary of intg_arg.upper_limit.
// 
// The Simpson's rule is used to perform the integration for each interval
// In the Simpson's rule, three points are used to approximate the 
// intg_arg.func_to_be_integrated.  The three points are:
// (left boundary, intg_arg.func_to_be_integrated(left boundary)), 
// (right boundary, intg_arg.func_to_be_integrated(right boundary)),
// (mid-point, intg_arg.function_to_be_integrated(mid-point)).  
// mid-point is the middle of the left and right boundary.
// A quadratic equation that passes through these three points is used
// to approximate the intg_arg.func_to_be_integrated
// The integration of the quadratic equation yields
// (width of interval)/6 * (f(left) + 4*f(mid-point) + f(right))
// Here, f is short for intg_arg.func_to_be_integrated
// The width of the interval is (interval boundary closer to 
// intg_arg.upper_limit - interval boundary closer to intg_arg.lower_limit).  
// Note that width could be negative if intg_arg.upper_limit < 
// intg_arg.lower_limit
//
// The integral is the sum of the integration over all intervals
//
// The caller function has to make sure that intg_arg.n_intervals >= 1
// Therefore, this function may assume that intg_arg.n_intervals >= 1
//
double simpson_numerical_integration(integrand intg_arg)
{
   double integral = 0.0;
   double div_n = (intg_arg.upper_limit - intg_arg.lower_limit)/ intg_arg.n_intervals; 
   double index1;

  if ( div_n < 0)
  {
    for ( index1 = intg_arg.lower_limit; index1 > (intg_arg.upper_limit );index1 += div_n)
   {
     integral += div_n / 6 * (intg_arg.func_to_be_integrated(index1) + 4* intg_arg.func_to_be_integrated(index1 + div_n/2) + intg_arg.func_to_be_integrated(index1 + div_n))   ;
   }

  }
  else
  {
   for ( index1 = intg_arg.lower_limit; index1 < (intg_arg.upper_limit );index1 += div_n)
   {
     integral += div_n / 6 * (intg_arg.func_to_be_integrated(index1) + 4* intg_arg.func_to_be_integrated(index1 + div_n/2) + intg_arg.func_to_be_integrated(index1 + div_n))   ;
   }
  } 
   return integral;
}
// do not change this
#endif /* NTEST_SIMPSON */

#ifndef NTEST_FSIMPSON
// Given intg_arg, this function performs numerical integration over the
// range of intg_arg.lower_limit to intg_arg.upper_limit of f(x):
// 
// f(x) = intg_arg.func_to_be_integrated(x) * cos_sin((n * M_PI * x)/L), 
//
// where 2L = intg_arg.upper_limit - intg_arg.lower_limit = period 
// 
// The range is divided into intg_arg.n_intervals uniform intervals, where the
// left-most interval has a left boundary of intg_arg.lower_limit and the 
// right-most interval has a right boundary of intg_arg.upper_limit (assuming 
// intg_arg.lower_limit <= intg_arg.upper_limit).  
// If intg_arg.lower_limit >= intg_arg.upper_limit, the right-most interval 
// has a right boundary of intg_arg.lower_limit and the left-most interval has 
// a left boundary of intg_arg.upper_limit.
// 
// The Simpson's rule is used to perform the integration for each interval
// In the Simpson's rule, three points are used to approximate f(x). 
// The three points are: (left boundary, f(left boundary)),
// (right boundary, f(right boundary)),
// (mid-point, f(mid-point)).  
// mid-point is the middle of the left and right boundary.
// A quadratic equation that passes through these three points is used
// to approximate the intg_arg.func_to_be_integrated
// The integration of the quadratic equation yields
// (width of interval)/6 * (f(left) + 4*f(mid-point) + f(right))
// The width of the interval is (interval boundary closer to 
// intg_arg.upper_limit - interval boundary closer to intg_arg.lower_limit).  
// Note that width could be negative if intg_arg.upper_limit < 
// intg_arg.lower_limit
//
// The integral is the sum of the integration over all intervals
//
// The caller function has to make sure that intg_arg.n_intervals >= 1
// Therefore, this function may assume that intg_arg.n_intervals >= 1
//
// The caller function should also pass in n >= 0
//
// The caller function should also pass in cos or sin for the function 
// cos_sin.
//
double simpson_numerical_integration_for_fourier(integrand intg_arg, int n, double (*cos_sin)(double))
{
 
   double integral = 0.0;
   double div_n = (intg_arg.upper_limit - intg_arg.lower_limit)/ intg_arg.n_intervals; 
   double index;
   double L = (intg_arg.upper_limit - intg_arg.lower_limit)/ 2;
   if ( L < 0)
   {
    L = -1 * L ;
   }


  if ( div_n < 0)
  {
    for ( index = intg_arg.lower_limit; index > (intg_arg.upper_limit );index += div_n)
   {
     integral += div_n / 6 * (intg_arg.func_to_be_integrated(index) * cos_sin((n * M_PI * index)/L)+ 4* intg_arg.func_to_be_integrated(index + div_n/2) * cos_sin((n * M_PI * (index + div_n/2))/L)+ intg_arg.func_to_be_integrated(index + div_n) * cos_sin((n * M_PI * (index + div_n))/L))   ;
   }

  }
  else
  {
   for ( index = intg_arg.lower_limit; index < (intg_arg.upper_limit );index += div_n)
    {
     integral += div_n / 6 * (intg_arg.func_to_be_integrated(index) * cos_sin((n * M_PI * index)/L)+ 4* intg_arg.func_to_be_integrated(index + div_n/2) * cos_sin((n * M_PI * (index + div_n/2))/L)+ intg_arg.func_to_be_integrated(index + div_n) * cos_sin((n * M_PI * (index + div_n))/L))   ;
   }

} 
   return integral;
}

#endif /* NTEST_FSIMPSON */

#ifndef NTEST_FOURIER
// Given fourier_arg, this function computes the first fourier_arg.n_terms 
// Fourier coefficients a_0, a_1, ..., a_{fourier_arg.n_terms-1} and stores
// them as fourier_arg.a_i[0], fourier_arg.a_i[1], and so on, and 
// b_1, ..., b_{fourier_arg.n_terms-1} and stores them as fourier_arg.b_i[1],
// fourier_arg.b_i[2], and so on.
//
// The period is defined to be 
//    fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit
// 
// The function simpson_numerical_integration is used in the process of 
// computing a_0.  fourier_arg.intg should be passed to the function.
//  
// The function simpson_numerical_integration_for_fourier is used in the 
// process of computing a_1, ... and b_1, ...
// fourier_arg.intg should be passed, appropriate n >= 0, and either sin or
// cos function should also be passed.
//
// The caller function should pass into this function fourier_arg.n_terms >= 1
//
// The caller function should also allocate space to store the coefficients
// a_0, a_1, ..., b_1, ...
// 
// The caller function should ensure that the period is not 0.
//
void fourier_coefficients(fourier fourier_arg) 
{
   int i;
   double L = (fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit)/2;
   if (L < 0)
   {
    L = -1 * L;
   }
   fourier_arg.a_i[0] = (1/L) * simpson_numerical_integration(fourier_arg.intg);
   for (i = 1; i < fourier_arg.n_terms; i++) {
      fourier_arg.a_i[i] = 0.0;
      fourier_arg.b_i[i] = 0.0;
	   fourier_arg.a_i[i] = (1/L) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i,cos);
	   fourier_arg.b_i[i] = (1/L) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i,sin);
	   
   }
}
#endif /* NTEST_FOURIER */

// IF YOU HAVE TO define more functions, do so after this line

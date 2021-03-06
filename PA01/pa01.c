#include <stdio.h>
#include <stdlib.h>
#include "pa01_aux.h"
#include "pa01_util.h"
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

int main(int argc, char * * argv)
{
   // check for correct number of arguments.  If not, exit and return 
   // exit_failure

   // now, try to parse the arguments and call the correct function
      
   // fill in the correct statements to complete the main function
   // we expect five arguments:
   //
   // the first argument is 1 character from the sets {"1", "2", "3"}
   // it specifies the unknown function for which we are computing
   // the associated Fourier series
   // 1:  unknown_function_1
   // 2:  unknown_function_2
   // 3:  unknown_function_3
   // otherwise: return EXIT_FAILURE
    
   // to compute the Fourier series, specify the range over which we 
   // want to perform the integration, the next two arguments
   // should specify the lower limit (double) and upper limit (double)
   // of the range
   //
   // if lower limit == upper limit, return EXIT_FAILURE

   // the next argument specifies the number of intervals (int) to be used
   // for integration
   //
   // if the number of intervals is less than 1, set it to 1

   // the function, the lower and upper limits, and the number of intervals
   // should be stored in the fields of fourier_arg.intg

   // the next argument specifies the number of Fourier coefficients to
   // be computed.
   //
   // if the number of coefficients is less than 1, set it to 1

   // use atof to convert an argument to a double 
   // use atoi to convert an argument to an int

   // fill in statements to initialize all fields of fourier_arg (declared
   // below), except for fourier_arg.a_i and fourier_arg.b_i, based on
   // the comments specified above.  Exit and return EXIT_FAILURE if 
   // necessary.

   fourier fourier_arg;

   fourier_arg.n_terms = 1; // this line should be replaced.

//   double integral = 0.0;
   if ( argc != 6)
   {
     return EXIT_FAILURE;
   }
   fourier_arg.intg.lower_limit = atof(argv[2]);
   fourier_arg.intg.upper_limit = atof(argv[3]);
   fourier_arg.intg.n_intervals = atoi(argv[4]);
   fourier_arg.n_terms = atoi(argv[5]);
   if (fourier_arg.intg.n_intervals < 1)
   { 
     fourier_arg.intg.n_intervals = 1;
   }


   if (fourier_arg.n_terms < 1)
   { 
     fourier_arg.n_terms = 1;
   }
   
  if ((argv[1][0] != '1') &&  (argv[1][0] != '2') && (argv[1][0] != '3'))
   {

     return EXIT_FAILURE;
   }
   if (argv[1][1] != '\0')
   {
     return EXIT_FAILURE;
   }
   if (argv[1][0] == '1')
   {
     fourier_arg.intg.func_to_be_integrated = unknown_function_1;
   }
   if (argv[1][0] == '2')
   {
     fourier_arg.intg.func_to_be_integrated = unknown_function_2;
   }
   if (argv[1][0] == '3')
   {
     fourier_arg.intg.func_to_be_integrated = unknown_function_3;
   }

   
  
//    integral = simpson_numerical_integration(fourier_arg.intg);

    

   // after you have initialized all other fields of fourier_arg,
   // i.e., all fields in fourier_arg.intg and fourier_arg.n_terms,
   // the following code assumes that all fields mentioned above
   // are filled in properly
   // 
   // do not change below this line
   //
   // based on fourier_arg.nterms
   // allocate space for fourier_arg.a_i and fourier_arg.b_i;

   fourier_arg.a_i = (double *)malloc(sizeof(double)*fourier_arg.n_terms);
   if (fourier_arg.a_i == NULL) {
      return EXIT_FAILURE;
   }
   fourier_arg.b_i = (double *)malloc(sizeof(double)*fourier_arg.n_terms);
   if (fourier_arg.b_i == NULL) {
      free(fourier_arg.a_i);
      return EXIT_FAILURE;
   }

   fourier_coefficients(fourier_arg);

   print_fourier_coefficients(fourier_arg.a_i, fourier_arg.b_i, 
                              fourier_arg.n_terms);

   free(fourier_arg.a_i);
   free(fourier_arg.b_i);

   return EXIT_SUCCESS;
} 

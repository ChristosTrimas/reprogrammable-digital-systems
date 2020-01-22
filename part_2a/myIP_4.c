#include "myLib.h"

void myFunc_Accel_4(unsigned int size, unsigned int dim, dataType_t threshold, dataType_t * data0, dataType_t * data1, dataType_t * data2)
{
	unsigned int i, k, r=1;


			for ( i = 0 ; i < size ; i ++ )
			{	

				for ( k = 0 ; k < 4 ; k ++ )
				{
						
					data2 [i*4 + k]=(data0 [ k*4 + 0] * data1 [ i*4+ 0]) + (data0 [ k*4 + 1] * data1 [ i*4+ 1]) + (data0 [ k*4 + 2] * data1 [ i*4+ 2]) + (data0 [ k*4 + 3] * data1 [ i*4+ 3]);
				}	
				

				r= ( data2 [ i*4 + 0 ]>threshold || data2 [ i*4 + 1 ]>threshold || data2 [ i*4 + 2 ]>threshold || data2 [ i*4 + 3]>threshold );

				if ( r )
					{
						data2 [ i*4 + 0 ] = 0.0 ;
						data2 [ i*4 + 1 ] = 0.0 ;
						data2 [ i*4 + 2 ] = 0.0 ;
						data2 [ i*4 + 3 ] = 0.0 ;
							
					}

			
			}			
}

		

		
	
#include "myLib.h"

void myFunc_Accel_16(unsigned int size, unsigned int dim, dataType_t threshold, dataType_t * data0, dataType_t * data1, dataType_t * data2)
{
	unsigned int i, k, l, r=1;

			for ( i = 0 ; i < size ; i ++ )
			{
				

				for ( k = 0 ; k < 16; k ++ )
				{	
					

					for ( l = 0 ; l < 16; l++ )
					{
						data2 [i*16 + k]+=	data0 [ k*16 +l] * data1 [ i*16 +l];
					}	 	
				}

				for ( l = 0 ; r && ( l < 16) ; l+=8 )
				{
					r =( data2 [ i*16 + 0 ]>threshold || data2 [ i*16 + 1 ]>threshold || data2 [ i*16 + 2 ]>threshold || data2 [ i*16 + 3]>threshold || data2 [ i*16 + 4]>threshold || data2 [ i*16 + 5]>threshold || data2 [ i*16 + 6]>threshold || data2 [ i*16 + 7]>threshold );
				}

				if ( r )
				{
					for ( l = 0 ; l < 16; l ++ )
					{
						data2 [ i*16+ l ] = 0.0;
					}
				}

			}		
}

		

		
	
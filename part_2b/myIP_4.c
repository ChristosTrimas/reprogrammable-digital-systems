#include "myLib.h"

void myFunc_Accel_4 (unsigned int size, unsigned int dim, dataType_t threshold, dataType_t * data0, dataType_t * data1, dataType_t * data2)
{


	    // size=1000;
	    // dim=4;
	    // threshold=0.5;

	unsigned int i;
	unsigned int k;
	unsigned int l;

#pragma HLS INTERFACE ap_bus depth=16 port=data0
#pragma HLS INTERFACE ap_bus depth=16000 port=data1
#pragma HLS INTERFACE ap_bus depth=16000  port=data2


 	 float d0[16];
	// float d1[size*dim];
 	 float d2[size*dim];


	for (  k = 0 ; k < 4 ; k ++ )
		{
		d0[k*4+0]=data0[ k * 4 + 0 ];

		d0[k*4+1]=data0[ k * 4 + 1 ];

		d0[k*4+2]=data0[ k * 4 + 2 ];

		d0[k*4+3]=data0[ k * 4 + 3 ];

		}



	for (  i = 0 ; i < size ; i ++ )
	{
#pragma HLS PIPELINE II=1
		int flag=1;

		data2[ i * 4 + 0 ]=0;
		data2[ i * 4 + 1 ]=0;
		data2[ i * 4 + 2 ]=0;
		data2[ i * 4 + 3 ]=0;


		for (  k = 0 ; k < 4 ; k ++ )
		{

		d2[i*4+k]=0;

		for(l=0; l<4 ; l++)
			d2[i*4+k] += d0[k*4+l]*data1[i*4+l];
		

		if(d2[i*4+k]>threshold)
			flag=0;
			
		
		}


		for (  k = 0 ; k < 4 ; k ++ )
			data2 [ i*4 + k ] = d2[ i*4 + k ]*flag;	
			


	  }


}



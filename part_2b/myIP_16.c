#include "myLib.h"

void myFunc_Accel_16 (unsigned int size, unsigned int dim, dataType_t threshold, dataType_t * data0, dataType_t * data1, dataType_t * data2)
{


	      size=1000;
	      dim=16;
	      threshold=0.5;

	unsigned int i,l;
	unsigned int k;

#pragma HLS INTERFACE ap_bus depth=256 port=data0
#pragma HLS INTERFACE ap_bus depth=16000 port=data1
#pragma HLS INTERFACE ap_bus depth=16000  port=data2


 	 float d0[256];
	// float d1[size*dim];
 	 float d2[size*dim];


	for (  k = 0 ; k < 16 ; k ++ )
		{
			myFunc_Accel_16_label3:for (  l = 0 ; l < 4 ; l ++ )
			{
				d0[k*16+4*l+0]=data0[ k * 16 + 4*l+0 ];
				d0[k*16+4*l+1]=data0[ k * 16 + 4*l+1 ];
				d0[k*16+4*l+2]=data0[ k * 16 + 4*l+2 ];
				d0[k*16+4*l+3]=data0[ k * 16 + 4*l+3 ];

			}




		}



	for (  i = 0 ; i < size ; i ++ )
	{
#pragma HLS PIPELINE II=1
		int flag=1;

			for (  l = 0 ; l < 2 ; l ++ )
			{
				data2[k*16+4*l+0]=0;
				data2[k*16+4*l+1]=0;
				data2[k*16+4*l+2]=0;
				data2[k*16+4*l+3]=0;
				data2[k*16+4*l+4]=0;
				data2[k*16+4*l+5]=0;
				data2[k*16+4*l+6]=0;
				data2[k*16+4*l+7]=0;

			}
		

			for (  k = 0 ; k < 16 ; k ++ )
			{

				d2[i*16+k]=0;

				for(l=0; l<16 ; l++)
					d2[i*16+k] += d0[k*16+l]*data1[i*16+l];
				
				if(d2[i*16+k]>threshold)
					flag=0;

			}		


			for (  k = 0 ; k < 16 ; k ++ )
			{
				data2[i*16+k]=d2[ i * 16 + k]*flag;
			}


	 }


}

#include "myLib.h"

#pragma SDS data mem_attribute(data0:CACHEABLE,data1:CACHEABLE,data2:PHYSICAL_CONTIGUOUS)


#pragma SDS data access_pattern(data0:SEQUENTIAL)
#pragma SDS data access_pattern(data1:SEQUENTIAL)
#pragma SDS data access_pattern(data2:SEQUENTIAL)


#pragma SDS data copy(data0[0:dim*dim])
#pragma SDS data copy(data1[0:dim*size])
#pragma SDS data copy(data2[0:dim*size])

#pragma SDS data data_mover(data0:AXIDMA_SIMPLE)
#pragma SDS data data_mover(data1:AXIDMA_SIMPLE)
#pragma SDS data data_mover(data2:AXIDMA_SIMPLE)

void myFunc_Accel_4 (unsigned int size, unsigned int dim, dataType_t threshold, dataType_t * data0, dataType_t * data1, dataType_t * data2)
{


	unsigned int i;
	unsigned int k;
	unsigned int l;

//	dim=4;
//	size=10000;
//	threshold=10000;



//#pragma HLS INTERFACE ap_bus depth=16 port=data0
//#pragma HLS INTERFACE ap_bus depth=16 port=data1
//#pragma HLS INTERFACE ap_bus depth=16  port=data2


 	 float d0[16];
// 	 float d2[size*dim];


	for (  k = 0 ; k < 4 ; k ++ )
		{
		d0[k*4+0]=data0[ k * 4 + 0 ];

		d0[k*4+1]=data0[ k * 4 + 1 ];

		d0[k*4+2]=data0[ k * 4 + 2 ];

		d0[k*4+3]=data0[ k * 4 + 3 ];

		}



	for (  i = 0 ; i < size ; i ++ )
	{
#pragma HLS PIPELINE II=4
		int flag=0;
		float d2[4];


		for (  k = 0 ; k < 4 ; k ++ )
		{

			d2[k]=0;

			for(l=0; l<4 ; l++)
				d2[k] += d0[k*4+l]*data1[i*4+l];
			

			if(d2[k]<threshold)
				flag=1;
		
		}


		for (  k = 0 ; k < 4 ; k ++ )
			data2 [i*4+k] = d2[k]*flag;
	 }


}



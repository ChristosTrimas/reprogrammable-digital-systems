#include "myLib.h"


void myFunc (unsigned int size, unsigned int dim, dataType_t threshold, dataType_t * data0, dataType_t * data1, dataType_t * data2)
{
	unsigned int i, k, l;

	for ( i = 0 ; i < size ; i ++ )
	{
		for ( k = 0 ; k < dim ; k ++ )
		{
			data2 [ i*dim + k ] = 0.0 ;
		}

		for ( k = 0 ; k < dim ; k ++ )
		{
			for ( l = 0 ; l < dim ; l ++ )
			{
				data2 [ i*dim + k ] += data0 [ k * dim + l ] * data1 [ i*dim+ l ];
			}			
		}

		int r = 1 ;

		for ( l = 0 ; r && ( l < dim ) ; l ++ )
		{
			r = ( data2 [ i*dim + l ] > threshold ) ;
		}

		if ( r )
		{
			for ( l = 0 ; l < dim ; l ++ )
			{
				data2 [ i*dim + l ] = 0.0;
			}
		}
	}
}

int main(int argc, char ** argv)
{
	unsigned int i;

	unsigned int seed = (unsigned int)atoi(argv[1]);
	assert(seed>0);

	srand(seed);

	unsigned int size = (unsigned int)atoi(argv[2]);
	assert(size>=1);

	unsigned int dim = (unsigned int)atoi(argv[3]);
	assert(dim>=2);

	dataType_t threshold = (dataType_t)atof(argv[4]);
	assert(threshold>=0.0);

	printf("Seed %u\nSize %u\nDimension %u\nThreshold %f\n\n", seed, size, dim, threshold);
	fflush(stdout);	

	dataType_t * data0 = (dataType_t *)malloc(sizeof(dataType_t)*dim*dim);


	assert(data0!=NULL);

	for(i=0;i<dim*dim;i++)
	{
		dataType_t t = (float)(rand()%10);
		dataType_t d = ((float)(rand()%10))/10;
		data0[i] = t+d;

	}
	
	dataType_t * data1 = (dataType_t *)malloc(sizeof(dataType_t)*dim*size);
//	 dataType_t  data1[dim*size];
	assert(data1!=NULL);

	for(i=0;i<dim*size;i++)
	{
		dataType_t t = (float)(rand()%10);
		dataType_t d = ((float)(rand()%10))/10;
		data1[i] = t+d;

	}

	dataType_t * data2 = (dataType_t *)malloc(sizeof(dataType_t)*dim*size);
	


	assert(data2!=NULL);
	printf("Calling myFunc... \n");
	fflush(stdout);

	myFunc (size, dim, threshold, data0, data1, data2);

	/* timing */
	double totalTime_sw=0.0;
	struct timespec timerStart_sw;
	struct timespec timerStop_sw;

	clock_gettime(CLOCK_REALTIME, &timerStart_sw);

	for(i=0;i<dim*size;i++)
		myFunc (size, dim, threshold, data0, data1, data2);

	clock_gettime(CLOCK_REALTIME, &timerStop_sw);
	totalTime_sw = (timerStop_sw.tv_sec-timerStart_sw.tv_sec)+ (timerStop_sw.tv_nsec-timerStart_sw.tv_nsec) / BILLION;

	printf("Execution time of myFunc: %f\n", totalTime_sw);

	///////////////////////////////////////////////////////////////////////////
	/*my func Accel*/
	//////////////////////////////////////////////////////////////////////////

	dataType_t *data3 = (dataType_t *)malloc(sizeof(dataType_t)*dim*size);


	assert(data3!=NULL);
	printf("\nCalling my func_Accel... \n");
	fflush(stdout);

	myFunc_Accel_16(size,dim,threshold,data0,data1,data3);

	
	for(i=0; i<size;i++){

		// printf("%f=%f\n",data3[i],data2[i]);
		assert(data3[i]==data2[i]); 

	}

	

	double totalTime_sw_accel=0.0;
	struct timespec timerStart_sw_accel;
	struct timespec timerStop_sw_accel;

	clock_gettime(CLOCK_REALTIME, &timerStart_sw_accel);

	for(i=0;i<dim*size;i++)
		myFunc_Accel_16(size, dim, threshold, data0, data1, data3);

	clock_gettime(CLOCK_REALTIME, &timerStop_sw_accel);
	totalTime_sw_accel = (timerStop_sw_accel.tv_sec-timerStart_sw_accel.tv_sec)+ (timerStop_sw_accel.tv_nsec-timerStart_sw_accel.tv_nsec) / BILLION;

	printf("Execution time of myFunc_Accel: %f\n", totalTime_sw_accel);

	printf("\nDONE\n\n");
	fflush(stdout);

	free(data0);
	free(data1);
	free(data2);
	free(data3);	

	return 0;
}


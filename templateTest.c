#include "templateTest.h"
#include "all_possible_sums.h"

void templatetest()
{
	int ai[3] = {1,2,3};
	int bi[3] = {4,5,6};
	float af[3] = {1.0,2.0,3.0};
	float bf[3] = {1.5,2.5,3.5};
	
	TEMPLATE(sum,int)(3,ai,bi);
	TEMPLATE(sum,float)(3,af,bf);
}
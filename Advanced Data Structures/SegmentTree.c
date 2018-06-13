/*
  Segment Tree Data Structure
  Given an array arr with N elements,this Data Structure handles
  - Sum queries from any valid index l to index r in O(log N) time
  - Update queries at any valid index i in original array in O(log N) time (taking care of the sum queries that may follow this query)
 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
static inline int mid_of(int low,int high){ return (low+high)/2; }
static int constructUtil(int arr[],int ss,int se,int* segment,int curr_root)
{
	int retval;
	if(ss==se)
	{
		retval=arr[ss];
		segment[curr_root]=retval;
	}
	else
	{
		int mid=mid_of(se,ss);
		retval=constructUtil(arr,ss,mid,segment,2*curr_root+1)+constructUtil(arr,mid+1,se,segment,2*curr_root+2);
	}
	return retval;
}
int* constructSegmentTree(int arr[],int n)
{
	int height=(int)(ceil(log2(n)));
	int max_size=2*((int)pow(2,height))-1;
	int* ret_segment_ptr=(int *)malloc(sizeof(int)*n);
	constructUtil(arr,0,n-1,ret_segment_ptr,0);
	return ret_segment_ptr;
}
static void updateUtil(int arr[],int* segment,int ss,int se,int i,int difference,int si)
{
	if( i <=se && i >= ss )//in range
	{
		segment[si]+=difference;
		int mid=mid_of(ss,se);
		updateUtil(arr,segment,ss,mid,i,difference,2*si+1);
		updateUtil(arr,segment,mid+1,se,i,difference,2*si+2);
	}
}
//Update = O(log N)
void update(int arr[],int* segment,int n,int index,int new_value)
{
	if(index < 0 || index > n-1)
	{
		;
	}
	else
	{
		int difference=new_value-arr[index];
		arr[index]+=difference;
		updateUtil(arr,segment,0,n-1,index,difference,0);
	}
}
static int getSumUtil(int* segment,int ss,int se,int query_l,int query_r,int si)
{
	int retval=0;
	if(query_l > ss && query_r < se)
	{
		if(ss==se)
		{
			retval=segment[si];
		}
		else
		{
			int mid=mid_of(ss,se);
			retval=getSumUtil(segment,ss,mid,query_l,query_r,2*si+1)+getSumUtil(segment,mid+1,se,query_l,query_r,2*si+2);
		}
	}
	else if(query_l <= ss && query_r >= se)
	{
		retval=segment[si];
	}
	return retval;
}
//sum
int getSum(int* segment,int n,int left,int right)
{
	int retval=0;
	if(left < 0 || left > right || right > n-1)
	{
		retval=-1;
	}
	else
	{
		retval=getSumUtil(segment,0,n-1,left,right,0);
	}
} 

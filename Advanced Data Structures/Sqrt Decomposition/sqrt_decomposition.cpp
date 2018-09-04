#include <bits/stdc++.h>
using namespace std;
class sqrt_decomposition
{
private:
	int block_size;
	int* blocks;
	int* arr;
	int length;
public:
	sqrt_decomposition(int* array,int len);
	void update(int index,int new_value);
	int query(int left,int right);
	//~sqrt_decomposition();	//Free Memory (Important)
};
sqrt_decomposition::sqrt_decomposition(int* array,int len)
{
	if(array==NULL)
		throw "NULL POINTER EXCEPTION";
	else
	{
		arr=new int(len);
		for(int i=0;i<len;i++){
			arr[i]=array[i];
		}
		length=len;
		block_size=ceil(sqrt(len));
		blocks=new int(block_size);
		for(int i=0;i<len;i++)
		{
			blocks[i/block_size] += array[i];
		}
	}
}
void sqrt_decomposition::update(int index,int new_value)
{
	int old_value=arr[index];
	blocks[index/block_size] += (new_value - old_value);
	arr[index] = new_value;
}
int sqrt_decomposition::query(int left,int right)
{
	int sum = 0;
    while (left<right and left%block_size!=0 and left!=0)
    {
        sum += arr[left];
        left++;
    }
    while (left+block_size <= right)
    {
        sum += blocks[left/block_size];
        left += block_size;
    }
    while (left<=right)
    {
        sum += arr[left];
        left++;
    }
    return sum;
}
signed main()
{

	//code here to use sqrt_decomposition data structure

	return 0;
}

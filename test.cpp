#include <iostream>
#include "vector.h"
#include "alloc.h"
//#include<vector>
using namespace std;
int main()
{
	My_vector<int,JY::allocator<int> > vec(5);
	My_vector<int,JY::allocator<int> >::iterator iter;
	for(iter = vec.begin();iter != vec.end();iter++)
		cout<<*iter<<" ";
	cout<<endl;
	return 0;
}

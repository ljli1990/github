#include  <stdio.h> 
typedef int (*int_array)[10];
int main()
{

	int a[10]={1,2,3,4,5};
	int_array i=&a;

	printf("%d=%d\n",i[0][4],a[4]);
      return 0;
}

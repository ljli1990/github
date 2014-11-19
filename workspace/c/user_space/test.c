#include <stdio.h>
#include <stdlib.h>
int bss_var;
int data_var0 = 1;

int main(int argc,char **argv)
{
	printf("The user space's address division of a process as follow:\n");
	printf("Data segment:\n");
	printf("address of \"main\" function:%p\n\n",main);

        printf("Data segment:\n");
	printf("address of data_var:%p\n",&data_var0);
	static int data_var1 = 4;
	printf("new end of data_var:%p\n\n",&data_var1);

        printf("BSS:\n");
	printf("address of bss_var:%p\n\n",&bss_var);

	char *str = (char *)malloc(sizeof(char)*10);
	printf("initial heap end:%p\n",str);
	char *buf = (char *)malloc(sizeof(char)*10);
	printf("new heap end:%p\n\n",buf);

        int stack_var0 = 2;
	printf("Stack segment:\n");
	printf("initial end of stack:%p\n",&stack_var0);
	int stack_var1 = 3;
	printf("new end of stack:%p\n",&stack_var1);

	return 0;
}

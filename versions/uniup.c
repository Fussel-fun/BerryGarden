#include <stdio.h>
#include <stdlib.h>
int main ()
{
	printf("Getting Versions");
	system("uniup.sh");
	int input = 0;
	do 
	{
		printf("Versions:\n");
		printf("1 = V0.3.0\n2 = V0.3.1\n9 = uninstall");
		scanf("%i", &input);
	}while(input == 0);
	
	if (input == 1)
	{
		system("updatev03.sh");
	}
	else if (input == 2)
	{
		system("updatev031.sh");
	}
	else if (input == 9)
	{
		system("uninstallbg.sh");
	}
return 0;
}

#include <stdio.h>

int main ()
{
printf("Getting Versions");
	system("uniup.sh");
	int input = 0;
	do 
	{
		printf("Versions:\n");
		printf("1 = V0.3.0\n2 = V0.3.1\n3 = V0.4\n9 = uninstall");
		scanf("%i", &input);
	}while(input == 0);
	
	if (input == 1)
	{
		system("updatev03.sh");
	}
	if (input == 2)
	{
		system("updatev031.sh");
	}
	if (input == 3)
	{
		system("updatev04.sh");
	}
	if (input == 9)
	{
		system("uninstallbg.sh");
	}
system("uniup.sh");
return 0;
}

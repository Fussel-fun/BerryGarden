#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
int mainmenu(int in);
int quitssh ();
int openlog ();
int gpioff();


const int lightcheck = 1;
const int soilcheck = 2;
const int tempmon = 3;
const int lisomonitor = 4;
const int pumpon = 5;
const int gpiooff = 6;
const int update = 7;
const int tmux = 8;
const int quit = 9;

// Define Pins 
// DEFINE GPIO PINS 
#define PIN26 25        // OUTPUT LIGHTCHECK
#define PIN16 27        // READ LIGHTCHECK
#define PIN14 15        // OUTPUT SOIL
#define PIN15 16        // READ SOIL 
#define PIN18 1 		// Pump PWR

	
// MAIN FUNK
int main ()
{
	char *print = "READY TO GET GROWING?\n";

	int in = 0;
wiringPiSetup();
     pinMode (PIN26, OUTPUT); //LIGHTCHECK
     pinMode (PIN16, INPUT);  //LIGHTCHECK
     pinMode (PIN14, OUTPUT); //SOILPROB
     pinMode (PIN15, INPUT);  //SOILPROB
     pinMode (PIN15, OUTPUT); // PUMP PWR
 

	// check Update 
	system("uniup.sh");
	// Set Time
	time_t currentTime;
	time(&currentTime);
	// Set Pinmode		
	// Greet User with time 
	printf ("\n\n");
	printf("WELCOME TO BERRYGARDEN!\n");
	printf("%s", print);
	delay (500);

while (in != 9)
{
printf("Choose Option:\n");
printf("1 = LIGHT\n2 = SOIL\n3 = TEMP\n4 = SOIL/LIGHTMONITOR\n5 = WATER S/L\n6 = GPIOOFF\n7 = UPDATE\n8 = TMUX\n9 = QUIT\n\n ");
scanf("%i", &in);
in = mainmenu(in);
}

return 0;
}			
// PROTOTYPE FUNK
int mainmenu(int in)
{
   time_t currentTime;
   time(&currentTime);					
if (in == lightcheck)
{
    FILE* file;
    file = fopen("log.md", "a");
	digitalWrite(PIN26, HIGH);
    if (digitalRead(PIN16) == LOW)
    {
    	fprintf(file, "%s\n LIGHT OFF\n\n", ctime(&currentTime));
        printf("OFF\n");
        fclose(file);    
    }
 	if (digitalRead(PIN16) == HIGH)
    {
        // LIGHT MENU
        fprintf(file, "%s\n LIGHT ON\n\n", ctime(&currentTime));
        printf("ON\n");
        fclose(file);
    }
	delay(500);
}
if (in == soilcheck)
{
	FILE* file;
		file = fopen("log.md", "a");
		pullUpDnControl (PIN15, PUD_OFF);
		 digitalWrite(PIN14, HIGH);
			if (digitalRead(PIN15) == HIGH)
			{
				printf("Genug Feuchtigkeit\n");
				fprintf(file, "%s\n ERDE FEUCHT\n\n", ctime(&currentTime));
				fclose(file);
				digitalWrite(PIN14, LOW);
				}
				else if(digitalRead(PIN15) == LOW)
				{
					printf("Trocken\n");
					fprintf(file, "%s\n ERDE TROCKEN\n\n", ctime(&currentTime));
					fclose(file);
					digitalWrite(PIN14, LOW);
				}      
	delay(500);
}
if (in == tempmon)
{
	system("./runtemp.sh");
	in = 0;
}
if (in == lisomonitor)
{
	printf("STARTING MONITOR\n");
	system("monitor");
	in = 0;
}
if (in == pumpon)
{
	digitalWrite(PIN18, HIGH);
		printf("PUMP RUNNING\npress any Number to Stop Pump(not 0)");
		scanf("%i", in);
	if (in =! 0)
	{
	digitalWrite(PIN18, LOW);
	in = 0;	
	}

}
if (in == gpiooff)
{
	gpioff();
	in = 0;
}
if (in == update)
{
	system("uniup");
	in = 0;
}
if (in == tmux)
{
	system("tmux");
	in = 0;
}
if (in == quit)
{
	printf("QUIT\n");
	time_t currentTime;
	time(&currentTime);
	FILE *file;
	file = fopen("log.md", "a");
	if (file == NULL)
	{
		printf("Failed to Open file\n");
		return 1;
	}
	fprintf(file, "%s\n SSH CLOSED\n",ctime(&currentTime));
	fclose(file);
	gpioff();
	return 9;	
}
return 0;
}
	    		    		    	
int openlog (int in)
{
int logls =1;
int logth =2;
	
// Ask waht Log?
in = 0;
do 
{
printf("LOGS:\n1 = LIGHT/SOIL\n2 = TEMP/HUM\n");
		scanf("%i", &in);
}while(in <= 0 || in > 2);		
// if 1 open LS Log 
if(in == logls)
{
	    printf("\n\n");
	    FILE *file = fopen("log.md", "r");  
	    if (file == NULL) { 
	    printf("Failed to Open file"); 
	        return 1;  
	    }
	    // Read and print each line from the file
	    char buff[100];
	        while (fgets(buff, sizeof(buff), file) != NULL) {
	            printf("%s", buff);
	        }
	    delay(3000);
	    printf("\n\n");
	    fclose(file);	
}
// if 2 open Temp log 
else if(in == logth)
{
	printf("\n\n");
	FILE *file = fopen("logtemp.txt", "r");  
	if (file == NULL) { 
	printf("Failed to Open file"); 
	    return 1;  
	}
	// Read and print each line from the file
	char buff[100];
	    while (fgets(buff, sizeof(buff), file) != NULL) {
	        printf("%s", buff);
	    }
	delay(3000);
	printf("\n\n");
	fclose(file);
}
in = 0;
return 0;
}


// Turn Off GPIO and print to Log
int gpioff()
{
    time_t currentTime;
    time(&currentTime);
    FILE* file;
    file = fopen("logtemp.txt", "a");
    digitalWrite (PIN26, LOW);
    digitalWrite (PIN14, LOW);  
    fprintf(file, "%s\n GPIO OFF\n\n", ctime(&currentTime));
    fclose(file);
    return 0;
}


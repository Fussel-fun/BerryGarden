#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <time.h>

// DEFINE GPIO PINS 
#define PIN26 25        // OUTPUT LIGHTCHECK
#define PIN16 27        // READ LIGHTCHECK
#define PIN14 15        // OUTPUT SOIL
#define PIN15 16        // READ SOIL 



const int LIGHT = 1;
const int WTR = 2;
const int LOG = 3;
const int RNMON = 4;
const int UP = 5;
const int GPIO = 6;
const int TEMP = 7;
const int BASH = 8;
const int QUIT = 9;

int mainmenu(int in);
int soilreadGPIO();
int checkLightGPIO();
int GPIOOFF();

int main()
{
   system("uniup.sh");
   wiringPiSetup();
        pinMode (PIN26, OUTPUT); //LIGHTCHECK
        pinMode (PIN16, INPUT);  //LIGHTCHECK
        pinMode (PIN14, OUTPUT); //SOILPROB
        pinMode (PIN15, INPUT);  //SOILPROB
		int in = 0;
		// Get Current Time 
        time_t currentTime;
        time(&currentTime);
        // While not Quit 
    while (in != 9)
    {
    // Print Current Time 			
    printf("\n\n");
	printf("HELLO FROM YOUR OWN BERRYGARDEN!\n\n");
  	printf("%s",  ctime(&currentTime));
        // print Options while no Option is Choosen 
        do
        {
            printf("Choose Option:\n\nOptions: \n1 = LIGHT MONITOR\n2 = SOIL MONITOR\n3 = LOGS\n4 = Run Monitor\n5 = UPDATE\n6 = GPIOOFF\n7 = Temp\n8 = TMUX\n9 = SSH Quit\n");
            scanf("%i", &in);
        }
        while (in == 0);
    // Open Menu Points 
    mainmenu(in);    
    }
    return 0;
}

// Main Menu
int mainmenu(int in)
{
int monmins = 0;
    if (in == LIGHT)
    {
    // LIGHT MENU
    checkLightGPIO();
    delay(500);
    }
    else if (in == WTR)
    {
    // WATER MENU
	soilreadGPIO();
	delay(500);
    }
    else if (in == LOG)
    {
    printf("\n\n");
    FILE *file = fopen("log.md", "r");  
    if (file == NULL) {  
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
    else if (in == RNMON)
    {
    	system("monitor");
    }
    else if (in == UP)
    {
    	system("uniup");
    }
    else if (in == GPIO)
    {
    	GPIOOFF();
    }
    else if (in == TEMP)
    {
    	system("runtemp.sh");
    }
    else if (in == BASH)
    {
    	system("tmux");
    }
    else if (in == QUIT)
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
    GPIOOFF();
    return 0;
    }
in = 0;
}

// Check Soil
int soilreadGPIO()
{
    time_t currentTime;
    time(&currentTime);
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
return 0;        
}

// Check if Light is On 
int checkLightGPIO()
{
    time_t currentTime;
    time(&currentTime);
    FILE* file;
    file = fopen("log.md", "a");
	digitalWrite(PIN26, HIGH);
    if (digitalRead(PIN16) == LOW)
    {
    	fprintf(file, "%s\n LIGHT OFF\n\n", ctime(&currentTime));
        printf("OFF\n");
        fclose(file);
        return 0;      
    }
 	if (digitalRead(PIN16) == HIGH)
    {
        // LIGHT MENU
        fprintf(file, "%s\n LIGHT ON\n\n", ctime(&currentTime));
        printf("ON\n");
        fclose(file);
        return 1;
    }
}



// Turn Off GPIO and print to Log
int GPIOOFF()
{
    time_t currentTime;
    time(&currentTime);
    FILE* file;
    file = fopen("log.md", "a");
    digitalWrite (PIN26, LOW);
    digitalWrite (PIN14, LOW);  
    fprintf(file, "%s\n GPIO OFF\n\n", ctime(&currentTime));
    fclose(file);
    return 0;
}
// Fan Switch INACTIVE
/*int fanGPIO (char in)
{
time_t currentTime;
time(&currentTime);
FILE* file;

file = fopen("log.md", "a");
	if (in == 1)
	{
		// Turn FAN 2 on
		digitalWrite(PIN17, HIGH);
		printf("FAN: %i\n", fan[1]);
		// if FAN ON
		fprintf(file, "%s\n FAN ON\n\n", ctime(&currentTime));
		//Send Terminal Indicator
		printf("Running\n");
		return 1;
	}
	else if (in == 0)
	{
		// Turn FAN off
		digitalWrite(PIN17, LOW);
		printf("FAN: %i\n", fan[0]); 
		fprintf(file, "%s\n FAN OFF\n\n", ctime(&currentTime));
		//Send Terminal Indicator
		printf("Off\n");
		return 0;
	}
}

//Water Pump Switch INACTIVE
int pumpGPIO(char in)   //HDWR1
{
    time_t currentTime;
    time(&currentTime);
    FILE* file;
    file = fopen("log.md", "a");
    // Set GPIO Pin for Water System 
    if (in == 0)
    {
    	digitalWrite(PIN2, LOW);
        printf("Pump Off\n");
        fprintf(file, "%s\n PUMP OFF\n\n", ctime(&currentTime));
        fclose(file);
        return 0;
    }
    else if (in == 1)
    {
    	digitalWrite(PIN2, HIGH);
        printf("Pump On\n");
        fprintf(file, "%s\n PUMP ON\n\n", ctime(&currentTime));
        fclose(file);
        return 1;
    }
}
*/

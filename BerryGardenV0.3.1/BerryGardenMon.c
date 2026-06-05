#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <time.h>

#define PIN26 25        // OUTPUT LIGHTCHECK
#define PIN16 27        // READ LIGHTCHECK
#define PIN14 15        // OUTPUT SOIL
#define PIN15 16        // READ SOIL 

char checkLight();
char checkSoil();

const int MINUTE = 60;

int main()
{
char in = 0;

	wiringPiSetup();
		pinMode (PIN26, OUTPUT);	// OUTPUT LIGHTCHECK
		pinMode (PIN16, INPUT);		// READ LIGHTCHECK
		pinMode (PIN14, OUTPUT); 	//SOILPROB
		pinMode (PIN15, INPUT);  	//SOILPROB
printf("Starting Monitor\n");
delay(500);
for (int i = 0; i < MINUTE; i++)
{
time_t currentTime;
time(&currentTime);
printf("%s", ctime(&currentTime));
checkSoil();
checkLight();
delay(1000);	
}
return 0;
}

char checkSoil()
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
                fprintf(file, "%s\n ERDE FEUCHT TEST\n\n", ctime(&currentTime));
                fclose(file);
                digitalWrite(PIN14, LOW);
            }
            else if(digitalRead(PIN15) == LOW)
            {
                printf("Trocken\n");
                fprintf(file, "%s\n ERDE TROCKEN TEST\n\n", ctime(&currentTime));
                fclose(file);
                digitalWrite(PIN14, LOW);
            }   
}


char checkLight()
{
        time_t currentTime;
        time(&currentTime);
        FILE* file;
        file = fopen("log.md", "a");
	digitalWrite(PIN26, HIGH);
        if (digitalRead(PIN16) == LOW)
        {
        	fprintf(file, "%s\n LIGHT OFF TEST\n\n", ctime(&currentTime));
            printf("LIGHT OFF\n");
            fclose(file);
            digitalWrite(PIN26, LOW);    
        }
 	if (digitalRead(PIN16) == HIGH)
        {
            // LIGHT MENU
            fprintf(file, "%s\n LIGHT ON TEST\n\n", ctime(&currentTime));
            printf("LIGHT ON\n");
            fclose(file);
            digitalWrite(PIN26, LOW);
        }	
}

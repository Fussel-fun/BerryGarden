#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <time.h>

// MENUES 
int mainmenu(int in);               //    MAINMENU
int TMP (int in);       //  TEMP SETTINGS 
int LGHT (int in);                  //   LIGHT SETTINGS
int WT (int in);                    //   WATER SETINGS 
int AIRFLOW(int in);                //    AIRFLOW SETTINGS 
// GPIO Function
// TMP
int tempGPIO(int in);
int fanGPIO(int in);
// WT
int soilreadGPIO();
int pumpGPIO(int in);
// LGHT
char checkLightGPIO(int in);
int GPIOOFF();

// DEFINE GPIO PINS 
#define PIN17 0         // OUTPUT FAN
#define PIN27 2         //  READ FAN
#define PIN26 25        // OUTPUT LIGHTCHECK
#define PIN16 27        // READ LIGHTCHECK
#define PIN14 15        // OUTPUT SOIL
#define PIN15 16        // READ SOIL 
#define PIN2 3          //  OUTPUT PUMP 
#define PIN3 4      // READ PUMP 

// BIND INPUT 
// For Temp Menu
const int TEMP = 1;
// For Light Menu
const int LIGHT = 2;
// For Water Menu 
const int WTR = 3;
// For Airflow
const int AIR = 4;
// Print Logs
const int LOG = 5;
// For Exiting 
const int QUIT = 9;

// MAIN
int main (void)
{
    int input = 0;
    // Set GPIO Modes 
    wiringPiSetup();
        pinMode (PIN17, OUTPUT); //FAN
        pinMode (PIN27, INPUT);  //FAN
        pinMode (PIN26, OUTPUT); //LIGHTCHECK
        pinMode (PIN16, INPUT);  //LIGHTCHECK
        pinMode (PIN14, OUTPUT); //SOILPROB
        pinMode (PIN15, INPUT);  //SOILPROB
        pinMode (PIN2, OUTPUT);  //PUMP
        pinMode (PIN3, INPUT);   //PUMP
        // Set CurrentTime for Main Menu 
        time_t currentTime;
        time(&currentTime);
    while (input != 9)
    {
                printf("%s",  ctime(&currentTime));
        // print Options while no Option is Choosen 
        do
        {
            printf("Choose Option:\n\nOptions: \n1 = TEMP MENU\n2 = LIGHT MENU\n3 = WATER MENU\n4 = AIR MENU\n5 = LOGS\n9 = QUIT\n");
            scanf("%i", &input);
        }
        while (input == 0);
    // Open Menu Points 
    mainmenu(input);    
    }
return 0;
}    

// Main Menu
int mainmenu(int in)
{
    if (in == TEMP)
    {
    // TEMP MENU 
    TMP (in);
    }
    else if (in == LIGHT)
    {
    // LIGHT MENU
    LGHT(in);
    }
    else if (in == WTR)
    {
    // WATER MENU
    WT(in);
    }
    else if (in == AIR)
    {
    // AIR-FLOW MENU
    AIRFLOW(in);
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
    else if (in == QUIT)
    {
    GPIOOFF();
    return 0;
    }
 in = 0;
}

// TEMP Settings 
int TMP (int in)
{
    in = 0;
    // TEMP MENU
    printf("TEMP MENU \n\n");
    printf("Choose Option:\n\n");
    // Read Temp Of PiPico 
    printf("1 = Read Temp\n");
    printf("2 = Turn on Fan\n");
    scanf("%i", &in);
        if(in == 1)
        {
            tempGPIO(1);
        }
        else if(in == 2)
        {           
            fanGPIO(1);                                          // 1 = on 0 = off
            printf("Press 0 to Turn off Fans\n");
            scanf("%i", &in);
                if (in == 0)
                {
                fanGPIO(in);
                }  
        }
        else if (in == 9)
        {
            return 1;
        }
return 0;
}

// LIGHT Settings 
int LGHT (int in)
{
    // LIGHT MENU
    printf("LIGHT MENU\n\n");
    // Print Light on off
    checkLightGPIO(in);
    delay(500);
    printf("\n\n");
}
// WATER Settings 
int WT (int in)
{
in = 0;
    do
    {   
        // Settings for Watering System 
        printf("DEBUG: in %i\n", in);
        printf("3 = Pump off\n");
        printf("1 = Pump on\n");
        printf("2 = Read Soil:\n");
        printf("9 = Quit\n"); 
        scanf("%i", &in);
    } while (in == 0);
    //WATER MENU
printf("WATER MENU\n\n");
// print amount and leght of watering Period 
    if (in == 1)
    {
        pumpGPIO(in);
        delay(1000);
        pumpGPIO(3);
    }
    // Read Soil Moister
    else if (in == 2)
    {
        soilreadGPIO();
    }
    else if(in == 3)
    {
        pumpGPIO(in);
    }
    else if (in == 9)
    {
        return 0;
    }
digitalWrite(PIN14, LOW);
delay(1000);
printf("\n\n");
}
// AIRFLOW / HUMIDITY Settings
int AIRFLOW(int in)
{
in = 0;
printf("DEBUG: in %i\n", in);
// AIR-FLOW MENU
printf("AIR-FLOW MENU\n\n");
// Print Humidity 

// Print Avrage Humidity

// Print Max Humidity for Sucking wet air out 

// Set Max Humidity 

// Print Logs of airchange and humidity 
}

// Hard Ware Control
// TEMP controll
int tempGPIO(int in)   //HDWR3
{   
    time_t currentTime;
    time(&currentTime);
    FILE* file;
    file = fopen("log.md", "a");
    // Read temp from PiPico     
    fprintf(file, "%s\n Temp: %i\n\n", ctime(&currentTime), tempGPIO);
    fclose(file);
} 

int fanGPIO (int in)
{//1 PINS READ 1 PIN Powers Transistor 
    time_t currentTime;
    time(&currentTime);
    FILE* file;

    file = fopen("log.md", "a");
    int fan[2]= {0, 1} ;
    if (in == 1)
    {
        // Turn FAN 2 on
        digitalWrite(PIN17, HIGH);
        printf("FAN: %i\n", fan[1]);
            // if FAN ON
            if (digitalRead(PIN27) == HIGH)
            {
            fprintf(file, "%s\n FAN ON\n\n", ctime(&currentTime));
            //Send Terminal Indicator
            printf("Running\n");

            }
    }
    else if (in == 0)
    {
    // Turn FAN off
    digitalWrite(PIN17, LOW);
    printf("FAN: %i\n", fan[0]);
        // if LED On 
        if (digitalRead(PIN27) == LOW)
        {
        //Send Terminal Indicator
        printf("Off\n");
        fprintf(file, "%s\n FAN OFF\n\n", ctime(&currentTime));
        } 
    }
              fclose(file);
}

// WTR Controll
// READ SOIL
int soilreadGPIO()
{
    time_t currentTime;
    time(&currentTime);
    FILE* file;

    file = fopen("log.md", "a");
    int in = 0;
            pullUpDnControl (PIN15, PUD_OFF);
            digitalWrite(PIN14, HIGH);
            if (digitalRead(PIN15) == HIGH)
            {
                printf("Genug Feuchtigkeit\n");
                fprintf(file, "%s\n ERDE FEUCHT\n\n", ctime(&currentTime));
                fclose(file);
                digitalWrite(PIN14, LOW);
                return 0;
            }
            else if(digitalRead(PIN15) == LOW)
            {
                printf("Trocken\n");
                fprintf(file, "%s\n ERDE TROCKEN\n\n", ctime(&currentTime));
                fclose(file);
                digitalWrite(PIN14, LOW);
                printf("Bewässerung Starten?");
                printf("Press 1 for ON or 9 to Quit");
                scanf("%i", &in);
                if (in == 1)
                {
                    pumpGPIO(1);
                    delay(5000);
                    pumpGPIO(3);
                }
                else if (in == 9)
                {
                    return 0;
                }
            }        
}

//PUMP GPIO
int pumpGPIO(int in)   //HDWR1
{//1 PIN READ 1 Pin power Transisrtor 
    time_t currentTime;
    time(&currentTime);
    FILE* file;
    file = fopen("log.md", "a");
    // Set GPIO Pin for Water System 
    if (in == 3)
    {
        printf("Pump Off\n");
        fprintf(file, "%s\n PUMP OFF\n\n", ctime(&currentTime));
        fclose(file);
    }
    if (in == 1)
    {
        printf("Pump On\n");
        fprintf(file, "%s\n PUMP ON\n\n", ctime(&currentTime));
        fclose(file);
    }

return 0;
}

// LIGHT Controll
char checkLightGPIO(int in)
{
    time_t currentTime;
    time(&currentTime);
    FILE* file;
    file = fopen("log.md", "a");
	in = 0;
	digitalWrite(PIN26, HIGH);
    if (digitalRead(PIN16) == LOW)
    {
        printf("OFF\n");
        fprintf(file, "%s\n LIGHT OFF\n\n", ctime(&currentTime));
        printf("Change Air For 2 Minutes? 1 ON 2 OFF");
       while(in == 0)
        {
        	scanf("%i", &in);
        }  
     		if (in == 1);
     		{
     			for (int i = 0; i < 120; i++)
        		{
        	    fanGPIO (1);
        	    delay(1000);
        		}
        	fanGPIO(0);
        	digitalWrite(PIN26, LOW);
        	digitalWrite(PIN16, LOW);  
        	}
        	if (in == 2)
        	{
        		return 0;
        	}                         
    }
 	if (digitalRead(PIN16) == HIGH)
    {
        // LIGHT MENU
        fprintf(file, "%s\n LIGHT ON\n\n", ctime(&currentTime));
        printf("ON\n");
    }
delay(500);
fclose(file);
return 0;
}

int GPIOOFF()
{
    time_t currentTime;
    time(&currentTime);
    FILE* file;
    file = fopen("log.md", "a");
    digitalWrite (PIN17, LOW);
    digitalWrite (PIN26, LOW);
    digitalWrite (PIN14, LOW);  
    fprintf(file, "%s\n GPIO OFF(Closed Programm)\n\n", ctime(&currentTime));
    fclose(file);
    return 0;
}
// Edit 



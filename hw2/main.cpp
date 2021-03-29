#include "mbed.h"

#include "uLCD_4DGL.h"

DigitalIn up(D3);
DigitalIn down(D8);
DigitalIn sel(D5);
AnalogOut sig(PA_4);

uLCD_4DGL uLCD(D1, D0, D2);


int main()
{
    int fre = 360;
    float T = 1000 / fre;
    float ADCdata[100];
    int confirm = 0;
    float i = 1.0f;
    int j = 1;

    uLCD.printf("Please select your frequency\n"); //Default Green on black text
    uLCD.printf("\n%5d Hz", fre);
    while(1){
        if(up){
            fre += 20;
            uLCD.locate(0,3);
            uLCD.printf("%5d Hz", fre);
        }
        if(down){
            fre -= 20;
            uLCD.locate(0,3);
            uLCD.printf("%5d Hz", fre);
        }
        if(sel){
            uLCD.locate(0,5);
            uLCD.printf("Your frequency is %5d Hz", fre);
            T = 1000.0 / fre;
            confirm = 1;
        }
        if(i <= 80)
            sig = i / 80.0f / 1.1f;
        if(i > 80)
            sig = (100 - i) / 20.0f / 1.1f;
        if(i > 100)
            i = 0.0f;
        wait_us((T * 10) - 19.3);

        if(confirm) {
            ADCdata[j - 1] = sig;
            if(j == 100){
                printf("%d\r\n", fre);
                for (int k = 0; k < 100; k++){
                    printf("%lf\r\n", ADCdata[k]);
                }
                j = 1;
                confirm = 0;
            }
            else j++;
        }
        i++;
    }
}

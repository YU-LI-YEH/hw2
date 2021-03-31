#include "mbed.h"

#include "uLCD_4DGL.h"

DigitalIn up(D3);
DigitalIn down(D8);
DigitalIn sel(D5);
AnalogOut sig(PA_4);
AnalogIn sig_fil(D11);

uLCD_4DGL uLCD(D1, D0, D2);


int main()
{
    int fre = 40;
    float T = 1000 / fre;
    float T2;
    float ADCdata[500];
    bool confirm = 0;
    float i = 1.0f;
    int j = 1;
    int a = 1;

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
            a = 1;
        }
        if(i <= 80)
            sig = i / 80.0f / 1.1f;
        if(i > 80)
            sig = (100 - i) / 20.0f / 1.1f;
        if(i > 100)
            i = 0.0f;
        if(((T * 10) - 19.3) > 0)
            T2 = (T * 10) - 19.3;
        else
            T2 = 0;
        wait_us(T2);


        if(confirm) {
            if (a == (100 * fre / 500)){
                printf("%d", a);
                ADCdata[j - 1] = sig_fil;
                if(j >= 500){
                    printf("%d\r\n", fre);
                    for (int k = 0; k < 500; k+=1){
                        printf("%lf\r\n", ADCdata[k]);
                    }
                    j = 1;
                    confirm = 0;
                    
                }
                else j++;
                a = 1;
            }
        }
        i++;
        a++;
    }
}

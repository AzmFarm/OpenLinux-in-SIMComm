#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <ctype.h>

#include "ATControl.h"


//void print_option_menu(const char* options_list[], int array_size);
//static void simcom_at_test();

void print_option_menu(const char* options_list[], int array_size)
{
    int i,j;
    for (i=0; i<(array_size/2); i++)
    {
        printf("%s",options_list[2*i]);
        for(j=30-strlen(options_list[2*i]); j>0; j--)
        {
            printf(" ");
        }
        printf("%s\n",options_list[2*i+1]);
    }

    if(array_size%2 != 0)
    {
        printf("%s\n",options_list[array_size -1]);
    }
}

int main()
{
    const char *options_list[] = {
        "1. get Module Version",
        "2. get CSQ",
        "3. get CREG",
        "4. get ICCID",
        "5. get IMEI",
        "6. get CIMI",
        "99. back"
    };

    int opt = 0;
    //int i,j;
    int ret;
    char scan_string[100] = {0};
    char buff[100]; 

    ret = atctrl_init();
    if(ret != 0)
    {
        return 0;
    }

    while(1)
    {
        printf("\nPlease select an option to test from the items listed below.\n");
        print_option_menu(options_list, sizeof(options_list)/sizeof(options_list[0]));
        printf("Option > ");
         
        memset(scan_string, 0, sizeof(scan_string));
        if (fgets(scan_string, sizeof(scan_string), stdin) == NULL)
            continue;

        /* Convert the option to an integer, and switch on the option entered. */
        opt = atoi(scan_string);
        switch(opt)
        {
            case 1:
                {
                    memset(buff,0,sizeof(buff));
                    getModuleRevision(buff, sizeof(buff));
                    printf("version: %s\n", (buff));
                }
                break;
            case 2:
                {
                    uint8_t rssi;
                    getCSQ(&rssi);
                    printf("csq: %d\n", rssi);
                }
                break;
            case 3:
                {
                    int reg_val;
                    reg_val = getCREG();
                    printf("reg: %d\n", reg_val);
                }
                break;
            case 4:
                {
                    memset(buff,0,sizeof(buff));
                    getICCID(buff, sizeof(buff));
                    printf("ICCID: %s\n", (buff));
                }
                break;
            case 5:
                {
                    memset(buff,0,sizeof(buff));
                    getIMEI(buff, sizeof(buff));
                    printf("IMEI: %s\n", (buff));
                }
                break;
            case 6:
                {
                    memset(buff,0,sizeof(buff));
                    getCIMI(buff, sizeof(buff));
                    printf("CIMI: %s\n", (buff));
                }
                break;

            default:
                break;
            }

        if(opt == 99)
        {
            break;
        }
    }

    atctrl_deinit();		
}

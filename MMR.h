#include <stdio.h>
#include <stdlib.h>

#define STR 30

//** Prototipos
int validNum(char txt[],int limi,int lims);


//** Cuerpos
int validNum(char txt[],int limi,int lims)
{
    char r[STR];
    int rint;
    do
    {
        printf("%s",txt);
        fflush(stdin); 
        gets(r);
        rint=atoi(r);
        if(rint<limi || rint>lims)
        {
            printf("Valor invalido, ingresalo de nuevo\n");
        }
    }while(rint<limi || rint>lims);
    return rint;
}
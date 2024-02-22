#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>

#define STR 30



typedef struct _datos
{
    int dia;
    int mes;
    int anio;
    int hora;
    int min;
}Tdato;

typedef struct _nodo
{  
    Tdato datos;
    struct _nodo *siguiente;
    struct _nodo *anterior;
}Tnodo;

typedef Tnodo* Tlista;

int validNum(char txt[],int limi,int lims);
int msgs(void);
void sistema(void);
void menu(void);
void agregarAlarma(Tlista &lista,tm **actual,int c);
int insertarAlarma(Tlista &lista,int c,Tnodo **nuevo);
int diaValid(int mes,int leap);
void insertarInicio(Tlista &lista,Tnodo **nuevo);
void insertarFin(Tlista &indice,Tnodo **nuevo);
void printList(Tnodo *lista);
void printAlarma(Tnodo *alarma);
void eliminarAlarma(Tlista &lista);
void insertarPos(Tlista &indice,Tnodo **nuevo);

int main(void)
{
    sistema();
    return 0;
}

int msgs(void)
{
    printf(" Alarmas\n\n");
    printf("1) Agregar Alarma");
    printf("\n2) Eliminar Alarma");
    printf("\n3) Editar Alarmas");
    printf("\n4) Ver alarmas");
    printf("\n5) Agregar sonido");
    printf("\n6) Salir\n");
    return (validNum("Escoge una opcion: ",1,8));
}

void sistema(void)
{
    Tlista lista=NULL;
    struct tm *actual;
    time_t t;
    int op;
    int c=0;
    char tecla;
    do
    {
        t = time(NULL);
        actual = localtime(&t);
        printf("Fecha actual: %02d/%02d/%d %d:%d \n", actual->tm_mday, actual->tm_mon + 1, actual->tm_year + 1900,actual->tm_hour,actual->tm_min);

        if(kbhit())
        {
            fflush(stdin);
            tecla=getch();
            if(tecla=='a')
            {
                agregarAlarma(lista,&actual,c);
                c++;
                printf("\nSe agrego una alarma correctamente\n");
                system("pause");
            }
            if(tecla=='n')
            {
                eliminarAlarma(lista);
                c--;
            }
            if(tecla=='b')
            {
                printList(lista);
                system("pause");
            }
        }

    }while(1);
}



void agregarAlarma(Tlista &lista,tm **actual,int c)
{
    Tnodo *nuevo=(Tnodo*)malloc(sizeof(Tnodo));
    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;

    int leap=0;
    int aniob=0;
    int mesb=0;
    int diab=0;
    int horab=0;
    
    int anio,mes;
    anio=(*actual)->tm_year+1900;
    mes=(*actual)->tm_mon+1;

    //año
    nuevo->datos.anio=validNum("Ingresa el año (cuatro digitos): ",anio,3000);

    if(nuevo->datos.anio==anio)
    {
        aniob=1;
    }

    //año bisiesto
    if((nuevo->datos.anio % 4) ==0)
    {
        leap=1;
    }

    //mes
    if(aniob)
    {
        nuevo->datos.mes=validNum("Ingresa el mes (dos digitos maximo): ",mes,12);
    }
    else
    {
        nuevo->datos.mes=validNum("Ingresa el mes (dos digitos maximo): ",1,12);
    }

    if(nuevo->datos.mes==mes)
    {
        mesb=1;
    }

    //dia
    if(aniob)
    {
        if(mesb)
        {
            nuevo->datos.dia=validNum("Ingresa el dia (dos cifras maximo): ",(*actual)->tm_mday,diaValid(nuevo->datos.mes,leap));
        }
        else
        {
            nuevo->datos.dia=validNum("Ingresa el dia (dos cifras maximo): ",1,diaValid(nuevo->datos.mes,leap));
        }
    }
    else
    {
        nuevo->datos.dia=validNum("Ingresa el dia (dos cifras maximo): ",1,diaValid(nuevo->datos.mes,leap));
    }
    
    if(nuevo->datos.dia==(*actual)->tm_mday)
    {
        diab=1;
    }

    //hora
    if(aniob)
    {
        if(mesb)
        {
            if(diab)
            {
                nuevo->datos.hora=validNum("Ingresa la hora (0-23): ",(*actual)->tm_hour,23);
            }
            else
            {
                nuevo->datos.hora=validNum("Ingresa la hora (0-23): ",0,23);
            }
        }
        else
        {
            nuevo->datos.hora=validNum("Ingresa la hora (0-23): ",0,23);
        }
    }
    else
    {
        nuevo->datos.hora=validNum("Ingresa la hora (0-23): ",0,23);
    }

    if(nuevo->datos.hora==(*actual)->tm_hour)
    {
        horab=1;
    }

    //minuto
    if(aniob)
    {
        if(mesb)
        {
            if(diab)
            {
                if(horab)
                {
                    nuevo->datos.min=validNum("Ingresa el minuto (0-59): ",(*actual)->tm_min,59);
                }
                else
                {
                    nuevo->datos.min=validNum("Ingresa el minuto (0-59): ",0,59);
                }
            }
            else
            {
                nuevo->datos.min=validNum("Ingresa el minuto (0-59): ",0,59);
            }
        }
        else
        {
            nuevo->datos.min=validNum("Ingresa el minuto (0-59): ",0,59);
        }
    }
    else
    {
        nuevo->datos.min=validNum("Ingresa el minuto (0-59): ",0,59);
    }

    insertarAlarma(lista,c,&nuevo);

}

int insertarAlarma(Tlista &lista,int c,Tnodo **nuevo)
{
    Tlista indice=lista;
    int jump=0;
    int salir = 0;
    if(lista==NULL)
    {
        insertarInicio(lista,nuevo);
        return 1;
    }


    while(!salir)
    {
        if((*nuevo)->datos.anio > indice->datos.anio)
        {
            if(indice->siguiente != NULL)
            {
                indice=indice->siguiente;
            }
            else
            {
                insertarFin(lista,nuevo);
                system("pause");
                return 1;
            }
        }
        else
        {
            if((*nuevo)->datos.anio == indice->datos.anio)
            {
                salir=1;
            }
            else
            {
                if(indice->anterior!=NULL)
                {
                    indice=indice->anterior;
                    insertarPos(indice,nuevo);
                    return 1;
                }
                else
                {
                    insertarInicio(lista,nuevo);
                    return 1;
                }
                
            }
        }

    }

    salir=0;
    while(!salir)
    {
        if((*nuevo)->datos.anio == indice->datos.anio)
        {
            if((*nuevo)->datos.mes > indice->datos.mes)
            {
                if(indice->siguiente != NULL)
                {
                    indice=indice->siguiente;
                }
                else
                {
                    insertarFin(lista,nuevo);
                    system("pause");
                    return 1;
                }
            }
            else
            {
                if((*nuevo)->datos.mes == indice->datos.mes)
                {
                    salir =1;
                }
                else
                {
                    if(indice->anterior!=NULL)
                    {
                        indice=indice->anterior;
                        insertarPos(indice,nuevo);
                        return 1;
                    }
                    else
                    {
                        insertarInicio(lista,nuevo);
                        return 1;
                    }
                }
                
            }
        }
    }

    salir=0;
    while(!salir)
    {
        if((*nuevo)->datos.anio == indice->datos.anio)
        {
            if((*nuevo)->datos.mes == indice->datos.mes)
            {
                if((*nuevo)->datos.dia > indice->datos.dia)
                {
                    if(indice->siguiente != NULL)
                    {
                        indice=indice->siguiente;
                    }
                    else
                    {
                        insertarFin(lista,nuevo);
                        system("pause");
                        return 1;
                    }
                }
                else
                {
                    if((*nuevo)->datos.dia == indice->datos.dia)
                    {
                        salir =1;
                    }
                    else
                    {
                        if(indice->anterior!=NULL)
                        {
                            indice=indice->anterior;
                            insertarPos(indice,nuevo);
                            return 1;
                        }
                        else
                        {
                            insertarInicio(lista,nuevo);
                            return 1;
                        }
                    }
                    
                }
            }
        }
    }

    salir=0;
    while(!salir)
    {
        if((*nuevo)->datos.anio == indice->datos.anio)
        {
            if((*nuevo)->datos.mes == indice->datos.mes)
            {
                if((*nuevo)->datos.dia == indice->datos.dia)
                {
                    if((*nuevo)->datos.hora > indice->datos.hora)
                    {
                        if(indice->siguiente != NULL)
                        {
                            indice=indice->siguiente;
                        }
                        else
                        {
                            insertarFin(lista,nuevo);
                            system("pause");
                            return 1;
                        }
                    }
                    else
                    {
                        if((*nuevo)->datos.dia == indice->datos.dia)
                        {
                            salir =1;
                        }
                        else
                        {
                            if(indice->anterior!=NULL)
                            {
                                indice=indice->anterior;
                                insertarPos(indice,nuevo);
                                return 1;
                            }
                            else
                            {
                                insertarInicio(lista,nuevo);
                                return 1;
                            }
                        }
                        
                    }
                }
            }
        }
    }

    salir=0;
    while(!salir)
    {
        if((*nuevo)->datos.anio == indice->datos.anio)
        {
            if((*nuevo)->datos.mes == indice->datos.mes)
            {
                if((*nuevo)->datos.dia == indice->datos.dia)
                {
                    if((*nuevo)->datos.hora == indice->datos.hora)
                    {
                        if((*nuevo)->datos.min > indice->datos.min)
                        {
                            if(indice->siguiente != NULL)
                            {
                                indice=indice->siguiente;
                            }
                            else
                            {
                                insertarFin(lista,nuevo);
                                system("pause");
                                return 1;
                            }
                        }
                        else
                        {
                            if((*nuevo)->datos.dia == indice->datos.dia)
                            {
                                salir =1;
                            }
                            else
                            {
                                if(indice->anterior!=NULL)
                                {
                                    indice=indice->anterior;
                                    insertarPos(indice,nuevo);
                                    return 1;
                                }
                                else
                                {
                                    insertarInicio(lista,nuevo);
                                    return 1;
                                }
                            }
                            
                        }
                    }
                }
            }
        }
    }
    /*
    if(c==1)
    {
        if((*nuevo)->)
    }
    if(indice->siguiente!=NULL)
    {
        while ((*nuevo)->datos.anio>indice->siguiente->datos.anio)
        {
            indice=indice->siguiente;
            jump++;
            if(jump==(c-1))
            {
                insertarFin(lista,nuevo);
                system("pause");
                return 1;
            }
        }
    }
    else
    {

    }

    

    if(indice->siguiente!=NULL)
    {
        while((*nuevo)->datos.anio == indice->siguiente->datos.anio)
        {
            if((*nuevo)->datos.mes>indice->siguiente->datos.mes)
            {
                indice=indice->siguiente;
                jump++;
                if(jump==(c-1))
                {
                    insertarFin(lista,nuevo);
                    system("pause");
                    return 1;
                }
            }
        }
    }

    if(indice->siguiente!=NULL)
    {
        while(indice->siguiente->datos.anio==(*nuevo)->datos.anio)
        {
            if((*nuevo)->datos.mes == indice->siguiente->datos.mes)
            {
                if((*nuevo)->datos.dia>indice->siguiente->datos.dia)
                {
                    indice=indice->siguiente;
                    jump++;
                    if(jump==(c-1))
                    {
                        insertarFin(lista,nuevo);
                        system("pause");
                        return 1;
                    }
                }
            }
        }
    }

    if(indice->siguiente!=NULL)
    {
        while(indice->siguiente->datos.anio==(*nuevo)->datos.anio)
        {
            if((*nuevo)->datos.mes == indice->siguiente->datos.mes)
            {
                if((*nuevo)->datos.dia == indice->siguiente->datos.dia)
                {
                    if((*nuevo)->datos.hora>indice->siguiente->datos.hora)
                    {
                        indice=indice->siguiente;
                        jump++;
                        if(jump==(c-1))
                        {
                            insertarFin(lista,nuevo);
                            system("pause");
                            return 1;
                        }
                    }
                }
            }
        }
    }

    if(indice->siguiente!=NULL)
    {
        while(indice->siguiente->datos.anio==(*nuevo)->datos.anio)
        {
            if((*nuevo)->datos.mes == indice->siguiente->datos.mes)
            {
                if((*nuevo)->datos.dia == indice->siguiente->datos.dia)
                {
                    if((*nuevo)->datos.hora == indice->siguiente->datos.hora)
                    {
                        if((*nuevo)->datos.min > indice->siguiente->datos.min)
                        {
                            indice=indice->siguiente;
                            jump++;
                            if(jump==(c-1))
                            {
                                insertarFin(lista,nuevo);
                                system("pause");
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    */
    printf("\nfin\n");
    system("pause");

    
    return 1;

}

void insertarInicio(Tlista &lista,Tnodo **nuevo)
{
    if(lista!=NULL)
    {
        (*nuevo)->siguiente=lista;
        lista->anterior=*nuevo;
        lista=*nuevo;
    }
    else
    {
        lista=*nuevo;
    }
}

//probar completo si no funciona
void insertarFin(Tlista &lista,Tnodo **nuevo)
{ 
    Tlista indice=lista;
    
    while (indice->siguiente!=NULL)
    {
        indice=indice->siguiente;
    }

    indice->siguiente=*nuevo;
    (*nuevo)->anterior=indice;
 
}

void insertarPos(Tlista &indice,Tnodo **nuevo)
{
    (*nuevo)->siguiente=indice->siguiente;
    indice->siguiente->anterior=*nuevo;
    (*nuevo)->anterior=indice;
    indice->siguiente=*nuevo;
}

void eliminarAlarma(Tlista &lista)
{
    Tlista indice=lista;
    char tecla='0';
    if(lista!=NULL)
    {
        
        system("cls");
        printAlarma(indice);
        printf("\na) Anterior d) Siguiente s) Salir");
        do
        {
            if(kbhit())
            {
                fflush(stdin);
                tecla=getch();
                if(tecla=='a')
                {
                    if(indice->anterior!=NULL)
                    {
                        indice=indice->anterior;
                        system("cls");
                        printAlarma(indice);
                        printf("\na) Anterior d) Siguiente s) Salir b) Eliminar");
                    }
                }
                if(tecla=='d')
                {
                    if(indice->siguiente!=NULL)
                    {
                        indice=indice->siguiente;
                        system("cls");
                        printAlarma(indice);
                        printf("\na) Anterior d) Siguiente s) Salir b) Eliminar");
                    }
                }
            }
            
        }while(tecla!='s' || tecla != 'b');
        
        if(tecla == 'b')
        {
            //falta aqui ***************************************************************************
        }
    }
    else
    {
        printf("\nNo hay alarmas\n");
        system("pause");
    }
}

void printList(Tnodo *lista)
{
    if(lista!=NULL)
    {
        Tlista indice=lista;
        
        printAlarma(indice);
        
        while (indice->siguiente!=NULL)
        {
            indice=indice->siguiente;
            printAlarma(indice);
        }
    }
    else
    {
        printf("\nNo hay alarmas\n");
        system("pause");
    }
}

void printAlarma(Tnodo *alarma)
{
    printf("\nAlarma\n\n");
    printf("Fecha: %02d/%02d/%d\n",alarma->datos.dia,alarma->datos.mes,alarma->datos.anio);
    printf("Hora: %02d:%02d\n",alarma->datos.hora,alarma->datos.min);
}

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

int diaValid(int mes,int leap)
{
    switch(mes)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
            break;
        case 2:
            if(leap==true)
            {
                return 29;
            }
            else
            {
                return 28;
            }
            break;
    }
}
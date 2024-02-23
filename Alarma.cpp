#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

//compilar con: g++ -o Alarma alarma.cpp -lwinmm -mconsole
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
void msgs(void);
void sistema(void);
void agregarAlarma(Tlista &lista,tm **actual,int c);
int insertarAlarma(Tlista &lista,int c,Tnodo **nuevo);
int diaValid(int mes,int leap);
void insertarInicio(Tlista &lista,Tnodo **nuevo);
void insertarFin(Tlista &indice,Tnodo **nuevo);
void printList(Tnodo *lista);
void printAlarma(Tnodo *alarma,int c);
void eliminarAlarma(Tlista &lista,int c);
void delAlarma(Tlista &lista, int i);
void modificarAlarma(Tlista &lista,tm *actual);
void editAlarma(Tnodo *indice,tm **actual,int i);
void insertarPos(Tlista &indice,Tnodo **nuevo);

int main(void)
{
    sistema();
    return 0;
}

void msgs(void)
{
    printf("\n\n Menu\n\n");
    printf("a) Agregar Alarma");
    printf("\nb) Eliminar Alarma");
    printf("\nc) Ver alarmas");
    printf("\nd) Modificar Alarma");
    printf("\ne) Salir\n");
    printf("Esoge una opcion: ");
}

void sistema(void)
{
    Tlista lista=NULL;
    struct tm *actual;
    time_t t;
    int op;
    int c=0;
    char tecla;

    msgs();
    do
    {
        t = time(NULL);
        actual = localtime(&t);
        //printf("Fecha actual: %02d/%02d/%d\n Hora actual: %d:%d \n", actual->tm_mday, actual->tm_mon + 1, actual->tm_year + 1900,actual->tm_hour,actual->tm_min);
        
        if(kbhit())
        {
            fflush(stdin);
            tecla=getch();
            if(tecla=='a')
            {
                system("cls");
                printf("Agregar alarma\n");
                agregarAlarma(lista,&actual,c);
                c++;
                printf("\nSe agrego una alarma correctamente\n\n");
                system("pause");
                system("cls");
                if(lista!=NULL)
                {
                    printf("Proxima alarma\n\n");
                    printf("Fecha: %02d/%02d/%d\nHora: %02d:%02d", lista->datos.dia, lista->datos.mes, lista->datos.anio, lista->datos.hora, lista->datos.min);
                }
                msgs();
            }
            if(tecla=='b')
            {
                eliminarAlarma(lista,c);
                c--;
                system("cls");
                if(lista!=NULL)
                {
                    printf("Proxima alarma\n\n");
                    printf("Fecha: %02d/%02d/%d\nHora: %02d:%02d", lista->datos.dia, lista->datos.mes, lista->datos.anio, lista->datos.hora, lista->datos.min);
                }
                msgs();
            }
            if(tecla=='c')
            {
                system("cls");
                printList(lista);
                printf("\n");
                system("pause");
                system("cls");
                if(lista!=NULL)
                {
                    printf("Proxima alarma\n\n");
                    printf("Fecha: %02d/%02d/%d\nHora: %02d:%02d", lista->datos.dia, lista->datos.mes, lista->datos.anio, lista->datos.hora, lista->datos.min);
                }
                msgs();
            }
            if(tecla == 'd')
            {
                modificarAlarma(lista,actual);
                system("cls");
                if(lista!=NULL)
                {
                    printf("Proxima alarma\n\n");
                    printf("Fecha: %02d/%02d/%d\nHora: %02d:%02d", lista->datos.dia, lista->datos.mes, lista->datos.anio, lista->datos.hora, lista->datos.min);
                }
                msgs();
            }
        }

        if(lista!= NULL)
        {
            if(lista->datos.anio<=actual->tm_year+1900)
            {
                if(lista->datos.mes <= actual->tm_mon+1)
                {
                    if(lista->datos.dia <= actual->tm_mday)
                    {
                        if(lista->datos.hora <= actual->tm_hour)
                        {
                            if(lista->datos.min <= actual->tm_min)
                            {
                                PlaySound(TEXT("C:"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                                printf("Alarma sonando\n\nPresiona x para detenerla\n");
                                if(kbhit)
                                {
                                    fflush(stdin);
                                    tecla=getch();
                                    if(tecla=='x')
                                    {
                                        delAlarma(lista,1);
                                        PlaySound(NULL, 0, 0);
                                        system("cls");
                                        if(lista!=NULL)
                                        {
                                            printf("Proxima alarma\n\n");
                                            printf("Fecha: %02d/%02d/%d\nHora: %02d:%02d", lista->datos.dia, lista->datos.mes, lista->datos.anio, lista->datos.hora, lista->datos.min);
                                        }
                                        msgs();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }while(tecla != 'e');
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
    nuevo->datos.anio=validNum("\n\nIngresa el año (cuatro digitos): ",anio,3000);

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

void eliminarAlarma(Tlista &lista,int c)
{
    Tlista indice=lista;
    int i=1;
    char tecla='0';
    if(lista!=NULL)
    {
        
        system("cls");
        printAlarma(indice,i);
        printf("\na) Anterior d) Siguiente s) Salir w) Eliminar");
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
                        i--;
                        system("cls");
                        printAlarma(indice,i);
                        printf("\na) Anterior d) Siguiente s) Salir w) Eliminar");
                    }
                }
                if(tecla=='d')
                {
                    if(indice->siguiente!=NULL)
                    {
                        indice=indice->siguiente;
                        i++;
                        system("cls");
                        printAlarma(indice,i);
                        printf("\na) Anterior d) Siguiente s) Salir w) Eliminar");
                    }
                }

                if(tecla == 'w')
                {
                    tecla = 's';
                    delAlarma(lista,i);
                    printf("\n\nSe elimino la alarma correctamente\n\n");
                    system("pause");
                }
            }
            
        }while(tecla!='s');
        
        
    }
    else
    {
        printf("\nNo hay alarmas\n");
        system("pause");
    }
}

void delAlarma(Tlista &lista, int i)
{
    i--;
    if(i==0)
    {
        Tnodo *temp=lista;
        if(lista->siguiente!=NULL)
        {
            lista=lista->siguiente;
            lista->anterior=NULL;
            free(temp);
            return;
        }
        else
        {
            free(temp);
            lista=NULL;
            return;
        }
        
    }

    int j;
    Tlista indice=lista;
    Tnodo *temp;
    for(j=0;j<i;j++)
    {
        indice=indice->siguiente;
    }

    
    if(indice->siguiente != NULL)
    {
        temp=indice;
        indice->siguiente->anterior=indice->anterior;
        indice->anterior->siguiente=indice->siguiente;
        free(temp);
        return;
    }
    else
    {
        temp=indice;
        indice->anterior->siguiente=NULL;
        free(temp);
        return;
    }
    
}

void modificarAlarma(Tlista &lista,tm *actual)
{
    Tlista indice=lista;
    int i=1;
    char tecla='0';
    if(lista!=NULL)
    {
        
        system("cls");
        printAlarma(indice,i);
        printf("\na) Anterior d) Siguiente s) Salir w) Modificar");
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
                        i--;
                        system("cls");
                        printAlarma(indice,i);
                        printf("\na) Anterior d) Siguiente s) Salir w) Modificar");
                    }
                }
                if(tecla=='d')
                {
                    if(indice->siguiente!=NULL)
                    {
                        indice=indice->siguiente;
                        i++;
                        system("cls");
                        printAlarma(indice,i);
                        printf("\na) Anterior d) Siguiente s) Salir w) Modificar");
                    }
                }

                if(tecla == 'w')
                {
                    tecla = 's';
                    editAlarma(indice,&actual,i);
                    printf("\n\nSe modifico la alarma correctamente\n\n");
                    system("pause");
                }
            }
            
        }while(tecla!='s');
    }
    else
    {
        printf("\nNo hay alarmas\n");
        system("pause");
    }
}

void editAlarma(Tnodo *indice,tm **actual,int i)
{
    int op=0;
    int leap;
    int aniob;
    int mesb;
    int diab;
    int horab;

    int anio,mes;
    anio=(*actual)->tm_year+1900;
    mes=(*actual)->tm_mon+1;

    if(indice->datos.anio==anio)
    {
        aniob=1;
    }
    else
    {
        aniob=0;
    }

    if((indice->datos.anio % 4) ==0)
    {
        leap=1;
    }
    else
    {
        leap=0;
    }
        
    if(indice->datos.mes==mes)
    {
        mesb=1;
    }
    else
    {
        mesb=0;
    }

    if(indice->datos.dia==(*actual)->tm_mday)
    {
        diab=1;
    }
    else
    {
        diab=0;
    }

    if(indice->datos.hora==(*actual)->tm_hour)
    {
        horab=1;
    }
    else
    {
        horab=0;
    }
    do
    {
        system("cls");
        printAlarma(indice,i);
        printf("\n1) Cambiar año\n");
        printf("2) Cambiar mes\n");
        printf("3) Cambiar dia\n");
        printf("4) Cambiar hora\n");
        printf("5) Cambiar minuto\n");
        printf("6) Salir\n");
        op=validNum("Escoge una opcion: ",1,6);
        system("cls");
        switch (op)
        {
            case 1:
                printAlarma(indice,i);
                printf("\n");
                indice->datos.anio=validNum("Año nuevo: ",anio,3000);
                if(indice->datos.anio==anio)
                {
                    aniob=1;
                }
                else
                {
                    aniob=0;
                }

                if((indice->datos.anio % 4) ==0)
                {
                    leap=1;
                }
                else
                {
                    leap=0;
                }
                break;
            case 2:
                printAlarma(indice,i);
                printf("\n");
                if(aniob)
                {
                    indice->datos.mes=validNum("Mes nuevo: ",mes,12);
                }
                else
                {
                    indice->datos.mes=validNum("Mes nuevo: ",1,12);
                }

                if(indice->datos.mes==mes)
                {
                    mesb=1;
                }
                else
                {
                    mesb=0;
                }
                break;
            case 3:
                printAlarma(indice,i);
                printf("\n");
                if(aniob)
                {
                    if(mesb)
                    {
                        indice->datos.dia=validNum("Dia nuevo: : ",(*actual)->tm_mday,diaValid(indice->datos.mes,leap));
                    }
                    else
                    {
                        indice->datos.dia=validNum("Dia nuevo: : ",1,diaValid(indice->datos.mes,leap));
                    }
                }
                else
                {
                    indice->datos.dia=validNum("Dia nuevo: : ",1,diaValid(indice->datos.mes,leap));
                }
                
                if(indice->datos.dia==(*actual)->tm_mday)
                {
                    diab=1;
                }
                else
                {
                    diab=0;
                }
                break;
            case 4:
                printAlarma(indice,i);
                printf("\n");
                if(aniob)
                {
                    if(mesb)
                    {
                        if(diab)
                        {
                            indice->datos.hora=validNum("Hora nueva: ",(*actual)->tm_hour,23);
                        }
                        else
                        {
                            indice->datos.hora=validNum("Hora nueva: ",0,23);
                        }
                    }
                    else
                    {
                        indice->datos.hora=validNum("Hora nueva: ",0,23);
                    }
                }
                else
                {
                    indice->datos.hora=validNum("Hora nueva: ",0,23);
                }

                if(indice->datos.hora==(*actual)->tm_hour)
                {
                    horab=1;
                }
                else
                {
                    horab=0;
                }
                break;
            case 5:
                printAlarma(indice,i);
                printf("\n");
                if(aniob)
                {
                    if(mesb)
                    {
                        if(diab)
                        {
                            if(horab)
                            {
                                indice->datos.min=validNum("Minuto nuevo: ",(*actual)->tm_min,59);
                            }
                            else
                            {
                                indice->datos.min=validNum("Minuto nuevo: ",0,59);
                            }
                        }
                        else
                        {
                            indice->datos.min=validNum("Minuto nuevo: ",0,59);
                        }
                    }
                    else
                    {
                        indice->datos.min=validNum("Minuto nuevo: ",0,59);
                    }
                }
                else
                {
                    indice->datos.min=validNum("Minuto nuevo: ",0,59);
                }
                break;
        }
    } while (op!=6);
                    
}

//mostrar
void printList(Tnodo *lista)
{
    int i=1;
    if(lista!=NULL)
    {
        Tlista indice=lista;
        
        printAlarma(indice,i);
        
        while (indice->siguiente!=NULL)
        {
            indice=indice->siguiente;
            i++;
            printAlarma(indice,i);
        }
    }
    else
    {
        printf("\nNo hay alarmas\n");
        system("pause");
    }
}

void printAlarma(Tnodo *alarma,int c)
{
    printf("\nAlarma %d\n",c);
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
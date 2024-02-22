/*

Ramón Mejía Martínez 372099
6 de febrero de 2024
Estructura de datos, laboratorio diagnostico
Listas enlazadas simples, operaciones basicas

*/
#include "MMR.h"

typedef struct _datos{
    int matricula;
    char apPat[30];
    char apMat[30];
    char nombre[30];
}Tdato;

typedef struct _nodo{
    Tdato datos;
    struct _nodo *ptr;
}Tnodo;

int numElementos(Tnodo *lista);
void obtenDatos(Tnodo **nodo);
void insertarInicio(Tnodo **lista);
void insertarFin(Tnodo **lista);
int insertarPos(Tnodo **lista,int pos);
int delPos(Tnodo **lista,int pos);
void printList(Tnodo *lista);
Tnodo *creaNodo(void);
void printTab(Tnodo *nodo);
int buscar(Tnodo *lista,int num);
void menu(void);
int msgs(void);

int main()
{
    menu();
    return 0;
}

int msgs(void)
{
    printf(" Menu\n\n");
    printf("1) Insertar elemento en posicion");
    printf("\n2) Insertar elemento en inicio");
    printf("\n3) Insertar elemento en final");
    printf("\n4) Eliminar elemento");
    printf("\n5) Buscar y recuperar elemento");
    printf("\n6) Recorrer lista e imprimir");
    printf("\n7) Obtener cantidad de elementos");
    printf("\n8) Salir\n");
    return (validNum("Escoge una opcion: ",1,8));
}

void menu(void)
{
    Tnodo *lista=NULL;
    int c=0;
    int op;
    int pos;
    int orden=0;
    do
    {
        system("cls");
        op=msgs();
        system("cls");
        
        switch(op)
        {
            case 1:
                printf("Insertar elemento al inicio de la lista\n\n");
                pos=validNum("Ingresa la posicion: ",0,c);
                insertarPos(&lista,pos);
                c++;
                break;
            case 2:
                printf("Insertar elemento al inicio de la lista\n\n");
                insertarInicio(&lista);
                c++;
                break;
            case 3:
                printf("Insertar elemento al final de la lista\n\n");
                insertarFin(&lista);
                c++;
                break;
            case 4:
                printf("Eliminar elemento de la lista\n\n");
                pos=validNum("Ingresa la posicion: ",0,c);
                if(delPos(&lista,pos)!=-1)
                {
                    c--;
                }
                break;
            case 5:
                printf("Buscar elemento\n\n");
                pos=validNum("Ingresa la matricula que deseas buscar: ",300000,399999);
                if(buscar(lista,pos)==-1)
                {
                    printf("\nNo se encontro esa matericula\n");
                }
                break;
            case 6:
                if(c!=0)
                {
                    printf("Lista\n\n");
                    printList(lista);
                }
                else
                {
                    printf("No hay elementos en la lista\n\n");
                }
                break; 
            case 7:
                printf("Cantidad de elementos\n\n");
                printf("La lista tiene %d elementos\n\n",numElementos(lista));
                break;
        }
        system("pause");
    } while (op!=8);
}

int numElementos(Tnodo *lista)
{
    int i=0;
    if(lista!=NULL)
    {
        Tnodo *tempPtr=lista;

        i++;
        while (tempPtr->ptr!=NULL)
        {
            tempPtr=tempPtr->ptr;
            i++;
        }
    }
    return i;
}

Tnodo *creaNodo(void)
{
    Tnodo *nuevo=(Tnodo*)malloc(sizeof(Tnodo));
    if(nuevo!=NULL)
    {
        obtenDatos(&nuevo);
        nuevo->ptr=NULL;
        return nuevo;
    }
    else
    {
        return NULL;
    }
}

void obtenDatos(Tnodo **nodo)
{
    (*nodo)->datos.matricula=validNum("Ingresa la matricula: ",300000,399999);
    printf("Ingresa el nombre: ");
    fflush(stdin);
    gets((*nodo)->datos.nombre);
    printf("Ingresa el apellido paterno: ");
    fflush(stdin);
    gets((*nodo)->datos.apPat);
    printf("Ingresa el apellido materno: ");
    fflush(stdin);
    gets((*nodo)->datos.apMat);
}

void insertarInicio(Tnodo **lista)
{
    Tnodo *nuevo=creaNodo();

    if(nuevo!=NULL)
    {
        nuevo->ptr=*lista;
        *lista=nuevo;
    }
    else
    {
        printf("\nNo se asigno la memoria\n");
    }
}

void insertarFin(Tnodo **lista)
{
    Tnodo *tempList=*lista;
    Tnodo *nuevo=creaNodo();

    if(nuevo!=NULL)
    {
        while (tempList->ptr!=NULL)
        {
            tempList=tempList->ptr;
        }
        tempList->ptr=nuevo;
    }
    else
    {
        printf("\nNo se asigno la memoria\n");
    }
}

int insertarPos(Tnodo **lista,int pos)
{
    if(pos==0)
    {
        insertarInicio(lista);
        return pos;
    }

    int i=0;
    Tnodo *tempList=*lista;
    Tnodo *nuevo=creaNodo();

    for(i=0;i<pos-1;i++)
    {
        if(tempList->ptr!=NULL)
        {
            tempList=tempList->ptr;
        }
        else
        {
            return -1;
        }
    }

    nuevo->ptr=tempList->ptr;
    tempList->ptr=nuevo;
    return i+1;
}

int delPos(Tnodo **lista, int pos)
{

    if(pos==0)
    {
        Tnodo *temp=*lista;
        *lista=(*lista)->ptr;
        free(temp);
        return pos;
    }

    int i=0;
    Tnodo *tempList=*lista;

    for(i=0;i<pos-1;i++)
    {
        if(tempList->ptr!=NULL)
        {
            tempList=tempList->ptr;
        }
        else
        {
            return -1;
        }
    }

    if(tempList->ptr!=NULL)
    {
        if(tempList->ptr->ptr==NULL)
        {
            free(tempList->ptr);
            tempList->ptr=NULL;
            return i+1;
        }   
        else
        {
            Tnodo *temp;
            temp=tempList->ptr;
            tempList->ptr=tempList->ptr->ptr;
            free(temp);
            return i+1;
        }
    }
    return -1;
}

void printList(Tnodo *lista)
{
    int i=0;
    if(lista!=NULL)
    {
        Tnodo *tempPtr=lista;
        printf("| MATRICULA |        NOMBRE        |     APELLIDO PATERNO     |     APELLIDO MATERNO     |\n");
        printTab(tempPtr);
        
        while (tempPtr->ptr!=NULL)
        {
            tempPtr=tempPtr->ptr;
            printTab(tempPtr);
        }
    }
    else
    {
        printf("\nLa lista esta vacia\n");
    }
}

void printTab(Tnodo *nodo)
{
    printf("| %-9d | %-20s | %-24s | %-24s |\n",nodo->datos.matricula,nodo->datos.nombre,nodo->datos.apPat,nodo->datos.apMat);
}

int buscar(Tnodo *lista,int num)
{
    if(lista!=NULL)
    {
        Tnodo *tempPtr=lista;
        int i=0;
        do
        {
            if(tempPtr->datos.matricula==num)
            {
                printf("| MATRICULA |        NOMBRE        |     APELLIDO PATERNO     |     APELLIDO MATERNO     |\n");
                printTab(tempPtr);
                return num;
            }
            tempPtr=tempPtr->ptr;
            i++;
        }while (tempPtr->ptr!=NULL);
    }
    return -1;
}
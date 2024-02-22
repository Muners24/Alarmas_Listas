#include <stdio.h>
#include <stdlib.h>

#define STR 30



typedef struct _datos
{
    int num;
}Tdato;

typedef struct _nodo
{  
    Tdato datos;
    struct _nodo *siguiente;
    struct _nodo *anterior;
}Tnodo;

typedef Tnodo* Tlista;


int validNum(char txt[],int limi,int lims);
Tnodo *creaNodo(void);
void obtenDatos(Tnodo **nodo);
void printList(Tnodo *lista);
void insertarInicio(Tlista &lista);
void insertarFin(Tlista &lista);
int insertarPos(Tlista &lista,int pos,int num);

int main()
{
    Tlista lista=NULL;
    int c=0;

    insertarInicio(lista);
    
    printList(lista);
    printList(lista);
    printList(lista);
    return 0;
}

Tnodo *creaNodo(void)
{
    Tnodo *nuevo=(Tnodo*)malloc(sizeof(Tnodo));
    if(nuevo!=NULL)
    {
        obtenDatos(&nuevo);
        nuevo->siguiente=NULL;
        nuevo->anterior=NULL;
        return nuevo;
    }
    else
    {
        return NULL;
    }
}

void obtenDatos(Tnodo **nodo)
{
    char n;
    (*nodo)->datos.num=validNum("Ingrese un numero: ",0,30);
}

void insertarInicio(Tlista &lista)
{
    Tnodo *nuevo=creaNodo();

    if(nuevo!=NULL)
    {
        if(lista!=NULL)
        {
            nuevo->siguiente=lista;
            lista->anterior=nuevo;
            lista=nuevo;
        }
        else
        {
            lista=nuevo;
        }
    }
    else
    {
        printf("\nNo se asigno la memoria\n");
    }
}

void printList(Tnodo *lista)
{
    int i=0;
    if(lista!=NULL)
    {
        Tlista indice=lista;
        
        printf("%d ",indice->datos.num);
        
        while (indice->siguiente!=NULL)
        {
            indice=indice->siguiente;
            printf("%d ",indice->datos.num);
        }
    }
    else
    {
        printf("\nLa lista esta vacia\n");
    }
}

void insertarFin(Tlista &lista)
{
    Tlista indice=lista;
    
    
    if(lista!=NULL)
    {
        Tnodo *nuevo=creaNodo();
        if(nuevo!=NULL)
        {
            while (indice->siguiente!=NULL)
            {
                indice=indice->siguiente;
            }
            indice->siguiente=nuevo;
            nuevo->anterior=indice;
        }
        else
        {
            printf("\nNo se asigno la memoria\n");
        }
    }
    else
    {
        insertarInicio(lista);
    }
}

//validar entrada positiva
int insertarPos(Tlista &lista,int pos,int num)
{
    if(pos==0)
    {
        insertarInicio(lista);
        return pos;
    }
    
    if(pos==(num))
    {
        insertarFin(lista);
        return pos;
    }

    int i=0;
    Tlista indice=lista;
    Tnodo *nuevo=creaNodo();

    for(i=0;i<pos-1;i++)
    {
        if(indice->siguiente!=NULL)
        {
            indice=indice->siguiente;
        }
        else
        {
            free(nuevo);
            return -1;
        }
    }
    
    nuevo->siguiente=indice->siguiente;
    indice->siguiente->anterior=nuevo;
    nuevo->anterior=indice;
    indice->siguiente=nuevo;

    return pos;
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
#include <stdio.h>
#include <stdlib.h>

struct
{
    int TareaId;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
    int Estado;
} typedef Tarea;

struct
{
    Tarea T;          // Aputa a la tarea en la que se encuentra el nodo
    TNodo *Siguiente; // Mi nodo apunta al siguiente elemento de la lista
} typedef TNodo;

TNodo *CrearListaVacia()
{
    return NULL;
}

TNodo *CrearNodo(Tarea *T, int ID, char *Descripcion, int Duracion)
{ // Creamos el nodo de la lista enlazada
    TNodo *NNodo = (TNodo *)malloc(sizeof(TNodo));
    NNodo->T.TareaId = ID;
    NNodo->T.Descripcion = Descripcion;
    NNodo->T.Duracion = Duracion;
    NNodo->T.Estado = 0;
    NNodo->Siguiente = NULL;

    return NNodo;
}

void InsertarNodo(TNodo **Star, TNodo *Nodo)
{ // Insertamos al inicio de la lista en manera de stack
    Nodo->Siguiente = *Star;
    *Star = Nodo;
}

TNodo *buscarNodo(TNodo *Star, int ID)
{
    TNodo *Aux = Star;
    while (Aux && Aux->T.TareaId != ID)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}

TNodo *QuitarNodo(TNodo *Star, Tarea dato)
{
    TNodo **aux = Star;
    while (*aux != NULL && (*aux)->T != dato)
    {
        aux = &(*aux)->Siguiente;
    }
    if (*aux)
    {
        TNodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
        return temp;
    }
    return NULL;
}

void EliminarNodo(TNodo *nodo)
{
    if (nodo)
        free(nodo);
}

int main()
{
    TNodo *Star; // Mi nodo apunta al primer elemento de la lista
    Star = CrearListaVacia();
    int opciones = 0;
    // Interfaz
    while (opciones != 6)
    {
        printf("---------------------------------");
        printf("\n-----------Bienvenido-----------\n");
        printf("---------------------------------");
        printf("Digite una de las siguentes opciones\n");
        printf("1 Listar tareas\n");
        printf("2 Crear tarea\n");
        printf("3 Cambiar estado de la tarea\n");
        printf("4 Buscar tarea por ID\n");
        printf("5 Buscar tarea por palabra clave\n");
        printf("6 Salir\n");
        scanf("%d", &opciones);
        switch (opciones)
        {
        case 1:
            printf("A seleccionado \"Listar tareas\" \n");
            
            break;
        case 2:
            printf("A seleccionado \"Crear tareas\" \n");
            break;
        case 3:
            printf("A seleccionado \"Cambiar estado\" \n");
            break;
        case 4:
            printf("A seleccionado \"Buscar tarea por ID\" \n");
            break;
        case 5:
            printf("A seleccionado \"Buscar tarea por palabra clave\" \n");
            break;
        case 6:
            char sn;
            printf("A seleccionado \"Salir\" \n");
            printf("¿Esta seguro? (s/n)\n");
            scanf("%c", &sn);
            if (sn == 's' || sn == 'S')
            {
                opciones = 6;
            }
            break;
        default:
            break;
        }
    }

    return 0;
}
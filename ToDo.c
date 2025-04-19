#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct
{
    int TareaId;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
    int Estado;
} typedef Tarea;

struct TNodo
{
    Tarea T;
    struct TNodo *Siguiente;
};
typedef struct TNodo TNodo;

int id()
{
    static int id = 1000;
    return id++;
}

TNodo *CrearListaVacia()
{
    return NULL;
}

TNodo *CrearNodo(int ID, char *descripcion, int Duracion)
{ // Creamos el nodo de la lista enlazada
    TNodo *NNodo = (TNodo *)malloc(sizeof(TNodo));
    NNodo->T.TareaId = ID;
    NNodo->T.Descripcion = (char *)malloc(strlen(descripcion) + 1);
    strcpy(NNodo->T.Descripcion, descripcion);
    NNodo->T.Duracion = Duracion;
    NNodo->T.Estado = 0;
    NNodo->Siguiente = NULL;

    return NNodo;
}

void InsertarNodo(TNodo **Start, TNodo *Nodo);

void CrearTarea(TNodo **Start);

TNodo *buscarNodo(TNodo *Start, int ID)
{
    TNodo *Aux = Start;
    while (Aux && Aux->T.TareaId != ID)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}
TNodo *buscarNodoPalabra(TNodo *Start, char *Palabra)
{
    TNodo *Aux = Start;
    while (Aux && strstr(Aux->T.Descripcion, Palabra) == NULL)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}

TNodo *QuitarNodo(TNodo **Start, int ID)
{
    TNodo **aux = Start;
    while (*aux != NULL && (*aux)->T.TareaId != ID)
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
void MostrarTareas(TNodo **nodo);
void MostrarTarea(TNodo *Start, int ID);
void EliminarNodo(TNodo *nodo);
void CambiarEstado(TNodo **Start, TNodo **Start2, int ID);
int main()
{
    TNodo *Start;           // Mi nodo apunta al primer elemento de la lista
    TNodo *StartRealizadas; // Mi nodo apunta al primer elemento de la lista de realizadas
    Start = CrearListaVacia();
    StartRealizadas = CrearListaVacia();
    int opciones = 0;
    // Interfaz
    while (opciones != 6)
    {
        printf("---------------------------------\n");
        printf("-----------Bienvenido-----------\n");
        printf("---------------------------------\n");
        printf("Digite una de las siguentes opciones\n");
        printf("1 Listar tareas\n");
        printf("2 Crear tarea\n");
        printf("3 Cambiar estado de la tarea\n");
        printf("4 Buscar tarea por ID\n");
        printf("5 Buscar tarea por palabra clave\n");
        printf("6 Salir\n");
        scanf(" %d", &opciones);
        switch (opciones)
        {
        case 1:
        {
            int continuar;
            do
            {
                int subOpcion = 0;
                printf("A seleccionado \"LiStart tareas\" \n");
                printf("Porfavor elija: \n 1 Mostrar todas las tareas \n 2 Mostrar las Tareas Pendientes \n 3 Mostrar las Tareas Realizadas\n");
                scanf(" %d", &subOpcion);
                if (subOpcion == 1)
                {
                    MostrarTareas(&Start);
                    MostrarTareas(&StartRealizadas);
                }
                else if (subOpcion == 2)
                {
                    MostrarTareas(&Start); // Pendientes
                }
                else
                {
                    MostrarTareas(&StartRealizadas);
                }
                printf("¿Desea salir? 1: SI 2: NO\n");
                scanf(" %d", &continuar);

            } while (continuar != 1);
            break;
        }
        case 2:
            printf("A seleccionado \"Crear tareas\" \n");
            CrearTarea(&Start);
            break;
        case 3:
        {
            int IDSeleccionado;
            printf("A seleccionado \"Cambiar estado\" \n");
            printf("Porfavor Digite el ID de la Tarea\n");
            scanf("%d", &IDSeleccionado);
            CambiarEstado(&Start, &StartRealizadas, IDSeleccionado);
            break;
        }
        case 4:
        {
            int IDSeleccionado;
            TNodo *Aux;
            printf("A seleccionado \"Buscar tarea por ID\" \n");
            printf("Porfavor Digite el ID de la Tarea\n");
            scanf("%d", &IDSeleccionado);

            Aux = buscarNodo(Start, IDSeleccionado);
            if (!Aux)
            {
                Aux = buscarNodo(StartRealizadas, IDSeleccionado);
            }
            else
            {
                printf("Tarea no existente\n");
            }
        }

        break;
        case 5:
        {
            TNodo *Aux;
            char Palabra[20];
            printf("A seleccionado \"Buscar tarea por palabra clave\" \n");
            printf("Porfavor ingese la palabra");
            gets(Palabra);
            Aux = buscarNodoPalabra(Start, Palabra);
            if (Aux != NULL)
            {
                int ID = Aux->T.TareaId;
                MostrarTarea(Aux, ID);
            }
            else
            {
                printf("No se encontró ninguna tarea con esa palabra clave.\n");
            }
            break;
        }
        case 6:
        {
            int continuar;
            printf("Ha seleccionado \"Salir\" \n");
            printf("¿Está seguro? 1:Si 2:No \n");
            scanf(" %d", &continuar);
            if (continuar != 1)
            {
                opciones = 6;
                printf("\nADIOS");
            }
            break;
        }
        }
    }

    return 0;
}

void InsertarNodo(TNodo **Start, TNodo *Nodo)
{ // Insertamos al inicio de la lista en manera de stack
    Nodo->Siguiente = *Start;
    *Start = Nodo;
    printf("Nodo insertado");
}

void CrearTarea(TNodo **Start)
{
    int continuar = 0;
    char descripcion[200];

    int duracion = 0;
    do
    {
        fflush(stdin);
        printf("Ingrese los datos de la tarea \n");
        printf("Descripcion : ");
        gets(descripcion); // fgets
        fflush(stdin);
        printf("Ingrese una duracion entre 10 y 100: ");
        scanf(" %d", &duracion);
        fflush(stdin);
        TNodo *Aux = CrearNodo(id(), descripcion, duracion);
        InsertarNodo(Start, Aux);
        printf("---------------------------------\n");
        printf("¿Desea agregar otra tarea? 1:Si 2:No\n");
        scanf(" %d", &continuar);

    } while (continuar == 1);
}

void MostrarTareas(TNodo **nodo)
{
    TNodo *Aux = *nodo; // Para asignar un puntero doble a uno simple le quito un * , desreferenciacion
    while (Aux)
    {
        printf("\n");
        printf("Id de la tarea: %d \n", Aux->T.TareaId);
        printf("Descripcion: \n ");
        puts(Aux->T.Descripcion);
        printf("Duracion de la tarea: %d \n", Aux->T.Duracion);
        printf("Estado de la tarea: ");
        if (Aux->T.Estado == 1)
        {
            printf("Realizada");
        }
        else
        {
            printf("Pendiente");
        }
        printf("\n-----------SIGUIENTE-------------\n");
        Aux = Aux->Siguiente;
    }
    printf("\nFin de las tareas\n");
}
void MostrarTarea(TNodo *Start, int ID)
{
    TNodo *Aux = buscarNodo(Start, ID);
    printf("\n");
    printf("Id de la tarea: %d \n", Aux->T.TareaId);
    printf("Descripcion: \n ");
    puts(Aux->T.Descripcion);
    printf("Duracion de la tarea: %d \n", Aux->T.Duracion);
    printf("Estado de la tarea: ");
    if (Aux->T.Estado == 1)
    {
        printf("Realizada");
    }
    else
    {
        printf("Pendiente");
    }
}

void EliminarNodo(TNodo *nodo)
{
    if (nodo)
        free(nodo);
}
void CambiarEstado(TNodo **Start, TNodo **Start2, int ID)
{
    TNodo *NodoAMover = QuitarNodo(Start, ID);
    if (NodoAMover)
    {
        InsertarNodo(Start2, NodoAMover);
        printf("Tarea ID: %d , Fue Movida", ID);
    }
    else
    {
        printf("Tarea no %d no existe", ID);
    }
}
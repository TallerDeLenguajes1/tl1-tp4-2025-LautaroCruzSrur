#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct
{
    int TareaId;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
    int Estado;        // Estado en la que se encuentra la tarea : "0 Pendiente" , "1 Realizada"
} typedef Tarea;

struct TNodo
{
    Tarea T;
    struct TNodo *Siguiente;
};
typedef struct TNodo TNodo;

int id() // Funcion para ir aumentando el id
{
    static int id = 1000;
    return id++;
}

TNodo *CrearListaVacia() // Creamos la lista vacia para que inicialice la lista apuntando a NULL
{
    return NULL;
}

TNodo *CrearNodo(int ID, char *descripcion, int Duracion)
{                                                                   // Creamos el nodo de la lista enlazada
    TNodo *NNodo = (TNodo *)malloc(sizeof(TNodo));                  // Hacemos una reserva de MD para almacenar un nodo
    NNodo->T.TareaId = ID;                                          // Introducimos su ID
    NNodo->T.Descripcion = (char *)malloc(strlen(descripcion) + 1); // Hacemos reserva de DM para la descripcion
    strcpy(NNodo->T.Descripcion, descripcion);                      // Introducimos la descripcion al nodo
    NNodo->T.Duracion = Duracion;                                   // Introducimos la duracion
    NNodo->T.Estado = 0;                                            // Igualamos el estado a 0 para que este pendiente
    NNodo->Siguiente = NULL;                                        // Y hacemos que el siguiente del nodo apunte a null

    return NNodo;
}

void InsertarNodo(TNodo **Start, TNodo *Nodo);

void CrearTarea(TNodo **Start);

TNodo *buscarNodo(TNodo *Start, int ID) // Buscamos un nodo en la lista por su ID
{
    TNodo *Aux = Start;                 // Guardamos la cabecera en un auxiliar
    while (Aux && Aux->T.TareaId != ID) // Recorremos la lista buscando que AUX != NULL y el ID no coincida
    {
        Aux = Aux->Siguiente; // Si el id no coincide y no es null apuntamos al siguiente
    }
    return Aux; // Si encuentra la coincidencia retornamos el Nodo Aux
}
TNodo *buscarNodoPalabra(TNodo *Start, char *Palabra)
{
    TNodo *Aux = Start; // Guardamos la cabecera en un auxiliar
    while (Aux && strstr(Aux->T.Descripcion, Palabra) == NULL)
    {                         // Siempre que el auxiliar != NULL y la comparacion del nodo con la palabra sea NULL
        Aux = Aux->Siguiente; // Apuntamos al siguiente Nodo
    }
    return Aux; // Si lo encuentra , retorna el Nodo Aux
}

TNodo *QuitarNodo(TNodo **Start, int ID) // Para quitar nodo necesitamos un puntero doble
{                                        // Un puntero doble almacena la direccion de memoria de otro puntero que apunta a una variable.
    TNodo **aux = Start;                 // Almacenamos esa direccion de memoria con un puntero doble
    while (*aux != NULL && (*aux)->T.TareaId != ID)
    {                             // Si el puntero es distinto de NULL y al acceder a los datos de Tarea con el puntero es distinto al ID
        aux = &(*aux)->Siguiente; // Apuntamos la direccion de memoria de siguiente
    }
    if (*aux) // Y si se encuentra el puntero por ID
    {
        TNodo *temp = *aux;       // Guardamos el auxiliar en un temporal
        *aux = (*aux)->Siguiente; // Hacemos que el auxiliar apunte al siguiente
        temp->Siguiente = NULL;   // Y que el temporal apunte a null para sacarlo de la lista
        return temp;              // Retornamos el temporal
    }
    return NULL; // Si el aux no existe retornamos NULL y la lista no se modifica
}
void MostrarTareas(TNodo **nodo);
void MostrarTarea(TNodo *Start, int ID);
void EliminarNodo(TNodo *nodo);
void CambiarEstado(TNodo **Start, TNodo **Start2, int ID);
int main()
{
    TNodo *Start;                        // Mi nodo apunta al primer elemento de la lista
    TNodo *StartRealizadas;              // Mi nodo apunta al primer elemento de la lista de realizadas
    Start = CrearListaVacia();           // Inicializamos la lista
    StartRealizadas = CrearListaVacia(); // Inicializamos la lista
    int opciones = 0;
    // Interfaz
    while (opciones != 6)
    {
        printf("\n---------------------------------\n");
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
            fflush(stdin);
            printf("A seleccionado \"Buscar tarea por palabra clave\" \n");
            printf("Porfavor ingrese la palabra :  ");
            gets(Palabra);
            fflush(stdin);
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

void InsertarNodo(TNodo **Start, TNodo *Nodo) // star es la cabezera y nodo es el que insertamos
{                                             // Insertamos al inicio de la lista en manera de stack
    Nodo->Siguiente = *Start;                 // Hacemos que el sigiente de nodo(el que insertamos) apunte a la cabezera
    *Start = Nodo;                            // Y Hacemos que la cabezera se convierta en el nodo que insertamos
    printf("Nodo insertado");
} // Esta funcion inserta los nodos al inicio de la lista(...5,4,3,2,1,0)

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
        TNodo *Aux = CrearNodo(id(), descripcion, duracion); // Creamos un nodo para poder insertarlo
        InsertarNodo(Start, Aux);                            // Utilizamos la funcion insertar Nodo
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
        Aux = Aux->Siguiente; // Apuntamos al siguiente de la lista
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
    if (nodo)       // Si existe
        free(nodo); // Liberamos la memoria del nodo
}
void CambiarEstado(TNodo **Start, TNodo **Start2, int ID)
{                                              // Star es el nodo que buscamos en la lista 1 , star 2 es la lista 2
    TNodo *NodoAMover = QuitarNodo(Start, ID); // Buscamos el nodo que necesitamos mover
    if (NodoAMover)                            // Si existe
    {
        InsertarNodo(Start2, NodoAMover); // Lo incertamos en la nueva lista
        printf("Tarea ID: %d , Fue Movida", ID);
    }
    else
    {
        printf("Tarea no %d no existe", ID);
    }
}
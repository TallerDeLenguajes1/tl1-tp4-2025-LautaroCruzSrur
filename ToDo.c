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

struct
{
    Tarea T;          // Aputa a la tarea en la que se encuentra el nodo
    TNodo *Siguiente; // Mi nodo apunta al siguiente elemento de la lista
} typedef TNodo;

int id()
{
    static int id = 1000;
    return id++;
}

TNodo *CrearListaVacia()
{
    return NULL;
}

TNodo *CrearNodo(int ID, char *Descripcion, int Duracion)
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

void CrearTarea(TNodo *Star){
    char continuar;
    char descripcion[100];
    int duracion = 0;
    do{
        printf("Ingrese los datos de la tarea \n");
        printf("Descripcion : ");
        gets(descripcion);
        fflush(stdin);
        printf("Ingrese una duracion entre 10 y 100: ");
        scanf("%d", &duracion);
        fflush(descripcion);
        InsertarNodo(Star,CrearNodo(id(),descripcion, duracion ));
        printf("---------------------------------");
        printf("¿Desea agregar otra tarea?");
        scanf("%c", continuar);
        fflush(stdin);
        
    } while (continuar == 'n' || continuar == 'N');
    
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

TNodo *QuitarNodo(TNodo *Star, int ID)
{
    TNodo **aux = Star;
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
void MostarTareas(TNodo *nodo){
    TNodo *Aux = nodo;
    while (Aux != NULL){
    printf("\n");
    printf("Id de la tarea: %d \n", Aux->T.TareaId);
    printf("Descripcion: \n ");
    puts(Aux->T.Descripcion);
    printf("Duracion de la tarea: %d \n", Aux->T.Duracion);
    printf("Estado de la tarea: ");
    if(Aux->T.Estado == 1)
    {
        printf("Realizada");
    }else{
        printf("Pendiente");
    } 
    printf("-----------SIGUIENTE-------------");
    Aux = Aux->Siguiente;
    }   
}
void MostarTarea(TNodo *Star , int ID){
    TNodo *Aux = buscarNodo(Star , ID);
    printf("\n");
    printf("Id de la tarea: %d \n", Aux->T.TareaId);
    printf("Descripcion: \n ");
    puts(Aux->T.Descripcion);
    printf("Duracion de la tarea: %d \n", Aux->T.Duracion);
    printf("Estado de la tarea: ");
    if(Aux->T.Estado == 1)
    {
        printf("Realizada");
    }else{
        printf("Pendiente");
    } 

}

void EliminarNodo(TNodo *nodo)
{
    if (nodo)
        free(nodo);
}
void CambiarEstado(TNodo *Star, TNodo *Star2, int ID){
    TNodo *Aux = buscarNodo(Aux , ID);
    InsertarNodo(Star2, Aux );
    EliminarNodo(QuitarNodo(Star,ID));
    printf("Tarea ID: %D , Fue Movida" , ID);
}
int main()
{
    TNodo *Star;// Mi nodo apunta al primer elemento de la lista
    TNodo *StarRealizadas; // Mi nodo apunta al primer elemento de la lista de realizadas
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
        int subOpcion = 0;
            printf("A seleccionado \"Listar tareas\" \n");
            printf("Porfavor eliga: \n 1 Mostrar todas las tareas \n 2 Mostrar las Tareas Pendientes \n 3 Mostrar las Tareas Realizadas\n");
            scanf("%d", &subOpcion);
            if(subOpcion == 1){
            MostarTareas(Star);
            MostarTareas(StarRealizadas);
            }else if(subOpcion == 2){
                MostarTareas(Star);
            }else{
                MostarTareas(StarRealizadas);
            }
            break;
        case 2:
            printf("A seleccionado \"Crear tareas\" \n");
            CrearTarea(Star);
            break;
        case 3:
            int IDSeleccionado;
            printf("A seleccionado \"Cambiar estado\" \n");
            printf("Porfavor Digite el ID de la Tarea\n");
            scanf("%d", &IDSeleccionado);
            CambiarEstado(Star , StarRealizadas ,IDSeleccionado);
            break;
        case 4:
        int IDSeleccionado;
        TNodo *Aux;
            printf("A seleccionado \"Buscar tarea por ID\" \n");
            printf("Porfavor Digite el ID de la Tarea\n");
            scanf("%d", &IDSeleccionado);
            
            Aux = buscarNodo(Star ,IDSeleccionado);

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
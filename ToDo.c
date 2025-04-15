#include <stdio.h>
#include <stdlib.h>

struct
{
    int TareaId;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
    int Estado;
}typedef Tarea;

struct 
{
    Tarea T;//Aputa a la tarea en la que se encuentra el nodo
    TNodo *Siguiente;//Mi nodo apunta al siguiente elemento de la lista
}typedef TNodo;

TNodo * CrearListaVacia(){
    return NULL;
}

TNodo * CrearNodo(Tarea *T , int ID , char *Descripcion , int Duracion){ //Creamos el nodo de la lista enlazada
    TNodo * NNodo = (TNodo *)malloc(sizeof(TNodo));
    NNodo->T.TareaId = ID;
    NNodo->T.Descripcion = Descripcion;
    NNodo->T.Duracion = Duracion;
    NNodo->T.Estado = 0;
    NNodo->Siguiente = NULL;

    return NNodo;
}

void InsertarNodo(TNodo **Star, TNodo * Nodo){//Insertamos al inicio de la lista en manera de stack
    Nodo->Siguiente= *Star;
    *Star = Nodo;
}

TNodo * buscarNodo(TNodo *Star, int ID){
    TNodo * Aux = Star;
    while (Aux && Aux->T.TareaId != ID)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
    
}

TNodo * QuitarNodo(TNodo * Star, Tarea dato){
    TNodo ** aux = Star;
    while (*aux != NULL && (*aux)->T != dato )
    {
        aux = &(*aux)->Siguiente;
    }
    if(*aux){
        TNodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
        return temp;
    }
    return NULL;
}

void EliminarNodo(TNodo * nodo){
    if (nodo)free(nodo);
    
}





int main(){
    TNodo * Star;//Mi nodo apunta al primer elemento de la lista

    Star = CrearListaVacia();
    


    return 0;
}
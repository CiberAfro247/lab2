#include "../include/carritoProductos.h"

struct rep_carritoProductos{
    TProducto producto;
    TCarritoProductos sig;
};


TCarritoProductos crearCarritoProductosVacio(){
    return NULL;
}
void insertarProductoCarritoProductos(TCarritoProductos &carritoProductos, TProducto producto){
    if (esVacioCarritoProductos(carritoProductos) || idTProducto(carritoProductos->producto) >= idTProducto(producto)){
        TCarritoProductos nuevoCarrito = new rep_carritoProductos;
        nuevoCarrito->producto = producto;
        nuevoCarrito->sig = carritoProductos;
        carritoProductos = nuevoCarrito;    
    }else{ 
        TCarritoProductos iter = carritoProductos;
        while (iter->sig != NULL && idTProducto(iter->sig->producto) < idTProducto(producto)){
            iter = iter->sig;
        }
            TCarritoProductos nuevoCarrito = new rep_carritoProductos;
            nuevoCarrito->sig = iter->sig; 
            iter->sig = nuevoCarrito;
            nuevoCarrito->producto = producto;
    }
}
void imprimirCarritoProductos(TCarritoProductos carritoProductos){
    while(carritoProductos != NULL){
        imprimirTProducto(carritoProductos->producto);
        carritoProductos = carritoProductos->sig;
    }
}

void liberarCarritoProductos(TCarritoProductos &carritoProductos){
    TCarritoProductos aux = carritoProductos;
    while(aux != NULL){
            TCarritoProductos temp = aux;
            liberarTProducto(temp->producto);
            aux = aux->sig;
            delete temp;
        }
        carritoProductos = NULL;
}

bool esVacioCarritoProductos(TCarritoProductos carritoProductos){
    if (carritoProductos == NULL){
        return true;
    }
    else return false;
}

bool existeProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    while (carritoProductos != NULL){
        if(idTProducto(carritoProductos->producto) == idProducto){
            return true;
        }
        carritoProductos=carritoProductos->sig;
    }
    return false;
}

TProducto obtenerProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    while (carritoProductos != NULL){
        if(idTProducto(carritoProductos->producto) == idProducto){
            return carritoProductos->producto;
        }
        carritoProductos=carritoProductos->sig;
    }
    return carritoProductos->producto;
}
void removerProductoCarritoProductos(TCarritoProductos &carritoProductos, int idProducto){
   if (idTProducto(carritoProductos->producto) == idProducto){
            TCarritoProductos del = carritoProductos;
            liberarTProducto(del->producto);
            carritoProductos = carritoProductos->sig;
            delete del;
    }
    else{
        if(carritoProductos != NULL){
            TCarritoProductos del = carritoProductos;
                while (del->sig != NULL && idTProducto(del->producto) != idProducto){
                    if(idTProducto(del->sig->producto) == idProducto){
                        TCarritoProductos aux = del->sig->sig;
                        liberarTProducto(del->sig->producto);
                        delete del->sig;
                        del->sig = aux;
                    } else {
                        del = del->sig;
                    }
                }   
        }
    }
}
#include "../include/producto.h"

struct rep_producto {
    int id;
    char nombre[MAX_NOMBRE_PRODUCTO];
    TFecha fechaIngreso;
    int precio;
};


TProducto crearTProducto(int id, const char nombre[MAX_NOMBRE_PRODUCTO], int precio, TFecha fechaIngreso){
    TProducto nuevoProducto = NULL;
    nuevoProducto = new rep_producto;
    nuevoProducto->id = id;
    strcpy(nuevoProducto->nombre,nombre);
    nuevoProducto->precio = precio;
    nuevoProducto->fechaIngreso = fechaIngreso;
    return nuevoProducto;
}

int idTProducto(TProducto producto){
    int id = producto->id;
    return id;
}

int precioTProducto(TProducto producto){
    int precio = producto->precio;
    return precio;
}

void imprimirTProducto(TProducto producto){
    printf("Producto: %d\n", producto->id);
    printf("%s\n", producto->nombre);
    printf("Precio: %d\n", producto->precio);
    printf("Ingresado el: ");
    imprimirTFecha(producto->fechaIngreso);
}

void liberarTProducto(TProducto &producto){
    liberarTFecha(producto->fechaIngreso);
    delete producto;
    producto = NULL;
}



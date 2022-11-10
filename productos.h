#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h> ///me deja utilizar la funcion sleep
#include "gotoxy.h"  ///me permite cambiar la posicion del cursor
#define TeclaArriba 72
#define TeclaAbajo 80
#define Enter 13
#include "clientes.h"
#include "pedidos.h"
#include "menu.h"


typedef struct _stProducto
{
    int idProducto;
    char nombreProducto[15];
    char categoria[15];
    float precio;
    int cantidad;
    int hayStock; // indica 1 activo y 0 anulado
} stProducto;


/// Productos
void mostrarProducto(stProducto *unProducto);
void crearProductoAdmin(stProducto *unProducto, int idProducto);
int crearProductoAdminyGuardarEnArchivo(stProducto *unProducto, char archivoProducto[]);
int generarIdProducto(char archivoProducto[]);
int pasarProductoaArchivo(char archivoProducto[], stProducto *unProducto, int posicion);
void mostrarunProductoEnArchivo(int pos, char archivoProducto[]);
void mostrarTodosProductosenArchivo(char archivoProductos[]);
int modificarProductoEnArchivo(char archivoProducto[], int idProducto);
int pasarProductoDesdeArchivo(char archivoProducto[], stProducto *unProducto, int posicion);
int bajaDeProducto(char archivoProducto[], int posProducto);
void mostrarProductoClientes(stProducto *unProducto);
void mostrarTodosProductosenArchivoClientes(char archivoProductos[]);
void agregarProductoAArreglo(stProducto unArregloProducto[], char archivoProductos[], int *validos, int idProducto);
void mostrarProductosenArreglo(stProducto unArregloProducto[], int *validos);
float costoTotalArreglo(stProducto unArregloProductos[], int validos);
void modificarProductoDeUnArreglo(stProducto unArregloProducto[], int *validos, int posProducto, int cantidad);
int buscarPosProductoEnArreglo(stProducto unArregloProducto[], int *validos, int idProducto);

#endif // PRODUCTOS_H_INCLUDED

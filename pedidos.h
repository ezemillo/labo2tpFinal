#ifndef PEDIDOS_H_INCLUDED
#define PEDIDOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h> ///me deja utilizar la funcion sleep
#include "productos.h"
#include "clientes.h"
#include "menu.h"



typedef struct
{
    int idPedido;   // auto incremental
    int idCliente;  // este valor corresponde al id del cliente que realizo  el pedido
    char fecha[12];
    stProducto productos[20];
    int cantProductos;
    char descripcion[300];
    float costo;
    int pedidoAnulado; // indica 1 activo y 0 anulado
} stPedido;

void mostrarPedido(stPedido unPedido);
int pasarPedidoaArchivo(char archivoPedido[], stPedido *unPedido4, int posicion);
int pasarPedidoPoridClienteaArreglo(int idCliente, stPedido unArregloPedidos[], int dimArreglo, char archivoPedido[]);
int generarNumeroPedido(char archivoPedido[]);
void crearPedido(stPedido* unPedido, int idCliente, int idPedido, int validosProductos, stProducto unArregloProductos[]);
int crearPedidoyGuardarEnArchivo(char archivoPedido[], int idCliente, int validosProductos, stProducto arregloProducto[]);
void mostrarTodosPedidosenArchivo(char archivoPedidos[]);
int buscarPosPedidoPoridCliente(int idCliente, int posInicial, char archivoPedido[], int vistaAdmin);
void mostrarPedidosPorCliente(char archivoPedido[], int idCliente, int admin); // vista admin=1
void mostrarunPedidoEnArchivo(int pos, char archivoPedido[]);
int modificarPedidoEnArchivo(char archivoPedidos[], int posPedido, int idCliente);
int bajaDePedido(char archivoPedidos[], int posPedido);
int pasarPedidoDesdeArchivo(char archivoPedido[], stPedido *unPedido4, int posicion);
float costoTotalPedido(stPedido unPedido);
void generarFechaActual(char unArregloFecha[]);


#endif // PEDIDOS_H_INCLUDED

#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

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
#include "productos.h"
#include "pedidos.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int idCliente; // auto incremental
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char genero;
    int rol;    // 1: es admin - 0: es com n
    int activo; // indica 1 activo y 0 inactivo
} stCliente;

/// Clientes
int idClienteNuevo(char archivo[]);
void bajaDeCliente(char archivo[]);
void altaDeCliente(char archivo[], int rol);
int verificarClienteYaExiste(char archivo[], stCliente clienteIngreso);
int login(char archivo[], int *idCliente);
void MostrarArchivoClientes(char archivo[]);
void gestionarModificarCliente(char pedidos[], char productos[], char clientes[], int *id, int opcionSeleccionada, int rol);
void altaDeClienteAdmin(char archivo[]);
int archivoClienteToArray (char clientes[],stCliente arrayClientes[], int dimension);

#endif // CLIENTES_H_INCLUDED

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
#include "productos.h"
#include "menu.h"




typedef struct
{
    int idPedido;   // auto incremental
    int idCliente;  // este valor corresponde al id del cliente que realizo  el pedido
    char fecha[12]; // dd/MM/aaaa
    stProducto productos[20];
    int cantProductos;
    char descripcion[300];
    float costo;
    int pedidoAnulado; // indica 1 activo y 0 anulado
} stPedido;

/// Generales
void generarFechaActual(char unArregloFecha[]);
void mostrarCorrecto();
void crearApp(char clientes[], char pedido[], char productos[], int *idActivo);
int cambiarOpcionSeleccionada(int teclaPulsada, int cantidadOpciones, int opcionSeleccionada);
void pintarPantallaConMenu(char *titulo, char *opciones[], int cantidadDeOpciones, int opcionSelecionada);
void mostrarPantallaConMenu(char *titulo, char *opciones[], int cantidadDeOpciones, int opcionSelecionada);
void mostrarOpcion(char *opcion, int numeroDeOpcion, int opcionSeleccionada);
/// Funciones Menu
int crearMenuModificarCliente();
int crearMenuDeInicio();
void gestionarOpcionDeMenuDeInicio(char clientes[], char pedido[], char productos[], int opcionSeleccionada, int *idActivo);
int crearMenuAdministrador();
void gestionarOpcionDeMenuDeAdministrador(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idActivo);
int crearMenuCliente();
void gestionarMenuClientes(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo);
int crearMenuComercios();
void gestionarOpcionDeMenuDeComercios(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos);
int crearMenuVerduleria();
void gestionarOpcionDeMenuVerduleria(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos);
int crearMenuCarniceria();
void gestionarOpcionDeMenuCarniceria(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos);
int crearMenuSupermercado();
void gestionarOpcionDeMenuSupermercado(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos);
int crearMenuFarmacia();
void gestionarOpcionDeMenuFarmacia(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos);
int crearMenuRestaurante();
void gestionarOpcionDeMenuRestaurante(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos);
void gestionarEntreMenuAdministradorYCliente(char clientes[], char pedido[], char productos[], int rol, int *idActivo);
int gestionarMenu(char *titulo, char *opciones[], int cantidadDeOpciones, int opcionSeleccionada);
void volverAlMenuClientes(char clientes[], char pedidos[], char productos[], int *idClienteActivo);
void volverAlMenuAdministrador(char clientes[], char pedidos[], char productos[], int *idClienteActivo);



/// Pedidos
void mostrarPedido(stPedido unPedido);
int pasarPedidoaArchivo(char archivoPedido[], stPedido *unPedido4, int posicion);
int pasarPedidoPoridClienteaArreglo(int idCliente, stPedido unArregloPedidos[], int dimArreglo, char archivoPedido[]);
int generarNumeroPedido(char archivoPedido[]);
void crearPedido(stPedido *unPedido, int idCliente, int idPedido, int validosProductos, stProducto unArregloProductos[]);
int crearPedidoyGuardarEnArchivo(char archivoPedido[], int idCliente, int validosProductos, stProducto arregloProducto[]);
void mostrarTodosPedidosenArchivo(char archivoPedidos[]);
int buscarPosPedidoPoridCliente(int idCliente, int posInicial, char archivoPedido[], int vistaAdmin);
void mostrarPedidosPorCliente(char archivoPedido[], int idCliente, int admin); // vista admin=1
void mostrarunPedidoEnArchivo(int pos, char archivoPedido[]);
int modificarPedidoEnArchivo(char archivoPedidos[], int posPedido, int idCliente);
int bajaDePedido(char archivoPedidos[], int posPedido);
int pasarPedidoDesdeArchivo(char archivoPedido[], stPedido *unPedido4, int posicion);
float costoTotalPedido(stPedido unPedido);



int main()
{
    char clientes[] = {"clientes.bin"};
    char pedidos[] = {"pedidos.bin"};
    char productos[] = {"productos.bin"};
    int idClienteActivo = 1;
    crearApp(clientes, pedidos, productos, &idClienteActivo);
    return 0;
}

///--------Generales--------------
void generarFechaActual(char unArregloFecha[])
{

    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[12];
    strftime(output, 12, "%d/%m/%y", tlocal);
    strcpy(unArregloFecha, output);
}


void mostrarCorrecto(int unInt)
{
    if (unInt == 1)
    {
        puts("\nOperacion Exitosa\n");
    }
    else
    {
        puts("\nOperacion Fallida\n");
    }
}




int crearMenuModificarCliente()
{
    int opcionSeleccionada = 0;
    char *titulo = "Menu de Modificacion";
    char *opciones[] = {"Nombre", "Apellido", "Usuario", "Password", "Mail", "Volver"};
    int cantidadDeOpciones = 6;
    opcionSeleccionada = gestionarMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);
    return opcionSeleccionada;
}



void gestionarModificarClienteAdmin(char pedidos[], char productos[], char clientes[], int *id, int opcionSeleccionada)
{
    gestionarModificarCliente(pedidos, productos, clientes, id, opcionSeleccionada, 1);
}


///---------------------- Funciones Pedidos --------------------------
///-----generales---------

void mostrarPedido(stPedido unPedido)
{

    printf("\n\t Pedido n: %d \n", unPedido.idPedido);
    printf("\n\t Cliente n: %d \n", unPedido.idCliente);
    if (unPedido.pedidoAnulado == 1)
    {
        printf("\n\t Su Pedido esta activo  \n");
        printf("\n");
    }
    else
    {
        puts("\n\t Su Pedido esta anulado  \n");
        printf("\n");
    }

    mostrarProductosenArreglo(unPedido.productos, &unPedido.cantProductos);

    printf("\n\t Fecha del pedido: %s \n", unPedido.fecha);
    printf("\n\t Notas adicionales: %s \n", unPedido.descripcion);
    printf("\n\t Importe total: %.2f \n", unPedido.costo);
}

int pasarPedidoaArchivo(char archivoPedido[], stPedido *unPedido4, int posicion)
{

    FILE *puntFile;
    puntFile = fopen(archivoPedido, "r+b");
    int correcto = 0;

    if (puntFile != NULL)
    {

        fseek(puntFile, posicion * sizeof(stPedido), SEEK_SET);
        if (fwrite(unPedido4, sizeof(stPedido), 1, puntFile) > 0)
        {
            correcto = 1;
        }
        fclose(puntFile);
    }
    return correcto;
}

int pasarPedidoPoridClienteaArreglo(int idCliente, stPedido unArregloPedidos[], int dimArreglo, char archivoPedido[])
{
    int validos = 0;
    int posPedido = 0;

    while (validos < dimArreglo && posPedido != -1)
    {
        posPedido = buscarPosPedidoPoridCliente(idCliente, posPedido, archivoPedido, 1);
    }

    return posPedido;
}

///------------ cargar pedido nuevo----------

int generarNumeroPedido(char archivoPedido[])
{

    FILE *puntFile;
    puntFile = fopen(archivoPedido, "rb");
    int idPedido = 0;
    long int pesoArchivo;
    if (puntFile == NULL)
    {
        puntFile = fopen(archivoPedido, "wb");
        fclose(puntFile);
        puntFile = fopen(archivoPedido, "rb");
    }

    if (puntFile != NULL)
    {
        fseek(puntFile, 0, SEEK_END);
        pesoArchivo = ftell(puntFile);

        idPedido = (int)pesoArchivo / sizeof(stPedido);

        fclose(puntFile);
    }

    return idPedido;
}

void crearPedido(stPedido *unPedido, int idCliente, int idPedido, int validosProductos, stProducto unArregloProductos[])
{
    int i = 0;
    unPedido->idPedido = idPedido;
    unPedido->idCliente = idCliente;
    unPedido->cantProductos = validosProductos;
    for (i = 0; i < validosProductos; i++)
    {
        unPedido->productos[i] = unArregloProductos[i];
    }
    char fechaActual[12];
    generarFechaActual(fechaActual);
    strcpy(unPedido->fecha, fechaActual);
    unPedido->pedidoAnulado = 1;

    puts("\n\t Agregar un comentario al pedido: \n");
    fflush(stdin);
    gets(unPedido->descripcion);

    unPedido->costo = costoTotalPedido(*unPedido);
}

int crearPedidoyGuardarEnArchivo(char archivoPedido[], int idCliente, int validosProductos, stProducto arregloProducto[])
{
    stPedido unPedido;
    int valida = 0;
    int idPedido = generarNumeroPedido(archivoPedido);
    crearPedido(&unPedido, idCliente, idPedido, validosProductos, arregloProducto);
    valida = pasarPedidoaArchivo(archivoPedido, &unPedido, idPedido);

    return valida;
}

void mostrarTodosPedidosenArchivo(char archivoPedidos[])
{
    FILE *puntFile;
    puntFile = fopen(archivoPedidos, "rb");
    stPedido unPedido;

    if (puntFile != NULL)
    {
        while (fread(&unPedido, sizeof(stPedido), 1, puntFile) > 0)
        {
            mostrarPedido(unPedido);
            puts("-----------------------------------------------------------------------------\n");
        }
        fclose(puntFile);
    }
}
///----------- mostrar  pedidos por cliente--------------

int buscarPosPedidoPoridCliente(int idCliente, int posInicial, char archivoPedido[], int vistaAdmin)
{
    stPedido unPedido;
    FILE *puntFile;
    puntFile = fopen(archivoPedido, "rb");
    int pos = -1;
    int flag = 0;

    if (puntFile != NULL)
    {

        fseek(puntFile, posInicial * sizeof(stPedido), SEEK_SET);
        while (flag != 1)
        {
            if (fread(&unPedido, sizeof(stPedido), 1, puntFile) > 0)
            {
                if (unPedido.idCliente == idCliente)
                {
                    pos = posInicial;
                    flag = 1;
                }
                posInicial++;
            }
            else
            {
                flag = 1;
                pos = -1;
            }
        }
        fclose(puntFile);
    }
    return pos;
}

void mostrarPedidosPorCliente(char archivoPedido[], int idCliente, int admin) // vista admin=1
{
    int pos = 0;
    int noPedido = 0;

    noPedido = buscarPosPedidoPoridCliente(idCliente, pos, archivoPedido, admin);
    if (noPedido == -1)
    {
        puts("No tiene pedidos cargados.");
    }
    else
    {
        while (pos != -1)
        {
            pos = buscarPosPedidoPoridCliente(idCliente, pos, archivoPedido, admin);
            if (pos != -1)
            {
                mostrarunPedidoEnArchivo(pos, archivoPedido);

                pos++;
            }
        }
    }
}

void mostrarunPedidoEnArchivo(int pos, char archivoPedido[])
{

    FILE *puntFile;
    puntFile = fopen(archivoPedido, "rb");
    stPedido unPedido;

    if (puntFile != NULL)
    {
        fseek(puntFile, pos * sizeof(stPedido), SEEK_SET);
        if (fread(&unPedido, sizeof(stPedido), 1, puntFile) > 0)
        {
            printf("\n */*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/ |Pedido n %d | */*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/ \n", pos);
            mostrarPedido(unPedido);
        }
        fclose(puntFile);
    }
}

///---------- baja de pedido

int bajaDePedido(char archivoPedidos[], int posPedido)
{
    stPedido unPedido;
    int correcto = 0;

    correcto = pasarPedidoDesdeArchivo(archivoPedidos, &unPedido, posPedido);
    unPedido.pedidoAnulado = 0;
    correcto = pasarPedidoaArchivo(archivoPedidos, &unPedido, posPedido);

    return correcto;
}

int pasarPedidoDesdeArchivo(char archivoPedido[], stPedido *unPedido4, int posicion)
{

    FILE *puntFile;
    puntFile = fopen(archivoPedido, "rb");
    int correcto = 0;

    if (puntFile != NULL)
    {

        fseek(puntFile, posicion * sizeof(stPedido), SEEK_SET);
        if (fread(unPedido4, sizeof(stPedido), 1, puntFile) > 0)
        {
            correcto = 1;
        }
        fclose(puntFile);
    }
    return correcto;
}

///-----------Productos-----------------

///--------generales




/// listado de productos para cliente


void mostrarProductoAdmin(stProducto *unProducto)
{

    printf("\t| %s |", unProducto->nombreProducto);
    puts("\n");
    printf("\t| ID: %d |", unProducto->idProducto);
    puts("\n");
    printf("\t| Categoria: %s | ", unProducto->categoria);
    puts("\n");
    printf("\t| Cantidad: %d | ", unProducto->cantidad);
    puts("\n");
    if (unProducto->hayStock == 1)
    {
        printf(" | Disponible | ");
    }
    else
    {
        puts(" | Sin stock | ");
    }
    printf("\t| Precio unidad: %.2f |", unProducto->precio);
    puts("\n");
    printf("\t| Subtotal: %.2f |", unProducto->precio * unProducto->cantidad);
    puts("\n");
}

///------modificar producto


///------ baja de productos



int crearMenuDeInicio()
{
    int opcionSeleccionada = 0;
    char *titulo = "Bienvenido a HaCPedidos";
    char *opciones[] = {"Ingresar", "Registrarse", "Salir"};
    int cantidadDeOpciones = 3;
    opcionSeleccionada = gestionarMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);
    return opcionSeleccionada;
}

void gestionarOpcionDeMenuDeInicio(char clientes[], char pedido[], char productos[], int opcionSeleccionada, int *idActivo)
{
    int opcionSeleccionadaInicio = 0;
    int rol = 0;
    system("cls");
    switch (opcionSeleccionada)
    {
    case 0:
        rol = login(clientes, idActivo);
        gestionarEntreMenuAdministradorYCliente(clientes, pedido, productos, rol, idActivo);
        if (rol != 0 && rol != 1)
        {
            opcionSeleccionadaInicio = crearMenuDeInicio();
            gestionarOpcionDeMenuDeInicio(clientes, pedido, productos, opcionSeleccionadaInicio, idActivo);
        }
        break;

    case 1:
        altaDeCliente(clientes, 0);
        opcionSeleccionadaInicio = crearMenuDeInicio();
        gestionarOpcionDeMenuDeInicio(clientes, pedido, productos, opcionSeleccionadaInicio, idActivo);
        break;
    case 2:
        printf("Hasta la proxima");
        exit(-1);
        break;
    }
}

int crearMenuAdministrador()
{
    int opcionSeleccionada = 0;
    char *titulo = "Menu de administrador";
    char *opciones[] = {"Ver clientes", "Modificar clientes", "Dar de baja clientes", "Ver pedidos de un cliente", "Ver pedidos",
                        "Dar de baja pedidos", "Ver listado de productos", "Agregar productos",
                        "Modificar productos", "Dar de baja productos", "Cerrar sesion"};
    int cantidadDeOpciones = 11;
    opcionSeleccionada = gestionarMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);
    return opcionSeleccionada;
}

void mostrarUnSoloClienteAdmin(char archivo[])
{
    FILE *archivito;
    stCliente cliente;
    archivito = fopen(archivo, "rb");
    int i = 0, clienteBuscar;

    printf("Ingerse el ID del cliente a buscar\n");
    scanf("%d", &clienteBuscar);

    if (archivito != NULL)
    {
        while (fread(&cliente, sizeof(stCliente), 1, archivito) > 0)
        {
            if (cliente.idCliente == clienteBuscar)
            {
                printf("\n Registro numero %d", i++);
                puts("\n-------------------------------------");
                printf("\n IdCliente: %d", cliente.idCliente);
                printf("\n Nombre: %s", cliente.nombre);
                printf("\n Apellido: %s", cliente.apellido);
                printf("\n Username: %s", cliente.userName);
                printf("\n Password: %s", cliente.password);
                printf("\n Mail: %s", cliente.mail);
                printf("\n Genero: %c", cliente.genero);
                printf("\n Rol: %d", cliente.rol);
                printf("\n Activo: %d", cliente.activo);
                puts("\n-------------------------------------");
            }
        }
    }
    fclose(archivito);
}

void gestionarOpcionDeMenuDeAdministrador(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idActivo)
{
    stProducto unProducto;
    system("cls");
    int idCliente = 0, idPedido = 0, idProducto = 0, rol = 1, opcionSeleccionadaMenuAdmin = 0, eleccion;
    switch (opcionSeleccionada)
    {
    case 0:
        printf("Desea ver un cliente solo o un listado? 1=uno 2=todos\n");
        scanf("%d", &eleccion);
        if (eleccion == 1)
        {
            mostrarUnSoloClienteAdmin(clientes);
        }
        else if (eleccion == 2)
        {
            MostrarArchivoClientes(clientes);
        }
        break;
    case 1:
        MostrarArchivoClientes(clientes);
        printf("\n---------Ingrese ID de cliente a modificar--------------\n");
        scanf("%d", &idCliente);
        opcionSeleccionadaMenuAdmin = crearMenuModificarCliente();
        gestionarModificarCliente(pedidos, productos, clientes, &idCliente, opcionSeleccionadaMenuAdmin, 1);
        break;
    case 2:
        MostrarArchivoClientes(clientes);
        bajaDeCliente(clientes);
        MostrarArchivoClientes(clientes);
        break;
    case 3:
        MostrarArchivoClientes(clientes);
        printf("Ingrese el ID del cliente del cual quiera ver sus pedidos");
        scanf("%d", &idCliente);
        mostrarPedidosPorCliente(pedidos, idCliente, rol);
        break;
    case 4:
        mostrarTodosPedidosenArchivo(pedidos);
        system("pause");
        break;
    case 5:
        mostrarTodosPedidosenArchivo(pedidos);
        puts("Ingrese el ID del cliente: \n");
        scanf("%d", &idCliente);
        mostrarPedidosPorCliente(pedidos, idCliente, rol);
        puts("Ingrese el ID del pedido a dar de baja: \n");
        scanf("%d", &idPedido);
        bajaDePedido(pedidos, idPedido);
        break;
    case 6:
        mostrarTodosProductosenArchivo(productos);
        break;
    case 7:
        crearProductoAdminyGuardarEnArchivo(&unProducto, productos);
        break;
    case 8:
        mostrarTodosProductosenArchivo(productos);
        puts("Ingrese el id del producto a modificar: ");
        scanf("%d", &idProducto);
        modificarProductoEnArchivo(productos, idProducto);
        break;
    case 9:
        mostrarTodosProductosenArchivo(productos);
        puts("Ingrese el id del producto a dar de baja: ");
        scanf("%d", &idProducto);
        bajaDeProducto(productos, idProducto);
        break;
    case 10:
        opcionSeleccionada = crearMenuDeInicio();
        gestionarOpcionDeMenuDeInicio(clientes, pedidos, productos, opcionSeleccionada, idActivo);
        break;
    }
    volverAlMenuAdministrador(clientes, pedidos, productos, idActivo);
}

///---------Menu cliente
int crearMenuCliente()
{
    int opcionSeleccionada = 0;
    char *titulo = "Menu de Cliente";
    char *opciones[] = {"Modificar mis datos", "Ver mis pedidos", "Hacer pedido", "Alta/Baja de pedido", "Ver Listado de Productos", "Cerrar sesion"};
    int cantidadDeOpciones = 6;
    opcionSeleccionada = gestionarMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);
    return opcionSeleccionada;
}

void gestionarMenuClientes(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo)
{
    int opcionSeleccionadaMenuClientes = 0;
    int opcionSeleccionada2 = 0;
    int pedidoFinalizado = 0;
    stProducto unArregloProductos[20];
    int validos = 0;

    int i = 0;
    system("cls");
    switch (opcionSeleccionada)
    {
    case 0:
        opcionSeleccionada2 = crearMenuModificarCliente();
        gestionarModificarCliente(pedidos, productos, clientes, idClienteActivo, opcionSeleccionada2, 0);
        break;
    case 1:
        system("cls");
        mostrarPedidosPorCliente(pedidos, *idClienteActivo, 0);
        volverAlMenuClientes(clientes, pedidos, productos, idClienteActivo);

        break;
    case 2:
        do
        {
            opcionSeleccionadaMenuClientes = crearMenuComercios();
            gestionarOpcionDeMenuDeComercios(opcionSeleccionadaMenuClientes, clientes, pedidos, productos, idClienteActivo, unArregloProductos, &validos);

        } while (pedidoFinalizado != 1);
        volverAlMenuClientes(clientes, pedidos, productos, idClienteActivo);
        break;
    case 3:
        mostrarPedidosPorCliente(pedidos, *idClienteActivo, 1);
        i = buscarPosPedidoPoridCliente(*idClienteActivo, 0, pedidos, 1);
        if (i != -1)
        {
            printf("\n\tIngrese el id del pedido que quiere dar de baja/alta:\n");
            scanf("%d", &i);
            bajaDePedido(pedidos, i);
            mostrarPedidosPorCliente(pedidos, *idClienteActivo, 1);
            system("pause");
        }
        volverAlMenuClientes(clientes, pedidos, productos, idClienteActivo);
        break;

    case 4:
        mostrarTodosProductosenArchivoClientes(productos);
        puts("\nPresione cualquier tecla para regresar al menu anterior...");
        system("pause>nul");
        opcionSeleccionada2 = crearMenuCliente();
        gestionarMenuClientes(opcionSeleccionada2, clientes, pedidos, productos, idClienteActivo);
        break;

    case 5:
        crearApp(clientes, pedidos, productos, idClienteActivo);
        break;
    }
}

void volverAlMenuClientes(char clientes[], char pedidos[], char productos[], int *idClienteActivo)
{
    int opcionSeleccionada;
    puts("\nPresione cualquier tecla para regresar al menu anterior...");
    system("pause>nul");
    opcionSeleccionada = crearMenuCliente();
    gestionarMenuClientes(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo);
}

void volverAlMenuAdministrador(char clientes[], char pedidos[], char productos[], int *idClienteActivo)
{

    int opcionSeleccionada;
    puts("\nPresione cualquier tecla para regresar al menu anterior...");
    system("pause>nul");
    opcionSeleccionada = crearMenuAdministrador();
    gestionarOpcionDeMenuDeAdministrador(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo);
}

int crearMenuComercios()
{
    int opcionSeleccionada = 0;
    char *titulo = "Donde queres comprar?";
    char *opciones[] = {"Verduleria", "Carniceria", "Supermercado", "Farmacia", "Restaurante", "Ver Carrito", "Eliminar Producto de Carrito", "Finalizar Compra", "Volver"};
    int cantidadDeOpciones = 9;
    opcionSeleccionada = gestionarMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);

    return opcionSeleccionada;
}

void gestionarOpcionDeMenuDeComercios(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos)
{
    system("cls");
    float total;
    int pos;
    int cant;
    switch (opcionSeleccionada)
    {
    case 0:
        opcionSeleccionada = crearMenuVerduleria();
        gestionarOpcionDeMenuVerduleria(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo, unArregloProductos, validos);
        break;
    case 1:
        opcionSeleccionada = crearMenuCarniceria();
        gestionarOpcionDeMenuCarniceria(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo, unArregloProductos, validos);
        break;
    case 2:
        opcionSeleccionada = crearMenuSupermercado();
        gestionarOpcionDeMenuSupermercado(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo, unArregloProductos, validos);
        break;

    case 3:
        opcionSeleccionada = crearMenuFarmacia();
        gestionarOpcionDeMenuFarmacia(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo, unArregloProductos, validos);
        break;
    case 4:
        opcionSeleccionada = crearMenuRestaurante();
        gestionarOpcionDeMenuRestaurante(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo, unArregloProductos, validos);
        break;
    case 5:
        /// ver carrito
        mostrarProductosenArreglo(unArregloProductos, validos);
        total = costoTotalArreglo(unArregloProductos, *validos);
        printf("El costo total del pedido es: %.2f.\n", total);
        system("pause");
        break;
    case 6:
        /// eliminar producto de arreglo
        mostrarProductosenArreglo(unArregloProductos, validos);
        puts("\nIngrese el ID del producto que desea modificar\n");
        scanf("%d", &pos);
        pos = buscarPosProductoEnArreglo(unArregloProductos, validos, pos);
        puts("\nIngrese la cantidad de unidades a anular\n");
        scanf("%d", &cant);
        modificarProductoDeUnArreglo(unArregloProductos, validos, pos, cant);
        mostrarProductosenArreglo(unArregloProductos, validos);
        system("pause");

        break;

    case 7:
        crearPedidoyGuardarEnArchivo(pedidos, *idClienteActivo, *validos, unArregloProductos);
        *validos = 0;
        volverAlMenuClientes(clientes, pedidos, productos, idClienteActivo);
        break;
    case 8:
        *validos = 0;
        opcionSeleccionada = crearMenuCliente();
        gestionarMenuClientes(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo);
        break;
    }
}

int crearMenuVerduleria()
{
    int opcionSeleccionada = 0;
    char *titulo = "Verduleria";
    char *opciones[] = {"Cebolla", "Papa", "Tomate", "Lechuga", "Palta", "Volver"};
    int cantidadDeOpciones = 6;
    opcionSeleccionada = gestionarMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);
    return opcionSeleccionada;
}

void gestionarOpcionDeMenuVerduleria(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos)
{

    system("cls");
    switch (opcionSeleccionada)
    {
    case 0:

        agregarProductoAArreglo(unArregloProductos, productos, validos, 0);
        break;
    case 1:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 1);
        break;
    case 2:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 2);
        break;

    case 3:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 3);
        break;
    case 4:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 4);
        break;
    case 5:
        opcionSeleccionada = crearMenuComercios();
        gestionarOpcionDeMenuDeComercios(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo, unArregloProductos, validos);
        break;
    }
}

int crearMenuCarniceria()
{
    int opcionSeleccionada = 0;
    char *titulo = "Carniceria";
    char *opciones[] = {"Milanesas", "Asado", "Carne Picada", "Bife de Cerdo", "Chinchulines", "Volver"};
    int cantidadDeOpciones = 6;
    opcionSeleccionada = gestionarMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);
    return opcionSeleccionada;
}

void gestionarOpcionDeMenuCarniceria(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos)
{
    system("cls");
    switch (opcionSeleccionada)
    {
    case 0:

        agregarProductoAArreglo(unArregloProductos, productos, validos, 5);

        break;
    case 1:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 6);
        break;
    case 2:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 7);
        break;

    case 3:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 8);
        break;
    case 4:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 9);
        break;
    case 5:

        opcionSeleccionada = crearMenuComercios();
        gestionarOpcionDeMenuDeComercios(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo, unArregloProductos, validos);

        break;
    }
}

int crearMenuSupermercado()
{
    int opcionSeleccionada = 0;
    char *titulo = "Supermercado";
    char *opciones[] = {"Arroz", "Yerba", "Servilletas", "Lentejas", "Coca-Cola", "Volver"};
    int cantidadDeOpciones = 6;
    opcionSeleccionada = gestionarMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);
    return opcionSeleccionada;
}

void gestionarOpcionDeMenuSupermercado(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos)
{
    system("cls");
    switch (opcionSeleccionada)
    {
    case 0:

        agregarProductoAArreglo(unArregloProductos, productos, validos, 10);
        break;
    case 1:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 11);
        break;
    case 2:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 12);
        break;

    case 3:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 13);
        break;
    case 4:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 14);
        break;
    case 5:

        opcionSeleccionada = crearMenuComercios();
        gestionarOpcionDeMenuDeComercios(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo, unArregloProductos, validos);
        break;
    }
}

int crearMenuFarmacia()
{
    int opcionSeleccionada = 0;
    char *titulo = "Farmacia";
    char *opciones[] = {"Perfume", "Cepillo dental", "Pasta dental", "Crema facial", "Desodorante", "Volver"};
    int cantidadDeOpciones = 6;
    opcionSeleccionada = gestionarMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);
    return opcionSeleccionada;
}

void gestionarOpcionDeMenuFarmacia(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos)
{
    system("cls");
    switch (opcionSeleccionada)
    {
    case 0:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 15);
        break;
    case 1:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 16);
        break;
    case 2:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 17);
        break;
    case 3:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 18);
        break;
    case 4:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 19);
        break;
    case 5:

        opcionSeleccionada = crearMenuComercios();
        gestionarOpcionDeMenuDeComercios(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo, unArregloProductos, validos);
        break;
    }
}

int crearMenuRestaurante()
{
    int opcionSeleccionada = 0;
    char *titulo = "Restaurante";
    char *opciones[] = {"Hamburguesa", "Pizza", "Empanadas", "Sushi", "Canelones", "Volver"};
    int cantidadDeOpciones = 6;
    opcionSeleccionada = gestionarMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);
    return opcionSeleccionada;
}

void gestionarOpcionDeMenuRestaurante(int opcionSeleccionada, char clientes[], char pedidos[], char productos[], int *idClienteActivo, stProducto unArregloProductos[], int *validos)
{
    system("cls");
    switch (opcionSeleccionada)
    {
    case 0:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 20);
        break;
    case 1:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 21);
        break;
    case 2:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 22);
        break;
    case 3:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 23);
        break;
    case 4:
        agregarProductoAArreglo(unArregloProductos, productos, validos, 24);
        break;
    case 5:
        opcionSeleccionada = crearMenuComercios();
        gestionarOpcionDeMenuDeComercios(opcionSeleccionada, clientes, pedidos, productos, idClienteActivo, unArregloProductos, validos);
        break;
    }
}

void crearApp(char clientes[], char pedido[], char productos[], int *idActivo)
{
    int opcionSeleccionada = 0;
    opcionSeleccionada = crearMenuDeInicio();
    gestionarOpcionDeMenuDeInicio(clientes, pedido, productos, opcionSeleccionada, idActivo);
}

void gestionarEntreMenuAdministradorYCliente(char clientes[], char pedido[], char productos[], int rol, int *idActivo)
{
    int opcionSeleccionada = 0;
    if (rol == 1)
    {
        opcionSeleccionada = crearMenuAdministrador();
        gestionarOpcionDeMenuDeAdministrador(opcionSeleccionada, clientes, pedido, productos, idActivo);
    }
    else if (rol == 0)
    {
        opcionSeleccionada = crearMenuCliente();
        gestionarMenuClientes(opcionSeleccionada, clientes, pedido, productos, idActivo);
    }
}

int gestionarMenu(char *titulo, char *opciones[], int cantidadDeOpciones, int opcionSeleccionada)
{
    pintarPantallaConMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);
    int teclaPulsada = 0;
    do
    {
        teclaPulsada = getch();
        opcionSeleccionada = cambiarOpcionSeleccionada(teclaPulsada, cantidadDeOpciones, opcionSeleccionada);
        pintarPantallaConMenu(titulo, opciones, cantidadDeOpciones, opcionSeleccionada);
    } while (teclaPulsada != Enter);
    return opcionSeleccionada;
}

int cambiarOpcionSeleccionada(int teclaPulsada, int cantidadOpciones, int opcionSeleccionada)
{
    if (teclaPulsada == TeclaAbajo)
    {
        opcionSeleccionada++;
        if (opcionSeleccionada > cantidadOpciones - 1)
        {
            opcionSeleccionada = 0;
        }
    }

    if (teclaPulsada == TeclaArriba)
    {
        opcionSeleccionada--;
        if (opcionSeleccionada < 0)
        {
            opcionSeleccionada = cantidadOpciones - 1;
        }
    }

    return opcionSeleccionada;
}

void pintarPantallaConMenu(char *titulo, char *opciones[], int cantidadDeOpciones, int opcionSelecionada)
{
    system("cls");
    mostrarPantallaConMenu(titulo, opciones, cantidadDeOpciones, opcionSelecionada);
}

void mostrarPantallaConMenu(char *titulo, char *opciones[], int cantidadDeOpciones, int opcionSelecionada)
{
    printf("\t -- %s --\n", titulo);
    for (int i = 0; i < cantidadDeOpciones; i++)
    {
        mostrarOpcion(opciones[i], i, opcionSelecionada);
    }
}

void mostrarOpcion(char *opcion, int numeroDeOpcion, int opcionSeleccionada)
{
    gotoxy(6, 3 + numeroDeOpcion);
    if (opcionSeleccionada == numeroDeOpcion)
    {
        color(112);
        printf(" %s \n", opcion);
        color(7);
    }
    else
    {
        printf(" %s \n", opcion);
    }
}


float costoTotalPedido(stPedido unPedido)
{
    float total = 0;
    for (int i = 0; i < unPedido.cantProductos; i++)
    {
        total = total + (unPedido.productos[i].precio * unPedido.productos[i].cantidad);
    }

    return total;
}




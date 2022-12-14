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
#include "clientes.h"
#include "pedidos.h"
#include "arbol.h"

#include "menu.h"



/// Generales
void generarFechaActual(char unArregloFecha[]);
void mostrarCorrecto(int unInt);
void crearApp(char clientes[], char pedido[], char productos[], int *idActivo);
int cambiarOpcionSeleccionada(int teclaPulsada, int cantidadOpciones, int opcionSeleccionada);
void pintarPantallaConMenu(char *titulo, char *opciones[], int cantidadDeOpciones, int opcionSelecionada);
void mostrarPantallaConMenu(char *titulo, char *opciones[], int cantidadDeOpciones, int opcionSelecionada);
void mostrarOpcion(char *opcion, int numeroDeOpcion, int opcionSeleccionada);
void funcionArbolEnMenu(char archivoCliente[]);
int getMesIngreso(char fecha[]);


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
void funcionModificarClienteEnArbol(char archivoClientes[]);
void funcionBorrarNodoArbol(char archivoCliente[]);



/// Pedidos




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



///------------ cargar pedido nuevo----------



///----------- mostrar  pedidos por cliente--------------




///---------- baja de pedido



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
                        "Modificar productos", "Dar de baja productos","Mostrar arbol y liquidar periodo","Modificar Cliente en Arbol","Borrar nodo de arbol", "Cerrar sesion"
                       };
    int cantidadDeOpciones = 14;
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

        funcionArbolEnMenu(clientes);



        break;
    case 11:

        funcionModificarClienteEnArbol(clientes);

        break;
    case 12:

        funcionBorrarNodoArbol(clientes);

        break;

    case 13:
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

        }
        while (pedidoFinalizado != 1);
        volverAlMenuClientes(clientes, pedidos, productos, idClienteActivo);
        break;
    case 3:
        mostrarPedidosPorCliente(pedidos, *idClienteActivo, 1);
//            int i = buscarPosPedidoPoridCliente(*idClienteActivo, 0, pedidos, 1);
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
    }
    while (teclaPulsada != Enter);
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



void funcionArbolEnMenu(char archivoCliente[])
{

    int idCliente=0;

    char fechaIngreso[10];
    int fechaIng;

    nodoArbolCliente* raiz = cargarArbolDesdeArchivoCliente(archivoCliente);
    puts("Arbol cargado con Exito\n");
    preOrden(raiz);
    puts("Ingrese el IDCliente a liquidar\n");
    scanf("%d",&idCliente);
    puts("Ingrese el mes y a?o a liquidar formato mmaa\n");

    fflush(stdin);
    fechaIng = getMesIngreso(gets(fechaIngreso));


    nodoArbolCliente * cliente = buscarClienteEnArbol(raiz,idCliente);
    nodoPedido* lista = cliente->listaDePedidos;
    float suma = liquidarClientePorFecha(lista,fechaIng);

    printf("La suma de los pedidos del periodio %d, del cliente %d es: %f \n",fechaIng,idCliente,suma);


}

int getMesIngreso(char fecha[])
{

    int m0 = fecha[0]-48;
    if(m0==0)
    {
        m0=9;
    }

    int m1 = fecha[1]-48;
    int m2 = fecha[2]-48;
    int m3 = fecha[3]-48;


    return m0*1000 + m1 *100 + m2*10 + m3;

}

void funcionModificarClienteEnArbol(char archivoClientes[])
{
    nodoArbolCliente* raiz = cargarArbolDesdeArchivoCliente(archivoClientes);
    puts("Arbol cargado con Exito\n");
    preOrden(raiz);

    modificarClienteEnArbol(raiz);
    /// guardar en archivo cliente la modificacion
}


void funcionBorrarNodoArbol(char archivoCliente[])
{

    int idCliente=0;


    nodoArbolCliente* raiz = cargarArbolDesdeArchivoCliente(archivoCliente);
    puts("Arbol cargado con Exito\n");
    preOrden(raiz);
    puts("Ingrese el IDCliente a borrar \n");
    scanf("%d",&idCliente);
    borrarNodoArbol(raiz,idCliente);
    preOrden(raiz);

}

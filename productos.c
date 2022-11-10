#include "productos.h"

void mostrarProducto(stProducto *unProducto)
{

    printf("\n\t| %s | ", unProducto->nombreProducto);
    printf("\t| ID: %d |", unProducto->idProducto);

    printf("\t| Categoria: %s | \n ", unProducto->categoria);
    if (unProducto->hayStock == 1)
    {
        printf("\t| Disponible | \n");
    }
    else
    {
        puts("\t| Sin stock | \n");
    }
    printf("\t| Cantidad: %d | ", unProducto->cantidad);
    printf("\t| Precio unitario: %.2f | ", unProducto->precio);
    printf("\t| Subtotal: %.2f \n", (unProducto->precio * unProducto->cantidad));
}



void crearProductoAdmin(stProducto *unProducto, int idProducto)
{
    unProducto->idProducto = idProducto;

    puts("\n\t Ingrese el nombre del producto: \n");
    fflush(stdin);
    gets(unProducto->nombreProducto);

    puts("\n\t Ingrese el precio: \n");
    scanf("%f", &unProducto->precio);

    puts("\n\t Ingrese la categoria del producto: \n");
    fflush(stdin);
    gets(unProducto->categoria);

    puts("\n\t Ingrese la cantidad a ingresar: \n");
    scanf("%d", &unProducto->cantidad);

    puts("\n\t Desea activar el producto 1 para activar, 0 para desactivar: \n");
    scanf("%d", &unProducto->hayStock);
}


int crearProductoAdminyGuardarEnArchivo(stProducto *unProducto, char archivoProducto[])
{
    int valida = 0;
    int idProducto = generarIdProducto(archivoProducto);
    crearProductoAdmin(unProducto, idProducto);
    mostrarProducto(unProducto);
    valida = pasarProductoaArchivo(archivoProducto, unProducto, idProducto);

    return valida;
}


int generarIdProducto(char archivoProducto[])
{

    FILE *puntFile;
    puntFile = fopen(archivoProducto, "rb");
    int idProducto = 0;
    long int pesoArchivo;
    if (puntFile == NULL)
    {
        puntFile = fopen(archivoProducto, "wb");
        fclose(puntFile);
        puntFile = fopen(archivoProducto, "rb");
    }

    if (puntFile != NULL)
    {
        fseek(puntFile, 0, SEEK_END);
        pesoArchivo = ftell(puntFile);

        idProducto = (int)pesoArchivo / sizeof(stProducto);

        fclose(puntFile);
    }

    return idProducto;
}



int pasarProductoaArchivo(char archivoProducto[], stProducto *unProducto, int posicion)
{

    FILE *puntFile;
    puntFile = fopen(archivoProducto, "r+b");
    int correcto = 0;

    if (puntFile != NULL)
    {

        fseek(puntFile, posicion * sizeof(stProducto), SEEK_SET);
        if (fwrite(unProducto, sizeof(stProducto), 1, puntFile) > 0)
        {
            correcto = 1;
        }
        fclose(puntFile);
    }
    return correcto;
}



void mostrarunProductoEnArchivo(int pos, char archivoProducto[])
{

    FILE *puntFile;
    puntFile = fopen(archivoProducto, "rb");
    stProducto unProducto;

    if (puntFile != NULL)
    {
        fseek(puntFile, pos * sizeof(stProducto), SEEK_SET);
        if (fread(&unProducto, sizeof(stProducto), 1, puntFile) > 0)
        {
            mostrarProducto(&unProducto);
        }
        fclose(puntFile);
    }
}



void mostrarTodosProductosenArchivo(char archivoProductos[])
{
    FILE *puntFile;
    puntFile = fopen(archivoProductos, "rb");
    stProducto unProducto;

    if (puntFile != NULL)
    {
        while (fread(&unProducto, sizeof(stProducto), 1, puntFile) > 0)
        {
            mostrarProducto(&unProducto);
            puts("\n-----------------------------------------------------------------\n");
        }
        fclose(puntFile);
    }
}


int modificarProductoEnArchivo(char archivoProducto[], int idProducto)
{
    stProducto unProducto;
    int correcto = 0;
    crearProductoAdmin(&unProducto, idProducto);
    correcto = pasarProductoaArchivo(archivoProducto, &unProducto, idProducto);

    return correcto;
}


int pasarProductoDesdeArchivo(char archivoProducto[], stProducto *unProducto, int posicion)
{

    FILE *puntFile;
    puntFile = fopen(archivoProducto, "rb");
    int correcto = 0;

    if (puntFile != NULL)
    {

        fseek(puntFile, posicion * sizeof(stProducto), SEEK_SET);
        if (fread(unProducto, sizeof(stProducto), 1, puntFile) > 0)
        {
            correcto = 1;
        }
        fclose(puntFile);
    }
    return correcto;
}


int bajaDeProducto(char archivoProducto[], int posProducto)
{
    stProducto unProducto;
    int correcto = 0;

    correcto = pasarProductoDesdeArchivo(archivoProducto, &unProducto, posProducto);
    unProducto.hayStock = 0;
    correcto = pasarProductoaArchivo(archivoProducto, &unProducto, posProducto);

    return correcto;
}


void mostrarProductoClientes(stProducto *unProducto)
{
    printf("\t| %s |", unProducto->nombreProducto);

    printf("\t| ID: %d |", unProducto->idProducto);

    printf("\t| Categoria:|%s | ", unProducto->categoria);

    if (unProducto->hayStock == 1)
    {
        printf("\t| Disponible | ");

    }
    else
    {
        puts("\t| Sin stock | ");

    }
    printf("\t| Cantidad: %d |", unProducto->cantidad);

    printf("\t| Precio unidad: %.2f | ", unProducto->precio);

    printf("\t| Subtotal: %.2f |\n", unProducto->precio * unProducto->cantidad);
    puts("\n");
}


void mostrarTodosProductosenArchivoClientes(char archivoProductos[])
{
    FILE *puntFile;
    puntFile = fopen(archivoProductos, "rb");
    stProducto unProducto;

    if (puntFile != NULL)
    {
        while (fread(&unProducto, sizeof(stProducto), 1, puntFile) > 0)
        {
            mostrarProductoClientes(&unProducto);
        }
        fclose(puntFile);
    }
}



void agregarProductoAArreglo(stProducto unArregloProducto[], char archivoProductos[], int *validos, int idProducto)
{
    FILE *puntFile;
    puntFile = fopen(archivoProductos, "rb");
    stProducto unProducto;
    int cantidad = 0;
    int opcion = 0;

    if (puntFile != NULL)
    {

        fseek(puntFile, idProducto * sizeof(stProducto), SEEK_SET);
        fread(&unProducto, sizeof(stProducto), 1, puntFile);
        fclose(puntFile);
    }
    mostrarProductoClientes(&unProducto);

    puts("\nQuiere Agregar este producto al carrito? 1 para si, 2 para no.\n");
    scanf("%d", &opcion);

    if (opcion == 1)
    {
        if (unProducto.hayStock == 1)
        {
            puts("Ingrese la cantidad de unidades que desea agregar");
            scanf("%d", &cantidad);
            unProducto.cantidad = cantidad;
            unArregloProducto[*validos] = unProducto;
            (*validos)++;
        }
        else
        {
            puts("Producto sin Stock momentaneamente!");
        }
    }
}



void mostrarProductosenArreglo(stProducto unArregloProducto[], int *validos)
{

    int i = 0;
    for (i = 0; i < *validos; i++)
    {

        mostrarProductoClientes(&unArregloProducto[i]);
        puts("\n-------------------------------------------------------------------------------\n");
    }
}

float costoTotalArreglo(stProducto unArregloProductos[], int validos)
{
    float total = 0;
    for (int i = 0; i < validos; i++)
    {
        total = total + (unArregloProductos[i].cantidad * unArregloProductos[i].precio);
    }

    return total;
}


void modificarProductoDeUnArreglo(stProducto unArregloProducto[], int *validos, int posProducto, int cantidad)
{

    if (cantidad < unArregloProducto[posProducto].cantidad)
    {
        unArregloProducto[posProducto].cantidad = unArregloProducto[posProducto].cantidad - cantidad;
    }
    else
    {
        unArregloProducto[posProducto] = unArregloProducto[*validos - 1];
        *validos = *validos - 1;
    }
}



int buscarPosProductoEnArreglo(stProducto unArregloProducto[], int *validos, int idProducto)
{
    int pos;
    for (int i = 0; i < *validos; i++)
    {
        if (unArregloProducto[i].idProducto == idProducto)
        {
            pos = i;
        }
    }
    return pos;
}

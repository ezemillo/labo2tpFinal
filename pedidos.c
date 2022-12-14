#include "pedidos.h"


void mostrarPedido(stPedido unPedido)
{

    printf("\n\t Pedido n: %d \n", unPedido.idPedido);
    printf("\t Cliente n: %d \n", unPedido.idCliente);
    /*if (unPedido.pedidoAnulado == 1)
    {
        printf("\n\t Su Pedido esta activo  \n");
        printf("\n");
    }
    else
    {
        puts("\n\t Su Pedido esta anulado  \n");
        printf("\n");
    }
    */
    ///mostrarProductosenArreglo(unPedido.productos, &unPedido.cantProductos);

    printf("\t Fecha del pedido: %s ", unPedido.fecha);
    ///printf("\n\t Notas adicionales: %s \n", unPedido.descripcion);
    printf("\t Importe total: %.2f \n", unPedido.costo);
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
        stPedido P;
        FILE* archivo = fopen (archivoPedido, "rb");
        int contador=0;
        if (archivo){
                while (contador< dimArreglo && fread(&P, sizeof(stPedido),1, archivo)>0){
                    if (idCliente==P.idCliente){
                        unArregloPedidos[contador]=P;
                        contador++;
                    }

                }

            fclose(archivo);
        }

    return contador; //CAPACIDAD DEL ARREGLO DE PEDIDOS
}


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

void generarFechaActual(char unArregloFecha[])
{

    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[12];
    strftime(output, 12, "%d/%m/%y", tlocal);
    strcpy(unArregloFecha, output);
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


float costoTotalPedido(stPedido unPedido)
{
    float total = 0;
    for (int i = 0; i < unPedido.cantProductos; i++)
    {
        total = total + (unPedido.productos[i].precio * unPedido.productos[i].cantidad);
    }

    return total;
}


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
void crearPedidoyGuardarEnArchivoRandom(char archivoPedido[], int idCliente)
{
    stProducto unProducto;

    stPedido unPedido;
    generarProductoRandom(&unProducto);
    int idPedido = generarNumeroPedido(archivoPedido);
    crearPedidoRandom(&unPedido, idCliente, idPedido, unProducto);
    pasarPedidoaArchivo(archivoPedido, &unPedido, idPedido);


}

void cargarArchivoPedidosRandom(char archivoPedidos[])
{
    for(int i=0; i<55;i++){

        for(int j=0; j<40;j++){
            crearPedidoyGuardarEnArchivoRandom(archivoPedidos,i);

        }

    }

}

void generarProductoRandom(stProducto* unProducto){
unProducto->cantidad=1;
strcpy(unProducto->categoria, "random");
unProducto->hayStock=1;
unProducto->idProducto=25;
strcpy(unProducto->nombreProducto, "Producto Random");
unProducto->precio = 5;
}

void crearPedidoRandom(stPedido *unPedido, int idCliente, int idPedido, stProducto unProducto)
{

    unPedido->idPedido = idPedido;
    unPedido->idCliente = idCliente;
    unPedido->cantProductos = 1;
    unPedido->productos[0] = unProducto;
    char fechaActual[12];
    generarFechaRandom2(fechaActual,idPedido);
    strcpy(unPedido->fecha, fechaActual);
    unPedido->pedidoAnulado = 1;


    strcpy(unPedido->descripcion , "sin comentarios");

    unPedido->costo = rand()%5000;
}


void generarFechaRandom2(char unArregloFecha[], int contador)
{
    srand(time(NULL)- contador);
    unArregloFecha[0] = rand()%3+48;
    unArregloFecha[1] = rand()%8+49;
    unArregloFecha[2] = 47;
    unArregloFecha[3] = rand()%2+48;
    if(unArregloFecha[3] == 48)
    {
        unArregloFecha[4] = rand()%8+49;
    }
    else
    {
        unArregloFecha[4] = rand()%2+48;
    }

    unArregloFecha[5] = 47;
    unArregloFecha[6] = 50;
    unArregloFecha[7] = 50;
    unArregloFecha[8] = 00;

}




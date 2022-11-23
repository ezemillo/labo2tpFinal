#include "arbol.h"


nodoArbolCliente* inicArbol ()
{
    return NULL;
}


nodoArbolCliente* crearNodoArbol(stCliente unCliente)
{

    nodoArbolCliente* unNodo = (nodoArbolCliente*)malloc(sizeof(nodoArbolCliente));

    unNodo->dato=unCliente;

    unNodo->der = NULL;
    unNodo->izq= NULL;
    unNodo->modificado =0;
    unNodo->listaDePedidos = NULL;

    return unNodo;

}




nodoArbolCliente * arrayToArbol (stCliente a[], int base, int tope)
{
    int medio;
    stCliente C;

    nodoArbolCliente* arbol=NULL;

    if(!(base>tope))
    {
        medio=(base+tope)/2;
        C=a[medio];
        arbol=crearNodoArbol(C);


        arbol->listaDePedidos=crearListaPedidosPorIdcliente(C.idCliente,"pedidos.bin");



        arbol->izq=arrayToArbol(a,base,medio-1);
        arbol->der=arrayToArbol(a,medio+1,tope);
    }

    return arbol;
}


nodoArbolCliente* buscarClienteEnArbol (nodoArbolCliente* arbol, int id)
{
    nodoArbolCliente* buscado= inicArbol();
    if (arbol)
    {
        if (arbol->dato.idCliente==id)
        {
            buscado=arbol;
        }
        else
        {
            if (arbol->dato.idCliente> id)
            {
                buscado=buscarClienteEnArbol(arbol->izq, id);
            }
            else
            {
                if (!buscado)
                {
                    buscado=buscarClienteEnArbol(arbol->der, id);
                }
            }
        }
    }

    return buscado;
}

int solicitarIdCliente()
{
    int id;
    printf("\nIngrese Id del Cliente a modificar: \n");
    scanf("%d",&id);
    return id;
}

void preOrden(nodoArbolCliente* arbol)
{
    if (arbol)
    {
        muestraUnCliente(arbol->dato);
        mostrarListaPedidos(arbol->listaDePedidos);
        puts("-----------------------------------------------------------------------------\n");
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }

}


void muestraUnCliente(stCliente c)
{
    printf("\n idCLiente:..................................%d",c.idCliente);
    printf("\n Nombre..:..................................%s",c.nombre);
    printf("\n iApellido.:..................................%s",c.apellido);
    printf("\n userName:.................................%s",c.userName);
    printf("\n Email:.......................................%s",c.mail);
    printf("\n Genero:.....................................%c",c.genero);
    printf("\n---------------------------------------------------");

}

nodoArbolCliente* cargarArbolDesdeArchivoCliente (char archivoCliente[])
{

    stCliente arrayCliente[200];
    int validos = archivoClienteToArray(archivoCliente,arrayCliente,200);

    nodoArbolCliente* arbol = arrayToArbol(arrayCliente,0,validos-1);


    return arbol;


}



int getMesAnoDeFecha(char fecha[])
{

    int m0 = fecha[3]-48;
    if(m0==0)
    {
        m0=9;
    }

    int m1 = fecha[4]-48;
    int m2 = fecha[6]-48;
    int m3 = fecha[7]-48;


    return m0*1000 + m1 *100 + m2*10 + m3;

}



float liquidarClientePorFecha(nodoPedido* lista, int fecha)
{
    float acum = 0;
    nodoPedido* seg=lista;
    while(seg)
    {
        int fechaPedido = getMesAnoDeFecha(seg->pedido.fecha);
        if(fecha == fechaPedido)
        {
            acum= acum+seg->pedido.costo;
            mostrarPedido(seg->pedido);
        }
        seg=seg->siguiente;
    }
    return acum;

}

/*
void mostrarListaPedidosPorCliente(char archivoPedido[], int idCliente, int admin) // vista admin=1
{

    stCliente Arreglo[100];
    nodoArbolCliente*  C;
    archivoClienteToArray(archivoPedido,Arreglo,100);
    nodoArbolCliente* arbol =arrayToArbol(Arreglo,0,100);
    C =buscarClienteEnArbol(arbol, idCliente);
    mostrarListaPedidos (C->listaDePedidos);

}
*/

///ver si se necesitan

void modificarClienteEnArbol (nodoArbolCliente* arbol)
{

    nodoArbolCliente* buscado = buscarClienteEnArbol(arbol, solicitarIdCliente());

    muestraUnCliente(buscado->dato);

    char respuesta[30];

    puts("\n Desea modificar nombre? 1=SI 2=NO \n");
    fflush(stdin);
    if(getch() == 49)
    {
        fflush(stdin);
        puts("Ingrese el nuevo nombre \n ");
        strcpy(buscado->dato.nombre,gets(respuesta) );
    }
    fflush(stdin);

    puts("Desea modificar apellido? 1=SI 2=NO \n");
    if(getch() == 49)
    {
        fflush(stdin);
        puts("Ingrese el nuevo apellido \n ");

        strcpy(buscado->dato.apellido, gets(respuesta));
    }
    fflush(stdin);

    puts("Desea modificar Username? 1=SI 2=NO \n");
    if(getch() == 49)
    {
        fflush(stdin);
        puts("Ingrese el nuevo username \n ");

        strcpy(buscado->dato.userName, gets(respuesta));
    }
    fflush(stdin);

    puts("Desea modificar password? 1=SI 2=NO \n");
    if(getch() == 49)
    {
        fflush(stdin);
        puts("Ingrese la nueva password \n ");

        strcpy(buscado->dato.password, gets(respuesta));
    }
    fflush(stdin);

    puts("Desea modificar mail? 1=SI 2=NO \n");
    if(getch() == 49)
    {
        fflush(stdin);
        puts("Ingrese el nuevo mail \n ");

        strcpy(buscado->dato.mail, gets(respuesta));
    }
    buscado->modificado=1;
    sobreescribirClienteEnArchivo("clientes.bin",buscado->dato);

    muestraUnCliente(buscado->dato);

}

void sobreescribirClienteEnArchivo (char ruta [], stCliente C)
{

    stCliente A;
    FILE* archivo = fopen (ruta, "r+b");
    if (archivo)
    {
        while (fread(&A, sizeof(stCliente),1,archivo)>0 && A.idCliente!=C.idCliente);
        fseek(archivo,(-1)*sizeof(stCliente),SEEK_CUR);
        fwrite(&C, sizeof(stCliente), 1, archivo);
    }

    fclose(archivo);
}




nodoArbolCliente* agregarClienteAlArbol (nodoArbolCliente* arbol, nodoArbolCliente* nuevo)
{
    if (!arbol)
    {
        arbol=nuevo;
    }
    else
    {
        if (arbol->dato.idCliente < nuevo->dato.idCliente)
        {
            arbol= agregarClienteAlArbol(arbol->der, nuevo);
        }
        else
        {
            if (arbol->dato.idCliente > nuevo->dato.idCliente)
            {
                arbol= agregarClienteAlArbol(arbol->izq, nuevo);
            }
        }
    }

    return arbol;
}

/// borrar nodo ARBOL

nodoArbolCliente* borrarNodoArbol(nodoArbolCliente* arbol, int idCliente){
    if(arbol){
        if(idCliente > arbol-> dato.idCliente){ // en caso de que el idCliente a buscar sea mayor que la raiz busca hacia la derecha
            arbol-> der = borrarNodoArbol(arbol-> der, idCliente);
        }else if(idCliente < arbol-> dato.idCliente){ // en caso de que el idCliente a buscar sea menor que la raiz busca hacia la izquierda
            arbol-> izq = borrarNodoArbol(arbol-> izq, idCliente);
        }else if(idCliente == arbol-> dato.idCliente){ /// una vez que encontramos el idCliente
            if(arbol-> izq){ // si el nodo que encontramos tiene un hijo a la izquierda y/o derecha
                arbol-> dato = (nodoMasDer(arbol-> izq))-> dato; // el nodo a borrar ahora va ser el nodo mas grande del lado izquierdo (el mayor de los menores)

                arbol-> izq = borrarNodoArbol(arbol-> izq, arbol-> dato.idCliente); // ahora lo que hace es buscar el nodo que subimos en la linea anterior y lo borramos del arbol
            }else if(arbol-> der){  /// si el nodo que encontramos tiene un hijo a la derecha
                arbol-> dato = (nodoMasIzq(arbol-> der))-> dato; // el nodo a borrar ahora va ser el nodo mas pequeno del lado derecho (el menor de los mayores)

                arbol-> der = borrarNodoArbol(arbol-> der, arbol-> dato.idCliente); // ahora lo que hace es buscar el nodo que subimos en la linea anterior y lo borramos del arbol
            }else{ /// En caso de que el nodo sea Hoja
                borrarLista(arbol->listaDePedidos);
                arbol = NULL;
            }
        }
    }
    return arbol;
}

nodoArbolCliente* nodoMasIzq(nodoArbolCliente* arbol){ // devuelve el nodo en el extremo izquierdo del arbol
    if(arbol-> izq){
        arbol = nodoMasIzq(arbol-> izq);
    }
    return arbol; // si el arbol esta vacio retorna NULL
}

nodoArbolCliente* nodoMasDer(nodoArbolCliente* arbol){ // devuelve el nodo en el extremo derecho del arbol
    if(arbol-> der){
        arbol = nodoMasDer(arbol-> der);
    }
    return arbol; // si el arbol esta vacio retorna NULL
}

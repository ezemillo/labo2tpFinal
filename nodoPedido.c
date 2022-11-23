#include "nodoPedido.h"


//crearListaDePedidoPoridCliente
//crearNodoPedido
//agregarPedidoAlFinal (pasar solo los pedidos que estan activos? o todos?) agregar al final porque estan ordenados por fecha de creacion

nodoPedido* crearNodoPedido(stPedido unPedido)
{

    nodoPedido * unNodo = (nodoPedido*) malloc(sizeof(nodoPedido));
    unNodo->pedido = unPedido;
    unNodo->siguiente = NULL;
    unNodo->modificado=0;

    return unNodo;
}


nodoPedido* buscarUltimoNodoPedido(nodoPedido* lista)
{
    nodoPedido* seg = lista;

    if(seg != NULL)
    {
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}

nodoPedido* agregarNodoFinal(nodoPedido* unNodo, nodoPedido* lista)
{

    if(!lista)
    {
        lista = unNodo;
    }
    else
    {
        buscarUltimoNodoPedido(lista)->siguiente = unNodo;
    }

    return lista;
}


nodoPedido * agregarAlPpio(nodoPedido* lista, nodoPedido* nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        nuevo->siguiente=lista;
        lista = nuevo;
    }
    return lista;
}



nodoPedido* crearListaPedidosPorIdcliente(int idCliente, char archivoPedidos[])
{

    stPedido arregloPedidos[100];
    nodoPedido* lista = NULL;
    int comprobar = -1;
    FILE* archivo= fopen(archivoPedidos, "rb");
    if (archivo)
    {
        stPedido P;
        while (fread(&P,sizeof(stPedido),1,archivo)>0)
        {
            if (idCliente==P.idCliente)
            {
                comprobar=0;
            }
        }
        fclose(archivo);
    }

    int validos = pasarPedidoPoridClienteaArreglo(idCliente,arregloPedidos,100,archivoPedidos);

    if(comprobar==0)
    {
        for(int i=0; i<validos ; i++)
        {
            lista = agregarNodoFinal(crearNodoPedido(arregloPedidos[i]), lista);
        }
    }

    return lista;
}



void mostrarListaPedidos (nodoPedido* lista)
{
    while (lista)
    {
        mostrarPedido(lista->pedido);
        lista=lista->siguiente;
    }

}


int agarrarFecha(char DDMMAA[])
{

    int m0 = DDMMAA[3]-48;


    int m1=DDMMAA[0]-48;
    int m2=DDMMAA[1]-48;
    int m3=DDMMAA[4]-48;
    int m4=DDMMAA[6]-48;
    int m5=DDMMAA[7]-48;
    return m5*100000+m4*10000+m0*1000+m3*100+m2*10+m1*1;
}

nodoPedido* agregarOrdenadoxFecha (nodoPedido* lista, nodoPedido* nuevo)
{

    if (!lista)  //Si la lista esta vacia, esta oredenada
    {
        lista = nuevo;
    }
    else
    {

        //Sie el nuevo nodoPedido es menor a la lista

        if (agarrarFecha(nuevo->pedido.fecha)<= agarrarFecha(lista->pedido.fecha))
        {

            lista=agregarAlPrincipio(lista,nuevo);
        }
        else
        {


            nodoPedido* ante=lista;
            nodoPedido* seguidora = lista;

            while (seguidora&&(agarrarFecha (nuevo->pedido.fecha ) > agarrarFecha (seguidora->pedido.fecha)))
            {
                ante=seguidora;
                seguidora=seguidora->siguiente;

            }

            //Insertar el nuevo nodo en la lista de manera ordenada
            nuevo->siguiente=seguidora;
            ante->siguiente=nuevo;

        }


    }

    return lista;

}

nodoPedido* borrarLista(nodoPedido* lista)
{
    nodoPedido* aux=NULL;
    while(lista)
    {
        aux=lista;
        lista=lista->siguiente;
        free(aux);
    }
    return lista;
}

nodoPedido* agregarAlPrincipio (nodoPedido* lista, nodoPedido* nuevo)
{

    nuevo->siguiente=lista;
    return nuevo;
}

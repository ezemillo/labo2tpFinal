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
        while(seg->siguiente != NULL)
            seg = seg->siguiente;

    return seg;
}

nodoPedido* agregarNodoFinal(nodoPedido* unNodo, nodoPedido* lista)
{

    nodoPedido * seg = lista;

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

nodoPedido* crearListaPedidosPorIdcliente(int idCliente, char archivoPedidos[]){

stPedido arregloPedidos[100];
nodoPedido* lista = NULL;
int validos = pasarPedidoPoridClienteaArreglo(idCliente,arregloPedidos,100,archivoPedidos);

for(int i=0; i<validos ; i++){
   lista = agregarNodoFinal(crearNodoPedido(arregloPedidos[i]),lista);
}

return lista;
}

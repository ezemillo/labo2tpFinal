#ifndef NODOPEDIDO_H_INCLUDED
#define NODOPEDIDO_H_INCLUDED

#include "pedidos.h"
typedef struct nodoPedido
{
    stPedido pedido;
    int modificado;    /// 0 si no se modifico
    struct nodoPedido* siguiente;
} nodoPedido;
nodoPedido* crearNodoPedido(stPedido unPedido);
nodoPedido* buscarUltimoNodoPedido(nodoPedido* lista);
nodoPedido* agregarNodoFinal(nodoPedido* unNodo, nodoPedido* lista);
nodoPedido* crearListaPedidosPorIdcliente(int idCliente, char archivoPedidos[]);


#endif // NODOPEDIDO_H_INCLUDED

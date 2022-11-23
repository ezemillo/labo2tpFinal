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
void mostrarListaPedidos (nodoPedido* lista);
void mostrarListaPedidosPorCliente(char archivoPedido[], int idCliente, int admin); // vista admin=1
nodoPedido * agregarAlPpio(nodoPedido* lista, nodoPedido* nuevo);
int agarrarFecha(char DDMMAA[]);
nodoPedido* agregarOrdenadoxFecha (nodoPedido* lista, nodoPedido* nuevo);
nodoPedido* borrarLista(nodoPedido* lista);
nodoPedido* agregarAlPrincipio (nodoPedido* lista, nodoPedido* nuevo);



#endif // NODOPEDIDO_H_INCLUDED

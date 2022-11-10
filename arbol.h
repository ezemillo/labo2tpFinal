#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include "clientes.h"
#include "pedidos.h"
#include "productos.h"
#include "menu.h"
#include "nodoPedido.h"


typedef struct _nodoArbolCliente{
	stCliente dato;
    int modificado;
	nodoLista* pedidos;
	struct _nodoArbolCliente* izq;
	struct _nodoArbolCliente* der;
}nodoArbolCliente;

//buscar nodoArbol por idCliente
//insertar lista de pedido en nodoArbol

nodoArbolCliente* crearNodoArbol(stCliente unCliente){

nodoArbolCliente* unNodo = (nodoArbolCliente*)malloc(sizeof(nodoArbolCliente));

unNodo->dato=unCliente;
unNodo->der = NULL;
unNodo->izq= NULL;
unNodo->modificado =0;
unNodo->pedidos = crearListaPedidosPorIdcliente(unCliente.idCliente, "pedidos.bin")

}




#endif // ARBOL_H_INCLUDED

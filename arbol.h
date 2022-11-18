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
	nodoPedido* pedidos;
	struct _nodoArbolCliente* izq;
	struct _nodoArbolCliente* der;
}nodoArbolCliente;

//buscar nodoArbol por idCliente
//insertar lista de pedido en nodoArbol
nodoArbolCliente* inicArbol ();
nodoArbolCliente* crearNodoArbol(stCliente unCliente);
nodoArbolCliente * arrayToArbol (stCliente a[], int base, int tope);
nodoArbolCliente* agregarClienteAlArbol (nodoArbolCliente* arbol, nodoArbolCliente* nuevo);
nodoArbolCliente* buscarClienteEnArbol (nodoArbolCliente* arbol, int id);
nodoArbolCliente* modificarClienteEnArbol (nodoArbolCliente* arbol);

#endif // ARBOL_H_INCLUDED

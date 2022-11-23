#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED


#include "clientes.h"
#include "productos.h"
#include "menu.h"
#include "nodoPedido.h"


typedef struct nodoArbolCliente{
	stCliente dato;
    int modificado;
	nodoPedido* listaDePedidos;
	struct nodoArbolCliente* izq;
	struct nodoArbolCliente* der;


}nodoArbolCliente;

//buscar nodoArbol por idCliente
//insertar lista de pedido en nodoArbol
nodoArbolCliente* inicArbol ();
nodoArbolCliente* crearNodoArbol(stCliente unCliente);
nodoArbolCliente * arrayToArbol (stCliente a[], int base, int tope);
nodoArbolCliente* agregarClienteAlArbol (nodoArbolCliente* arbol, nodoArbolCliente* nuevo);
nodoArbolCliente* buscarClienteEnArbol (nodoArbolCliente* arbol, int id);
int solicitarIdCliente();
void modificarClienteEnArbol (nodoArbolCliente* arbol);
void preOrden(nodoArbolCliente* arbol);
void muestraUnCliente(stCliente c);
nodoArbolCliente* cargarArbolDesdeArchivoCliente (char archivoCliente[]);
float liquidarClientePorFecha(nodoPedido* lista, int fecha);
int getMesAnoDeFecha(char fecha[]);
void mostrarListaPedidosPorCliente(char archivoPedido[], int idCliente, int admin); // vista admin=1
void sobreescribirClienteEnArchivo (char ruta [], stCliente C);
nodoArbolCliente* nodoMasDer(nodoArbolCliente* arbol);
nodoArbolCliente* nodoMasIzq(nodoArbolCliente* arbol);
nodoArbolCliente* borrarNodoArbol(nodoArbolCliente* arbol, int idCliente);



#endif // ARBOL_H_INCLUDED

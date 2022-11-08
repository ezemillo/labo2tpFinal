#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED



typedef struct _nodoArbolCliente{
	stCliente dato;
    int modificado;
	nodoLista* pedidos;
	struct _nodoArbolCliente* izq;
	struct _nodoArbolCliente* der;
}nodoArbolCliente;


#endif // ARBOL_H_INCLUDED

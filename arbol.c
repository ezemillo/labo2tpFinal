#include "arbol.h"
#include "nodoPedido.h"

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
    unNodo->pedidos = crearListaPedidosPorIdcliente(unCliente.idCliente, "pedidos.bin");
    return unNodo;

}
nodoArbolCliente * arrayToArbol (stCliente a[], int base, int tope)
{
    int medio;

    nodoArbolCliente* arbol=NULL;

    if(!(base>tope))
    {
        medio=(base+tope)/2;
        arbol=crearNodoArbol(a[medio]);
        arbol->izq=arrayToArbol(a,base,medio-1);
        arbol->der=arrayToArbol(a,medio+1,tope);
    }

    return arbol;
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
/*
nodoArbolCliente* modificarClienteEnArbol (nodoArbolCliente* arbol)
{
    int id;
    nodoArbolCliente* encontrado =NULL;
    printf("\nIngrese Id:");
    scanf("%d",&id);
    encontrado= buscarClienteEnArbol(arbol, id);
//// que tendriamos que hacer si encuentro el nodo como lo modifico y lo vuelvo a meter en el mismo lugar tendria que trabajar sobre otra funcion que me retorne el mismo nodo


}
*/


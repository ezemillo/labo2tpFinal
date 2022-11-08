

nodoArbol* arrayToArbol (stCliente a[], int base, int tope){
    int medio;

    nodoArbol* arbol=NULL;

    if(!(base>tope))
    {
        medio=(base+tope)/2;
        arbol=CrearArbol(a[medio]);
        arbol->izq=arrayToArbol(a,base,medio-1);
        arbol->der=arrayToArbol(a,medio+1,tope);
    }

    return arbol;
}



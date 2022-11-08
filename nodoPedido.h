#ifndef NODOPEDIDO_H_INCLUDED
#define NODOPEDIDO_H_INCLUDED

typedef struct _nodoPedido{
	stPedido pedido;
    int modificado;    /// 0 si no se modifico
	struct _nodoPedido* sig;
}nodoPedido;
//crearListaDePedidoPoridCliente
//crearNodoPedido
//agregarPedidoAlFinal (pasar solo los pedidos que estan activos? o todos?) agregar al final porque estan ordenados por fecha de creacion



#endif // NODOPEDIDO_H_INCLUDED

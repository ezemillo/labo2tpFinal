#ifndef NODOPEDIDO_H_INCLUDED
#define NODOPEDIDO_H_INCLUDED

typedef struct _nodoPedido{
	stPedido pedido;
    int modificado;    /// 0 si no se modifico
	struct _nodoPedido* sig;
}nodoPedido;



#endif // NODOPEDIDO_H_INCLUDED

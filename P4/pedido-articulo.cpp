#include "pedido-articulo.hpp"

//OPERADORES FUERA DE CLASE
std::ostream& operator <<(std::ostream& o, const Pedido_Articulo::ItemsPedido& items) {
	o << "  PVP\tCantidad\t\tArtículo"
	<< "\n===================================================================\n";
	double total=0.0;
	for(auto i:items) {
		const Articulo& articulo=*i.first;
		const LineaPedido& linea=i.second;
		total+=linea.precio_venta()*linea.cantidad();
		o << linea << "\t\t["	//linea imprime el precio y la cantidad
		<< articulo.referencia() << "]"
		<< " \"" << articulo.titulo() << "\"\n";
	}
	o << "===================================================================\n"
	<< "Total     \t" << std::fixed << std::setprecision(2) << total << " €" << std::endl;
	return o;
}

std::ostream& operator <<(std::ostream& o, const Pedido_Articulo::Pedidos& pedidos) {
	size_t n_pedidos=pedidos.size();
	o << "[Pedidos: " << n_pedidos
	<< "]\n" << "===================================================================\n"
	<< "  PVP\tCantidad\t\tFecha de venta\n"
	<< "===================================================================\n";
	double total=0.0;
	double cant_total=0.0;
	for(auto i:pedidos) {
		const Pedido& pedido=*i.first;
		const LineaPedido& linea=i.second;
		total+=linea.precio_venta()*linea.cantidad();;
		cant_total+=linea.cantidad();
		o << linea << "\t\t"	//linea imprime el precio y la cantidad
		<< pedido.fecha() << "\n";
	}
	o << "===================================================================\n"
	<< std::fixed << std::setprecision(2) << total
	<< " € \t" << std::setprecision(0) << cant_total << std::endl;
	return o;
}
//FIN OPERADORES FUERA DE CLASE

//MOSTRAR INFORMACIÓN
void Pedido_Articulo::mostrarDetallePedidos(std::ostream& o) {
	double total=0.0;
	for(auto i:ADirecta_) {
		const Pedido& pedido=*i.first;
		const ItemsPedido& items=i.second;
		total+=pedido.total();
		o << "Pedido núm. " << pedido.numero()
		<< "\nCliente: " << pedido.tarjeta()->titular()->id()
		<< "\t\tFecha: " << pedido.fecha() << "\n" << items;
	}
	o << "\nTOTAL VENTAS\t\t" << total << " €" << std::endl;
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream& o) {
	for(auto i:AInversa_) {
		const Articulo& articulo=*i.first;
		const Pedidos& pedidos=i.second;
		o << "Ventas de [" << articulo.referencia() << "] \"" << articulo.titulo() << "\"\n"
		<< pedidos << std::endl;
	}
}
//FIN MOSTRAR INFORMACIÓN

//LINEAPEDIDO

//OPERADORES FUERA DE CLASE
std::ostream& operator <<(std::ostream& o, const LineaPedido& linea) {
	o << std::fixed << std::setprecision(2) 
	<< linea.precio_venta() << " €\t"
	<< linea.cantidad();
	return o;
}
//FIN OPERADORES FUERA DE CLASE
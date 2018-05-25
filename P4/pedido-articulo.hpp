#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include "pedido.hpp"
#include "usuario.hpp"
#include <set>
#include <map>

class Pedido;
class Articulo;

class LineaPedido {
	public:
		//CONSTRUCTORES
		explicit LineaPedido(double p_venta, unsigned cantidad=1u): p_venta_(p_venta), cantidad_(cantidad) {}
		//FIN CONSTRUCTORES
		//MÉTODOS OBSERVADORES
		double precio_venta() const noexcept {return p_venta_;}
		unsigned cantidad() const noexcept {return cantidad_;}
		//FIN MÉTODOS OBSERVADORES
	private:
		double p_venta_;
		unsigned cantidad_;
};

//OPERADORES FUERA DE CLASE
std::ostream& operator <<(std::ostream& o, const LineaPedido& linea);
//FIN OPERADORES FUERA DE CLASE

class OrdenaPedidos {
	public:
		bool operator()(const Pedido* ped1, const Pedido* ped2) const noexcept {
			return ped1->numero() < ped2->numero();
		}
};

class OrdenaArticulos {
	public:
		bool operator()(const Articulo* art1, const Articulo* art2) const noexcept {
			return art1->referencia() < art2->referencia();
		}
};

class Pedido_Articulo {
	public:
		typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
		typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
		//MÉTODOS PARA ASOCIAR
		void pedir(Pedido& pedido, Articulo& articulo, double precio, unsigned cantidad=1) {
			LineaPedido lineap(precio, cantidad);
			ADirecta_[&pedido].insert(std::make_pair(&articulo, lineap));
			AInversa_[&articulo].insert(std::make_pair(&pedido, lineap));
		}
		void pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned cantidad=1) {
			pedir(pedido, articulo, precio, cantidad);
		}
		//FIN MÉTODOS PARA ASOCIAR
		//MÉTODOS OBSERVADORES
		const ItemsPedido& detalle(Pedido& p) noexcept {
			return ADirecta_[&p];
		}
		const Pedidos ventas(Articulo& a) noexcept {
			return AInversa_[&a];
		}
		//FIN MÉTODOS OBSERVADORES
		//MOSTRAR INFORMACIÓN
		void mostrarDetallePedidos(std::ostream& o);
		void mostrarVentasArticulos(std::ostream& o);
		//FIN MOSTRAR INFORMACIÓN
	private:
		std::map<Pedido*, ItemsPedido, OrdenaPedidos> ADirecta_;
		std::map<Articulo*, Pedidos, OrdenaArticulos> AInversa_;
};

//OPERADORES FUERA DE CLASE
std::ostream& operator <<(std::ostream& o, const Pedido_Articulo::ItemsPedido& items);
std::ostream& operator <<(std::ostream& o, const Pedido_Articulo::Pedidos& pedidos);
//FIN OPERADORES FUERA DE CLASE

#endif
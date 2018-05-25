#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "usuario.hpp"
#include "tarjeta.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido {
	public:
		//CONTRUCTORES
		Pedido(Usuario_Pedido& usuario_pedido, Pedido_Articulo& pedido_articulo, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha=Fecha());
		//FIN CONSTRUCTORES
		//CLASE DE EXCEPCIÓN VACÍO
		class Vacio {
			public:
				Vacio(const Usuario& user): user_(&user) {}
				const Usuario& usuario() const noexcept {return *user_;}
			private:
				const Usuario* user_;
		};
		//FIN CLASE DE EXCEPCIÓN VACÍO
		//CLASE DE EXCEPCIÓN IMPOSTOR
		class Impostor {
			public:
				Impostor(const Usuario& user): user_(&user) {}
				const Usuario& usuario() const noexcept {return *user_;}
			private:
				const Usuario* user_;
		};
		//FIN CLASE DE EXCEPCIÓN IMPOSTOR
		//CLASE DE EXCEPCIÓN SINSTOCK
		class SinStock {
			public:
				SinStock(const Articulo& art): art_(&art) {}
				const Articulo& articulo() const noexcept {return *art_;}
			private:
				const Articulo* art_;
		};
		//FIN CLASE DE EXCEPCIÓN SINSTOCK
		//OBSERVADORES
		int numero() const noexcept {return numero_;}
		const Tarjeta* tarjeta() const noexcept {return tarjeta_;}
		Fecha fecha() const noexcept {return fecha_;}
		double total() const noexcept {return importe_venta_;}
		static int n_total_pedidos() noexcept {return total_;}
		//FIN OBSERVADORES
	private:
		int numero_;
		const Tarjeta* tarjeta_;
		Fecha fecha_;
		double importe_venta_;
		static int total_;
};

//OPERADORES FUERA DE CLASE
std::ostream& operator <<(std::ostream& o, const Pedido& ped);
//FIN OPERADORES FUERA DE CLASE

#endif
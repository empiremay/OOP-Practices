#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include "pedido.hpp"
#include <set>
#include <map>

class Usuario_Pedido {
	public:
		typedef std::set<Pedido*> Pedidos;
		//MÉTODOS ASOCIA
		void asocia(Usuario& u, Pedido& p) {
			usuario_pedidos_[&u].insert(&p);
			pedidos_usuario_[&p]=&u;
		}
		void asocia(Pedido& p, Usuario& u) {
			asocia(u, p);
		}
		//FIN MÉTODOS ASOCIA
		//MÉTODOS OBSERVADORES
		const Pedidos& pedidos(Usuario& u) noexcept {
			return usuario_pedidos_[&u];
		}
		const Usuario* cliente(Pedido& p) noexcept {
			return pedidos_usuario_[&p];
		}
		//FIN MÉTODOS OBSERVADORES
	private:
		typedef std::map<Usuario*, Pedidos> AD;
		typedef std::map<Pedido*, Usuario*> AI;
		AD usuario_pedidos_;
		AI pedidos_usuario_;
};

#endif
#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

int Pedido::total_=0;

//CONTRUCTORES
Pedido::Pedido(Usuario_Pedido& usuario_pedido, Pedido_Articulo& pedido_articulo, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha): numero_(total_+1), tarjeta_(&tarjeta), fecha_(fecha), importe_venta_(0.0) {
	//Comprobaciones para posibles casos de excepción
	if(usuario.n_articulos()==0) throw Vacio(usuario);
	if(tarjeta.titular()!=(&usuario)) throw Impostor(usuario);
	if(tarjeta.caducidad()<fecha_) throw Tarjeta::Caducada(tarjeta.caducidad());
	Usuario::Articulos compras=usuario.compra();

	int contador=0;	//Contador para comprobar que el carrito solo tiene libros digitales expirados
	int contcomp=0;
	for(auto i: compras) {
		//std::cout << "Esto deberia imprimirse varias veces" << std::endl;
		contcomp++;
		Articulo* art=i.first;
		unsigned exist=i.second;
		//Comprobar si el libro del carrito está expirado
		ArticuloAlmacenable* artalm=dynamic_cast<ArticuloAlmacenable*>(art);
		LibroDigital* libdig=dynamic_cast<LibroDigital*>(art);
		//Comprobar si el libro está expirado
		if(libdig && libdig->f_expir()<fecha_)  {
			//No añadir ebook al pedido
			usuario.compra(*libdig, 0);
			contador++;
		}
		else {
			if(artalm && (artalm->stock() < exist)) {
				//Vaciar carrito
				auto c=usuario.compra();
				for(auto& j: c) {
					const Articulo& art2=*j.first;
					usuario.compra(art2,0);
				}
				//Fin vaciar carrito
				throw SinStock(*art);
			}
		}
	}
	if(contador==contcomp) {
		throw Vacio(usuario);
	}
	//Fin comprobaciones para posibles casos de excepción
	total_++;
	auto c=usuario.compra();
	for(auto k: usuario.compra()) {
		Articulo& art3=*k.first;
		ArticuloAlmacenable* artalm2=dynamic_cast<ArticuloAlmacenable*>(&art3);
		unsigned disp=k.second;
		//Añadir articulo al pedido
		pedido_articulo.pedir(*this, art3, art3.precio(), disp);
		//Actualizar existencias
		if(artalm2) {
			artalm2->stock()-=disp;
		}
		importe_venta_+=disp*art3.precio();
	}
	for(auto& j: c) {
		const Articulo& art4=*j.first;
		usuario.compra(art4,0);
	}
	//Asociar pedido al usuario
	usuario_pedido.asocia(usuario, *this);
}
//FIN CONSTRUCTORES

//OPERADORES FUERA DE CLASE
std::ostream& operator <<(std::ostream& o, const Pedido& ped) {
	o << "Núm. pedido: " << ped.numero()
	<< "\nFecha:       " << ped.fecha()
	<< "\nPagado con:  " << ped.tarjeta()->tipo() << " n.º: " << ped.tarjeta()->numero()
	<< "\nImporte:     " << std::fixed << std::setprecision(2)
	<< ped.total() << " €" << std::endl;
	return o;
}
//FIN OPERADORES FUERA DE CLASE


#include "articulo.hpp"

std::ostream& operator <<(std::ostream& o, const Articulo& art) {
	o << "[" << art.referencia() << "] \"" << art.titulo()
	<< "\", de ";

	//Recorrer todos los autores
	Articulo::Autores::iterator ini=art.autores().begin();
	Articulo::Autores::iterator fin=art.autores().end();

	o << (*ini)->apellidos();
	ini++;

	for(auto i=ini; i!=fin; i++) {
		o << ", " << (*i)->apellidos();
	}

	o << ". " << art.f_publi().anno() << ". "
	<< std::fixed << std::setprecision(2) << art.precio() << " €\n\t";
	art.impresion_especifica(o);
	return o;
}

//MÉTODO IMPRESIÓN ESPECÍFICA
inline void Libro::impresion_especifica(std::ostream& o) const noexcept {
	o << n_pag_ << " págs., " << stock_ << " unidades.";
}
//FIN MÉTODO IMPRESIÓN ESPECÍFICA

//MÉTODO IMPRESIÓN ESPECÍFICA
inline void Cederron::impresion_especifica(std::ostream& o) const noexcept {
	o << tam_ << " MB, " << stock_ << " unidades.";
}
//FIN MÉTODO IMPRESIÓN ESPECÍFICA

//MÉTODO IMPRESIÓN ESPECÍFICA
inline void LibroDigital::impresion_especifica(std::ostream& o) const noexcept {
	o << "A la venta hasta el " << f_expir_ << ".";
}
//FIN MÉTODO IMPRESIÓN ESPECÍFICA
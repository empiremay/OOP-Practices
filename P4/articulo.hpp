// Práctica 4 POO
#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <iomanip>
#include <set>

class Autor;

class Articulo {
	public:
		typedef std::set<Autor*> Autores;
		//EXCEPCIÓN ARTICULOS_VACIOS
		class Autores_vacios {

		};
		//FIN EXCEPCIÓN ARTICULOS_VACIOS
		//CONSTRUCTORES
		Articulo(const Autores& a, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha_publi, double precio): autores_(a), cod_ref_(referencia), titulo_(titulo), fecha_publi_(fecha_publi), precio_(precio) {
			if(autores_.empty()) throw Autores_vacios();
		}
		//FIN CONSTRUCTORES
		//OBSERVADORES
		const Cadena& referencia() const noexcept {return cod_ref_;}
		const Cadena& titulo() const noexcept {return titulo_;}
		const Fecha& f_publi() const noexcept {return fecha_publi_;}
		double precio() const noexcept {return precio_;}
		const Autores& autores() const noexcept {return autores_;}
		//FIN OBSERVADORES
		//MODIFICADORES
		double& precio() noexcept {return precio_;}
		//FIN MODIFICADORES
		//MÉTODO IMPRESIÓN ESPECÍFICA
		virtual void impresion_especifica(std::ostream& o) const noexcept =0;
		//FIN MÉTODO IMPRESIÓN ESPECÍFICA
		//DESTRUCTOR
		virtual ~Articulo() {}
		//DESTRUCTOR
	private:
		Autores autores_;
		Cadena cod_ref_;
		Cadena titulo_;
		Fecha fecha_publi_;
		double precio_;
};

//OPERADORES FUERA DE CLASE
std::ostream& operator <<(std::ostream& o, const Articulo& art);
//FIN OPERADORES FUERA DE CLASE

class Autor {
	public:
		//CONSTRUCTOR
		Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& dir) noexcept: nombre_(nombre), apellidos_(apellidos), dir_(dir) {}
		//FIN CONSTRUCTOR
		//OBSERVADORES
		const Cadena& nombre() const noexcept {return nombre_;}
		const Cadena& apellidos() const noexcept {return apellidos_;}
		const Cadena& direccion() const noexcept {return dir_;}
		//FIN OBSERVADORES
	private:
		Cadena nombre_;
		Cadena apellidos_;
		Cadena dir_;
};

//CLASES DERIVADAS
class ArticuloAlmacenable: public Articulo {
	public:
		//CONSTRUCTOR
		ArticuloAlmacenable(const Autores& a, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha_publi, double precio, unsigned stock=0): Articulo(a, referencia, titulo, fecha_publi, precio), stock_(stock) {}
		//FIN CONSTRUCTOR
		//OBSERVADOR
		unsigned stock() const noexcept {return stock_;}
		//FIN OBSERVADOR
		//MODIFICADOR
		unsigned& stock() noexcept {return stock_;}
		//FIN MODIFICADOR
	protected:
		unsigned stock_;
};

class Libro: public ArticuloAlmacenable {
	public:
		//CONSTRUCTOR
		Libro(const Autores& a, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha_publi, double precio, unsigned paginas, unsigned stock=0): ArticuloAlmacenable(a, referencia, titulo, fecha_publi, precio, stock), n_pag_(paginas) {}
		//FIN CONSTRUCTOR
		//OBSERVADOR
		unsigned n_pag() const noexcept {return n_pag_;}
		//FIN OBSERVADOR
		//MÉTODO IMPRESIÓN ESPECÍFICA
		void impresion_especifica(std::ostream& o) const noexcept;
		//FIN MÉTODO IMPRESIÓN ESPECÍFICA
	private:
		unsigned n_pag_;
};

class Cederron: public ArticuloAlmacenable {
	public:
		//CONSTRUCTOR
		Cederron(const Autores& a, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha_publi, double precio, unsigned tamano, unsigned stock=0): ArticuloAlmacenable(a, referencia, titulo, fecha_publi, precio, stock), tam_(tamano) {}
		//FIN CONSTRUCTOR
		//OBSERVADORES
		unsigned tam() const noexcept {return tam_;}
		//FIN OBSERVADORES
		//MÉTODO IMPRESIÓN ESPECÍFICA
		void impresion_especifica(std::ostream& o) const noexcept;
		//FIN MÉTODO IMPRESIÓN ESPECÍFICA
	private:
		unsigned tam_;
};

class LibroDigital: public Articulo {
	public:
		//CONSTRUCTOR
		LibroDigital(const Autores& a, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha_publi, double precio, const Fecha& expir): Articulo(a, referencia, titulo, fecha_publi, precio),  f_expir_(expir) {}
		//FIN CONSTRUCTOR
		//OBSERVADOR
		const Fecha& f_expir() const noexcept {return f_expir_;}
		//FIN OBSERVADOR
		//MÉTODO IMPRESIÓN ESPECÍFICA
		void impresion_especifica(std::ostream& o) const noexcept;
		//FIN MÉTODO IMPRESIÓN ESPECÍFICA
	private:
		Fecha f_expir_;
};
//FIN CLASES DERIVADAS

#endif

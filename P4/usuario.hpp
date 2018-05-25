#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "../P1/cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

extern "C" {
	#include <unistd.h>
}

#include <random>
#include <map>
#include <unordered_map>
//#include <set>
#include <unordered_set>

class Tarjeta;
class Numero;

class Clave {
	public:
		enum Razon{CORTA, ERROR_CRYPT};
		//CONSTRUCTORES
		Clave(const char* contra);
		//FIN CONSTRUCTORES
		//OBSERVADORES
		const Cadena& clave() const noexcept {return clave_;}
		//FIN OBSERVADORES
		//OTROS M�TODOS
		bool verifica(const char* contra) const {return strcmp(crypt(contra, clave_.c_str()), clave_.c_str())==0;}
		//FIN OTROS M�TODOS
		//CLASE DE EXCEPCI�N INCORRECTA
		class Incorrecta {
			public:
				Incorrecta(Razon razon): razon_(razon) {}
				Razon razon() const {return razon_;}
			private:
				Razon razon_;
		};
		//FIN CLASE DE EXCEPCI�N INCORRECTA
	private:
		Cadena clave_;
};

class Usuario {
	public:
		typedef std::map<Numero, Tarjeta*> Tarjetas;
		typedef std::unordered_map<Articulo*, unsigned int> Articulos;
		typedef std::unordered_set<Cadena> Usuarios;
		//CONSTRUCTOR
		Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& dir, const Clave& contra);
		//FIN CONSTRUCTOR
		//CLASE DE EXCEPCION ID_DUPLICADO
		class Id_duplicado {
			public:
				Id_duplicado(const Cadena& id): id_(id) {}
				const Cadena& idd() const {return id_;}
			private:
				Cadena id_;
		};
		//FIN CLASE DE EXCEPCION ID_DUPLICADO
		//M�TODOS OBSERVADORES
		const Cadena& id() const noexcept {return id_;}
		const Cadena& nombre() const noexcept {return nombre_;}
		const Cadena& apellidos() const noexcept {return apellidos_;}
		const Cadena& direccion() const noexcept {return dir_;}
		const Tarjetas& tarjetas() const noexcept {return tarjetas_;}
		const Articulos& compra() const noexcept {return articulos_;}
		size_t n_articulos() const {return articulos_.size();}
		//FIN M�TODOS OBSERVADORES
		//NO COPIAS POR DEFECTO
		Usuario(const Usuario& usuario)=delete;
		Usuario& operator =(const Usuario& usuario)=delete;
		//FIN NO COPIAS POR DEFECTO
		//M�TODOS DE ASOCIACI�N
		void es_titular_de(const Tarjeta& tarj);
		void no_es_titular_de(Tarjeta& tarj);
		void compra(const Articulo& articulo, unsigned cantidad=1);
		//FIN M�TODOS DE ASOCIACI�N
		//OPERADOR DE INSERCI�N
		friend std::ostream& operator <<(std::ostream& o, const Usuario& usuario);
		//FIN OPERADOR DE INSERCI�N
		//DESTRUCTOR
		~Usuario();
		//FIN DESTRUCTOR
	private:
		Cadena id_;
		Cadena nombre_;
		Cadena apellidos_;
		Cadena dir_;
		Clave contra_;
		Tarjetas tarjetas_;
		Articulos articulos_;
		static Usuarios usuarios_;
};

//OPERADORES FUERA DE CLASE
std::ostream& mostrar_carro(std::ostream& o, const Usuario& usuario);
//FIN OPERADORES FUERA DE CLASE

#endif

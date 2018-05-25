#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
//#include "usuario.hpp"
#include <iomanip>

class Usuario;

class Numero {
	public:
		enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
		//CONSTRUCTORES
		Numero(const Cadena& numero);
		//FIN CONSTRUCTORES
		//CLASE DE EXCEPCIÓN INCORRECTO
		class Incorrecto {
			public:
				Incorrecto(Razon razon): razon_(razon) {}
				Razon razon() const {return razon_;}
			private:
				Razon razon_;
		};
		//FIN CLASE DE EXCEPCIÓN INCORRECTO
		//OPERADORES DE CONVERSIÓN
		operator const char*() const noexcept;
		//FIN OPERADORES DE CONVERSIÓN
	private:
		Cadena numero_;
};

//OPERADORES FUERA DE CLASE
bool operator <(const Numero& num1, const Numero& num2);
//FIN OPERADORES FUERA DE CLASE

class Usuario;

class Tarjeta {
	public:
		enum Tipo {VISA, Mastercard, Maestro, JCB, AmericanExpress};
		//CONSTRUCTORES
		Tarjeta(Tipo tipo, const Numero& numero, Usuario& titular, const Fecha& caducidad);
		//FIN CONSTRUCTORES
		//CLASE DE EXCEPCIÓN CADUCADA
		class Caducada {
			public:
				Caducada(const Fecha& caducada): caducada_(caducada) {}
				const Fecha& cuando() const {return caducada_;}
			private:
				Fecha caducada_;
		};
		//FIN CLASE DE EXCEPCIÓN CADUCADA
		//NO PERMITIR COPIAS
		Tarjeta(const Tarjeta& tarjeta)=delete;
		Tarjeta& operator =(const Tarjeta& tarjeta)=delete;
		//FIN NO PERMITIR COPIAS
		//MÉTODOS OBSERVADORES
		Tipo tipo() const {return tipo_;}
		Numero numero() const {return numero_;}
		const Usuario* titular() const {return titular_;}
		Fecha caducidad() const {return caducidad_;}
		Cadena titular_facial() const {return titular_facial_;}
		//FIN MÉTODOS OBSERVADORES
		//MÉTODO ANULA_TITULAR
		void anula_titular();
		//FIN MÉTODO ANULA_TITULAR
		//DESTRUCTOR
		~Tarjeta();
		//FIN DESTRUCTOR
	private:
		Tipo tipo_;
		Numero numero_;
		const Usuario* titular_;
		Fecha caducidad_;
		Cadena titular_facial_;
};

//OPERADORES FUERA DE CLASE
std::ostream& operator <<(std::ostream& o, const Tarjeta& tarjeta);
std::ostream& operator <<(std::ostream& o, const Tarjeta::Tipo& tipo);
bool operator <(const Tarjeta& tar1, const Tarjeta& tar2);
//FIN OPERADORES FUERA DE CLASE

#endif
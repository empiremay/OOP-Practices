#include "tarjeta.hpp"
#include "usuario.hpp"
#include <algorithm>	//std::remove_if

//NUMERO

bool luhn(const Cadena& numero);

//CLASES USADAS EN CONSTRUCTOR
/*class EsBlanco {
	public:
		bool operator()(char i) const {return isspace(i);}
};*/

class EsDigito {
	public:
		bool operator()(char i) const {return isdigit(i);}
};
//FIN CLASES USADAS EN CONSTRUCTOR

//CONSTRUCTORES
Numero::Numero(const Cadena& numero): numero_(numero) {
	//Comprobación inicial de longitud
	if(numero.length()==0) {
		throw Incorrecto(LONGITUD);
	}
	//Retirada de espaciado en blanco
	Cadena::iterator fin=std::remove_if(numero_.begin(), numero_.end(), [](char c) {return std::isspace(c);});

	if(fin!=numero_.end()) {
		*fin='\0';
		Cadena cad(numero_.c_str());
		numero_=cad;
	}

	if(std::find_if(numero_.begin(), numero_.end(), std::not1(std::function<bool(char)>(EsDigito())))!=numero_.end()) {
		throw Incorrecto(DIGITOS);
	}

	size_t j=numero_.length();
	if(j<13 || j>19) throw Incorrecto(LONGITUD);
	if(!luhn(numero_)) throw Incorrecto(NO_VALIDO);
}
//FIN CONSTRUCTORES

//OPERADORES DE CONVERSIÓN
Numero::operator const char*() const noexcept {
	return numero_.c_str();
}
//FIN OPERADORES DE CONVERSIÓN

//OPERADORES FUERA DE CLASE
bool operator <(const Numero& num1, const Numero& num2) {
	return strcmp(num1,num2)<0;
}
//FIN OPERADORES FUERA DE CLASE


//TARJETA

//CONSTRUCTORES
Tarjeta::Tarjeta(Tipo tipo, const Numero& numero, Usuario& titular, const Fecha& caducidad): tipo_(tipo), numero_(numero), titular_(&titular), caducidad_(caducidad), titular_facial_(titular.nombre()+" "+titular.apellidos()) {
	if(caducidad<Fecha()) {
		throw Caducada(caducidad);
	}
	titular.es_titular_de(*this);
}
//FIN CONSTRUCTORES

//MÉTODO ANULA_TITULAR
void Tarjeta::anula_titular() {
	titular_=nullptr;
}
//FIN MÉTODO ANULA_TITULAR

//DESTRUCTOR
Tarjeta::~Tarjeta() {
	Usuario* usuario=const_cast<Usuario*>(titular_);
	//Si existe titular deja de serlo
	if(titular_!=0) {
		usuario->no_es_titular_de(*this);
	}
}
//FIN DESTRUCTOR

//OPERADORES FUERA DE CLASE
std::ostream& operator <<(std::ostream& o, const Tarjeta& tarjeta) {
	o << tarjeta.tipo() << tarjeta.numero() << "\n"
	<< tarjeta.titular_facial() << "\n" << "Caduca: "
	<< std::setfill('0') << std::setw(2)
	<< tarjeta.caducidad().mes() << "/"
	<< std::setw(2)
	<< tarjeta.caducidad().anno()%100 << std::endl;
	return o;
}

std::ostream& operator <<(std::ostream& o, const Tarjeta::Tipo& tipo) {
	switch(static_cast<int>(tipo)) {
		case 0: o << "VISA" << std::endl; break;
		case 1:	o << "Mastercard" << std::endl; break;
		case 2:	o << "Maestro" << std::endl; break;
		case 3:	o << "JCB" << std::endl; break;
		case 4: o << "AmericanExpress" << std::endl; break;
	}
	return o;
}

bool operator <(const Tarjeta& tar1, const Tarjeta& tar2) {
	return tar1.numero()<tar2.numero();
}
//FIN OPERADORES FUERA DE CLASE
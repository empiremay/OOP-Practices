#include "usuario.hpp"
#include "tarjeta.hpp"
//#include <iomanip>

Usuario::Usuarios Usuario::usuarios_;

//CLAVE

Clave::Clave(const char* contra) {
	// La contraseña debe tener al menos 5 caracteres
	if(strlen(contra)<5){
		throw Clave::Incorrecta(Razon::CORTA);
	}
	std::random_device r;
	const char* cadena="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ./0123456789";
	std::uniform_int_distribution<size_t> car(0,sizeof(cadena)-2);

	char cad_aleatoria[]={cadena[car(r)], cadena[car(r)]};
	
	char* encriptada=crypt(contra, cad_aleatoria);
	if(encriptada==nullptr) {
		throw Clave::Incorrecta(Razon::ERROR_CRYPT);
	}
	clave_=encriptada;
}


//USUARIO

//CONSTRUCTOR
Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& dir, const Clave& contra): id_(id), nombre_(nombre), apellidos_(apellidos), dir_(dir), contra_(contra) {
	if(!usuarios_.insert(id).second) {
		throw Id_duplicado(id);
	}
}
//FIN CONSTRUCTOR

//MÉTODOS DE ASOCIACIÓN
void Usuario::es_titular_de(const Tarjeta& tarj) {
	if(tarj.titular()==this) {
		tarjetas_[tarj.numero()]=const_cast<Tarjeta*>(&tarj);
	}
}

void Usuario::no_es_titular_de(Tarjeta& tarj) {
	//Borrar enlace
	tarjetas_.erase(tarj.numero());
}

void Usuario::compra(const Articulo& articulo, unsigned cantidad) {
	if(cantidad!=0) {
		articulos_[const_cast<Articulo*>(&articulo)]=cantidad;
	}
	else {
		articulos_.erase(const_cast<Articulo*>(&articulo));
	}
}
//FIN MÉTODOS DE ASOCIACIÓN

//OPERADOR DE INSERCIÓN
std::ostream& operator <<(std::ostream& o, const Usuario& usuario) {
	o << usuario.id_ << " ["
	<< usuario.contra_.clave() << "] "
	<< usuario.nombre_ << " "
	<< usuario.apellidos_ << "\n"
	<< usuario.dir_ << "\n"
	<< "Tarjetas:" << std::endl;
	for(auto& i:usuario.tarjetas_) {
		o << *i.second << std::endl;
	}
	return o;
}
//FIN OPERADOR DE INSERCIÓN

//DESTRUCTOR
Usuario::~Usuario() {
	for(auto& i:tarjetas_) {
		i.second->anula_titular();
	}
	usuarios_.erase(id_);
}
//FIN DESTRUCTOR

//OPERADORES FUERA DE CLASE
std::ostream& mostrar_carro(std::ostream& o, const Usuario& usuario) {
	o << "Carrito de compra de " << usuario.id()
	<< " [Artículos: " << usuario.n_articulos() << "]"
	<< "\n Cant. "
	<< "Artículo"
	<< "\n===============================================\n";
	for(auto i:usuario.compra()) {
		o << "  " << i.second << "    ["
		<< i.first->referencia()
		<< "] \"" << i.first->titulo()
		<< "\", " << i.first->f_publi().anno()
		<< ". " << std::fixed << std::setprecision(2) << i.first->precio() << " €" << std::endl;
	}
	return o;
}
//FIN OPERADORES FUERA DE CLASE











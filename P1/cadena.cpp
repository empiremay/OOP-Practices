#include "cadena.hpp"

//CONSTRUCTORES
Cadena::Cadena(size_t tam, char s): s_(new char[tam+1]), tam_(tam) {
	// Rellenar con caracter de relleno
	for(int i=0; i<tam_; i++) {
		s_[i]=s;
	}
	s_[tam_]='\0';
}

Cadena::Cadena(const Cadena& c): s_(new char[c.tam_+1]), tam_(c.tam_) {
	//Rellenar la cadena
	strcpy(s_,c.s_);
}

Cadena::Cadena(const char *cad): s_(new char[strlen(cad)+1]), tam_(strlen(cad)) {
	strcpy(s_, cad);
	s_[tam_]='\0';
}

Cadena::Cadena(const char *cad, size_t n): s_(new char[strlen(cad)+1]), tam_(strlen(cad)) {
	if(n<=strlen(cad)) {
		// Copiar los n primeros caracteres
		tam_=n;
		delete[] s_;
		s_=new char[n+1];
		memcpy(s_,cad,n);
		s_[n]='\0';
	}
	else {
		// Copiar la cadena entera
		strcpy(s_, cad);
	}
}

Cadena::Cadena(const Cadena& cad, size_t ini, size_t ncar)/*: s_(new char[cad.tam_+1]), tam_(cad.tam_)*/ {
	// Comprobar que ini no sea mayor que cad.tam_
	if(ini>=cad.length()) {
		throw std::out_of_range("out of range exception");
	}
	// Controlar si npos==-1
	if(ncar==npos || (ini+ncar)>cad.length()) {
		// Copiar hasta el final de la cadena
		tam_=cad.length()-ini;
		s_=new char[tam_+1];
		memcpy(s_,cad.c_str()+ini,tam_);
		s_[tam_]='\0';
	}
	else {
		// Copiar la cadena cad desde ini hasta ini+ncar
		tam_=ncar;
		s_=new char[tam_+1];
		memcpy(s_,cad.c_str()+ini,tam_);
		s_[tam_]='\0';
	}
}
//FIN CONSTRUCTORES

//CONSTRUCTOR DE COPIA Y OPERADOR DE ASIGNACIÓN CON SEMÁNTICA DE MOVIMIENTO
Cadena::Cadena(Cadena&& c): s_(new char[c.tam_+1]), tam_(c.tam_) {
	//Rellenar la cadena
	strcpy(s_,c.s_);
	//Destruir c
	c.s_=nullptr;
	c.tam_=0;
}

Cadena& Cadena::operator =(const char* cad) {
	delete[] s_;
	tam_=strlen(cad);
	s_=new char[tam_+1];
	strcpy(s_, cad);
	return *this;
}

Cadena& Cadena::operator =(Cadena&& c) {
	if(this!=&c) {
		s_=c.s_;
		tam_=c.tam_;
		//Destruir c
		c.s_=nullptr;
		c.tam_=0;
	}
	return *this;
}
//FIN CONSTRUCTOR DE COPIA Y OPERADOR DE ASIGNACIÓN CON SEMÁNTICA DE MOVIMIENTO

//OPERADORES
Cadena& Cadena::operator =(const Cadena& c) {
	if(this!=&c) {
		delete[] s_;
		tam_=c.length();
		s_=new char[tam_+1];
		strcpy(s_, c.s_);
	}
	return *this;
}

const char* Cadena::c_str() const {
	return s_;
}

Cadena& Cadena::operator +=(const Cadena& c) {
	tam_=tam_+c.length();
	char* aux=new char[tam_+1];
	strcpy(aux, s_);
	strcat(aux, c.s_);
	delete[] s_;
	s_=new char[tam_+1];
	strcpy(s_, aux);
	delete[] aux;
	return *this;
}
//FIN OPERADORES

//OPERADORES DE ACCESO A LA CADENA
char Cadena::operator [](size_t pos) const noexcept {
	return s_[pos];
}

char& Cadena::operator [](size_t pos) noexcept {
	return s_[pos];
}

char Cadena::at(size_t pos) const {
	if(pos>=tam_) {
		throw std::out_of_range("No se puede acceder a esta posicion");
	}
	else {
		return s_[pos];
	}
}

char& Cadena::at(size_t pos) {
	if(pos>=tam_) {
		throw std::out_of_range("No se puede acceder a esta posicion");
	}
	else {
		return s_[pos];
	}
}
//FIN OPERADORES DE ACCESO A LA CADENA

//OPERADORES LÓGICOS
bool operator <(const Cadena& c1, const Cadena& c2) {
	return strcmp(c1.c_str(), c2.c_str())<0;
}

bool operator ==(const Cadena& c1, const Cadena& c2) {
	return strcmp(c1.c_str(), c2.c_str())==0;
}

bool operator >(const Cadena& c1, const Cadena& c2) {
	return strcmp(c1.c_str(), c2.c_str())>0;
}

bool operator !=(const Cadena& c1, const Cadena& c2) {
	if(strcmp(c1.c_str(), c2.c_str())!=0) {
		return true;
	} else {
		return false;
	}
}

bool operator <=(const Cadena& c1, const Cadena& c2) {
	return strcmp(c1.c_str(), c2.c_str())<=0;
}

bool operator >=(const Cadena& c1, const Cadena& c2) {
	return strcmp(c1.c_str(), c2.c_str())>=0;
}
//FIN OPERADORES LÓGICOS

//Operador +
Cadena operator +(const Cadena& c1, const Cadena& c2) {
	Cadena cad(c1);
	cad+=c2;
	return cad;
}
//Fin operador +

//FUNCIÓN SUBSTR
Cadena Cadena::substr(size_t ini, int tam) const {
	// Casos en los que da excepción
	if(ini>=tam_ || ini+tam>=tam_ || tam<0) {
		throw std::out_of_range("Fuera de rango");
	}
	else {
		char* cadena=new char[tam+1];
		/*for(int i=0; i<tam; i++) {
			cadena[i]=s_[i+ini];
		}*/
		memcpy(cadena,s_+ini,tam);
		cadena[tam]='\0';
		Cadena cad(cadena);
		delete[] cadena;
		return cad;
	}
}
//FIN FUNCIÓN SUBSTR

Cadena::~Cadena() {
	delete[] s_;
}

//P1 OPERADORES DE INSERCIÓN Y EXTRACCIÓN
std::ostream& operator <<(std::ostream& o, const Cadena& c) {
	o << c.c_str();
	return o;
}

std::istream& operator >>(std::istream& i, Cadena& c) {
	char cadena[32]="";
	i.width(32);
	i >> cadena;
	c=cadena;
	return i;
}
//P1 FIN OPERADORES DE INSERCIÓN Y EXTRACCIÓN




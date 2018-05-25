#ifndef CADENA_HPP
#define CADENA_HPP
#include<iostream>
#include<stdio.h> 
#include<ctime>
#include<cstring>
#include<exception>
#include<stdexcept>
#include<functional>

class Cadena {
	public:
		static const size_t npos=-1;
		typedef char* iterator;
        typedef const char * const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		//CONSTRUCTORES
		explicit Cadena(size_t tam=0, char s=' ');
		Cadena(const Cadena& c);
		Cadena(const char* cad);
		Cadena(const char* cad, size_t n);
		Cadena(const Cadena& cad, size_t ini, size_t ncar=npos);
		//FIN CONSTRUCTORES
		//CONSTRUCTOR DE COPIA Y OPERADOR DE ASIGNACIÓN CON SEMÁNTICA DE MOVIMIENTO
		Cadena(Cadena&& c);
		Cadena& operator =(Cadena&& c);
		//FIN CONSTRUCTOR DE COPIA Y OPERADOR DE ASIGNACIÓN CON SEMÁNTICA DE MOVIMIENTO
		//OPERADORES
		Cadena& operator =(const Cadena& c);
		Cadena& operator =(const char* cad);
		Cadena& operator +=(const Cadena& c);
		//FIN OPERADORES
		//OBSERVADORES
		const char* c_str() const;
		const size_t length() const noexcept {return tam_;}
		//FIN OBSERVADORES
		//OPERADORES DE ACCESO A LA CADENA
		char operator [](size_t pos) const noexcept;
		char& operator [](size_t pos) noexcept;
		char at(size_t pos) const;
		char& at(size_t pos);
		//FIN OPERADORES DE ACCESO A LA CADENA
		//FUNCIÓN SUBSTR
		Cadena substr(size_t ini, int tam) const;
		//FIN FUNCIÓN SUBSTR
		~Cadena();
		//ITERADORES
		iterator begin() noexcept { 
	        return s_;
		}
	    iterator end() noexcept {
	        return s_+tam_;
	    }
	    const_iterator begin() const noexcept {
	        return s_;
	    }
	    const_iterator end() const noexcept {
	        return s_+tam_;
	    }
	    const_iterator cbegin() const noexcept {
	        return s_;
	    }
	    const_iterator cend() const noexcept {
	        return s_+tam_;
	    }
	    reverse_iterator rbegin() noexcept {
	        return reverse_iterator(end());
	    }
	    reverse_iterator rend() noexcept {
	        return reverse_iterator(begin());
	    }
	    const_reverse_iterator rbegin() const noexcept {
	        return const_reverse_iterator(end());
	    }
	    const_reverse_iterator rend() const noexcept {
	        return const_reverse_iterator(begin());
	    }
	    const_reverse_iterator crbegin() const noexcept {
	        return const_reverse_iterator(end());
	    }
	    const_reverse_iterator crend() const noexcept {
	        return const_reverse_iterator(begin());
	    }
	    //FIN ITERADORES
	private:
		char* s_;
		size_t tam_;
};
//Operador +
Cadena operator +(const Cadena& c1, const Cadena& c2);
//Fin operador +

//OPERADORES LÓGICOS
bool operator <(const Cadena& c1, const Cadena& c2);
bool operator ==(const Cadena& c1, const Cadena& c2);
bool operator >(const Cadena& c1, const Cadena& c2);
bool operator !=(const Cadena& c1, const Cadena& c2);
bool operator <=(const Cadena& c1, const Cadena& c2);
bool operator >=(const Cadena& c1, const Cadena& c2);
//FIN OPERADORES LÓGICOS

//P1 OPERADORES DE INSERCIÓN Y EXTRACCIÓN
std::ostream& operator <<(std::ostream& o, const Cadena& c);
std::istream& operator >>(std::istream& i, Cadena& c);
//P1 FIN OPERADORES DE INSERCIÓN Y EXTRACCIÓN

//PARA LA PRÁCTICA P2
// Para P2 y ss.
// Especialización de la plantilla hash<T>para definir la
// función hash a utilizar con contenedores desordenados de
// Cadena, unordered_[set|map|multiset|multimap].
namespace std {
	template <> struct hash<Cadena> {
		size_t operator()(const Cadena& cad) const
		{ // conversión const char* ->string
			return hash<string>{}(cad.c_str());
		}
	};
}
//FIN PARA LA PRÁCTICA P2
#endif

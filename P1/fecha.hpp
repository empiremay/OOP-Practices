#ifndef FECHA_HPP_
#define FECHA_HPP_
#include<iostream>
#include<stdio.h> 
#include<ctime>
#include<cstring>

class Fecha {
	public:
		//CONSTRUCTORES
		explicit Fecha(int dia=0, int mes=0, int anno=0);
		Fecha(const char* cad);
		//FIN CONSTRUCTORES
		static const int AnnoMinimo=1902;
		static const int AnnoMaximo=2037;
		//P1 CADENA
		const char* cadena() const;
		//FIN P1 CADENA
		Fecha& operator++();	//Operador de preincremento
		Fecha operator++(int);	//Operador de postincremento
		Fecha& operator--();	//Operador de predecrecremento
		Fecha operator--(int);	//Operador de postdecrecremento
		Fecha operator+(int dias) const;
		Fecha operator-(int dias) const;
		Fecha& operator+=(int dias);
		Fecha& operator-=(int dias);
		class Invalida {
			public:
				Invalida(const char* motivo): por_que_(motivo) {}
				const char* por_que() const {return por_que_;}
			private:
				const char* por_que_;
		};
		//MÃ‰TODOS OBSERVADORES
		int dia() const noexcept {return dia_;}
		int mes() const noexcept {return mes_;}
		int anno() const noexcept {return anno_;}
		//FIN MÃ‰TODOS OBSERVADORES
	private:
		int dia_, mes_, anno_;
		bool fechaValida() const;
};

//FUNCIONES CON MÃS DE UN PARÃMETRO
long operator-(const Fecha& f1, const Fecha& f2);
//FIN FUNCIONES CON MÃS DE UN PARÃMETRO

//OPERADORES BOOLEANOS
bool operator ==(const Fecha& f1, const Fecha& f2);
bool operator !=(const Fecha& f1, const Fecha& f2);
bool operator >(const Fecha& f1, const Fecha& f2);
bool operator >=(const Fecha& f1, const Fecha& f2);
bool operator <(const Fecha& f1, const Fecha& f2);
bool operator <=(const Fecha& f1, const Fecha& f2);
//FIN OPERADORES BOOLEANOS

//P1 OPERADORES DE INSERCIÓN Y EXTRACCIÓN
std::ostream& operator <<(std::ostream& o, const Fecha& f);
std::istream& operator >>(std::istream& i, Fecha& f);
//P1 FIN OPERADORES DE INSERCIÓN Y EXTRACCIÓN

#endif

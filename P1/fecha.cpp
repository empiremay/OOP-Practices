#include "fecha.hpp"

//FUNCIONES CON MÁS DE UN PARÁMETRO
long operator-(const Fecha& f1, const Fecha& f2) {
	struct std::tm fecha1={0,0,0,f1.dia(), f1.mes()-1, f1.anno()-1900, 0,0,0};
	struct std::tm fecha2={0,0,0,f2.dia(), f2.mes()-1, f2.anno()-1900, 0,0,0};
	std::time_t tiempo1=std::mktime(&fecha1);
	std::time_t tiempo2=std::mktime(&fecha2);
	long diferencia;
	diferencia=static_cast<long int>(difftime(tiempo1,tiempo2)/86400);
	return diferencia;
}
//FIN FUNCIONES CON MÁS DE UN PARÁMETRO

//OPERADORES BOOLEANOS
bool operator ==(const Fecha& f1, const Fecha& f2) {
	return (f1.dia()==f2.dia() && f1.mes()==f2.mes() && f1.anno()==f2.anno());
}

bool operator !=(const Fecha& f1, const Fecha& f2) {
	return !(f1==f2);
}

bool operator <(const Fecha& f1, const Fecha& f2) {
	if(f1.anno()<f2.anno()) {
		return true;
	}
	else {
		if(f1.anno()==f2.anno()) {
			if(f1.mes()<f2.mes()) {
				return true;
			}
			else {
				if(f1.mes()==f2.mes()) {
					if(f1.dia()<f2.dia()) {
						return true;
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}	
	}
}

bool operator >=(const Fecha& f1, const Fecha& f2) {
	return !(f1<f2);
}

bool operator >(const Fecha& f1, const Fecha& f2) {
	return f2<f1;
}

bool operator <=(const Fecha& f1, const Fecha& f2) {
	return !(f2<f1);
}
//FIN OPERADORES BOOLEANOS

bool Fecha::fechaValida() const {
	static int diasMes[]= {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(anno_<AnnoMinimo || anno_>AnnoMaximo) {
		return false;
	}
	if(mes_<1 || mes_>12) {
		return false;
	}
	if(dia_<1 || dia_>31) {
		return false;
	}
	if(diasMes[mes_-1]<dia_) {
		return false;
	}
	//Es febrero
	if(mes_==2) {
		if(anno_%4==0 && (anno_%400==0 || anno_%100!=0)) {
			// Es bisiesto
			if(dia_>29) {
				return false;
			} else {
				return true;
			}
		} else {
			if(dia_>28) {
				return false;
			} else {
				return true;
			}
		}
	}
	return true;
}

//CONSTRUCTORES
Fecha::Fecha(int dia, int mes, int anno): dia_(dia), mes_(mes), anno_(anno) {
	//Asignar fechas del sistema en caso de que sean 0
	std::time_t tiempo_calendario = std::time(0);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
	int d= tiempo_descompuesto->tm_mday;
	int m= tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
	int a= tiempo_descompuesto->tm_year + 1900; // tm_year: a~ nos desde 1900
	if(dia==0) dia_=d;
	if(mes==0) mes_=m;
	if(anno==0) anno_=a;
	//Comprobar que la fecha es válida
	if(!fechaValida()) {
		//Lanzar excepción del tipo Fecha::Invalida
		throw Invalida("Fecha no valida");
	}
}

Fecha::Fecha(const char* cad) {
	time_t tiempo;
	tm *tm;
	tiempo=time(NULL);
	tm=localtime(&tiempo);
    int d,m,a;
    int num=sscanf(cad,"%d/%d/%d",&d,&m,&a);
    if(num!=3) {
    	throw Invalida("Cadena formato incorrecto");
    }
    if(d==0){ dia_=tm->tm_mday; } else { dia_=d; }
    if(m==0){ mes_=1+tm->tm_mon; } else { mes_=m; }
    if(a==0){ anno_=1900+tm->tm_year; } else { anno_=a; }
    if(!fechaValida()) {
		//Lanzar excepción del tipo Fecha::Invalida
		throw Invalida("Fecha no valida");
	}
}
//FIN CONSTRUCTORES

const char* Fecha::cadena() const {
	static char* cadena=new char[50];
    struct tm hoy = { 0, 0, 0, dia_, mes_ - 1, anno_ - 1900, 0, 0, 0 };
    std::mktime (&hoy);
    std::setlocale(LC_TIME,"spanish_Spain");
    std::strftime(cadena,50,"%A %d de %B de %Y",&hoy);
    return cadena;
}

Fecha& Fecha::operator+=(int dias) {
	static int diasMes[]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(dias>0) {
		for(int i=0; i<dias; i++) {
			//Año bisiesto
			if(mes_==2 && anno_%4==0) {
				if(dia_==29) {
					dia_=1;
					mes_++;
				}
				else {
					dia_++;
				}
			}
			//No es año bisiesto
			else {
				if(diasMes[mes_-1]==dia_ && mes_<12) {
					mes_++;
					dia_=1;
				}
				else {
					if(diasMes[mes_-1]==dia_ && mes_==12) {
						mes_=1;
						dia_=1;
						anno_++;
					}
					else {
						if(diasMes[mes_-1]!=dia_) {
							dia_++;
						}
					}
				}
			}
		}
	}
	if(dias<0) {
		for(int i=dias; i<0; i++) {
			//Año bisiesto
			if(mes_==3 && anno_%4==0) {
				if(dia_==1) {
					dia_=29;
					mes_--;
				}
				else {
					dia_--;
				}
			}
			//No es año bisiesto
			else {
				if(dia_==1 && mes_>1) {
					mes_--;
					dia_=diasMes[mes_-1];
				}
				else {
					if(dia_==1 && mes_==1) {
						mes_=12;
						dia_=diasMes[mes_-1];
						anno_--;
					}
					else {
						if(dia_!=1) {
							dia_--;
						}
					}
				}
			}
		}
	}	
	if(!fechaValida()) {
		//Lanzar excepción del tipo Fecha::Invalida
		throw Invalida("Fecha no valida");
	}
	return *this;
}

Fecha& Fecha::operator++() {
	return *this+=1;
}

Fecha Fecha::operator++(int) {
	Fecha temp(*this);
	*this+=1;
	return temp;
}

Fecha& Fecha::operator--() {
	return *this+=-1;
}

Fecha Fecha::operator--(int) {
	Fecha temp(*this);
	*this+=-1;
	return temp;
}

Fecha Fecha::operator+(int dias) const {
	Fecha hoy(*this);
	hoy+=dias;
	return hoy;
}

Fecha Fecha::operator-(int dias) const {
	Fecha hoy(*this);
	hoy+=(-dias);
	return hoy;
}

Fecha& Fecha::operator-=(int dias) {
	*this+=(-dias);
	return *this;
}

//P1 OPERADORES DE INSERCI�N Y EXTRACCI�N
std::ostream& operator <<(std::ostream& o, const Fecha& f) {
	o << f.cadena();	// el m�todo cadena devuelve la fecha en formato const char*
	return o;
}

std::istream& operator >>(std::istream& i, Fecha& f){
	char fecha[11]="";
	i.width(11);
	try {
		i >> fecha;
		f=fecha;
	} catch(Fecha::Invalida) {i.setstate(std::ios::failbit); throw;}
	return i;
}
//P1 FIN OPERADORES DE INSERCI�N Y EXTRACCI�N


VPATH=../Tests-auto:.
#compilador
CXX=clang++
#banderas del compilador
CPPFLAGS = -I../Tests-auto -I. -DP1
CXXFLAGS = -std=c++11 -g -Wall -pedantic
#-fmax-errors=15
#LDFLAGS =
#ficheros creados
EJECUTABLES =test-P1-auto test-P1-consola 
OBJETOS = test-P1-auto.o test-P1-consola.o fecha.o cadena.o
###
all:$(EJECUTABLES)
###
test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o fecha.o cadena.o #test-P0-auto.o
	$(CXX) $(LDFLAGS) $^ -o $@

test-P1-consola: test-P1-consola.o fecha.o cadena.o 
	$(CXX) $(LDFLAGS) $^ -o $@

test-P1-auto.o: test-P1-auto.cpp fecha.hpp cadena.hpp

test-P1-consola.o: test-P1-consola.cpp fecha.hpp cadena.hpp

fecha.o: fecha.cpp fecha.hpp

cadena.o: cadena.cpp cadena.hpp

test-cas0-fecha-auto.o test-caso0-cadena-auto.o: test-auto.hpp fecha.hpp cadena.hpp fct.h
###

clean:
	$(RM) $(OBJETOS) $(EJECUTABLES) *~
#*- */

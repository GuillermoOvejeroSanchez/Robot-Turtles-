/*
GRUPO 1B DE FP
GUILLERMO OVEJERO SANCHEZ
MARLON JONATHAN CAMPOVERDE MENDEZ
*/

#include "checkML.h"
#include <iostream>
#include <ctime>
#include "Puntuaciones.h"
#include "Cartas.h"
#include "Dibujo.h"
#include "Juego.h"

bool menu(tJuego& juego, tPuntuaciones& puntuaciones, tInfoJugador**& alfabetico); //Ejecuta las diferentes opciones del juego

int main() {
	srand((unsigned int)time(NULL));
	tPuntuaciones puntuaciones;
	tInfoJugador** alfabetico;
	tJuego juego;
	bool salir = false;

	if (cargarPuntuaciones(puntuaciones)) {
		while (salir != true) {
			alfabetico = ordenAlfabetico(puntuaciones);
			salir = menu(juego, puntuaciones, alfabetico);
		}
	}
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}


bool menu(tJuego& juego, tPuntuaciones& puntuaciones, tInfoJugador**& alfabetico) {
	char opcion;
	bool salir = false;
	std::cout << "1).Jugar\n2).Mostrar puntuaciones\n3).Ver reglas e instrucciones\n\n0).Salir\n";
	std::cin >> opcion;
	std::cin.ignore(256, '\n');

	switch (opcion) {
	case '0': //Salir
		guardarPuntuaciones(puntuaciones); 
		liberar(puntuaciones, alfabetico);
		for (int i = 0; i < juego.jugadores; i++) //Puedo acceder a juego.jugadores?, o llamo desde otro lado
			liberar(juego.arrayJugadores[i].mazo);
		salir = true;
		break;
	case '1':  //Juego
		if (cargarJuego(juego)) {
			ejecutarJuego(juego, puntuaciones);
			ordenarPredeterminado(puntuaciones);
			alfabetico = ordenAlfabetico(puntuaciones);
		}
		else {
			std::cout << "No se ha podido cargar el tablero escogido" << std::endl;
			system("pause");
		}
		break;

	case '2': //Mostrar Puntuaciones
		std::cout << "1).Orden por defecto\n2).Orden Alfabetico\n";
		std::cin >> opcion;
		std::cin.ignore(256, '\n');
		std::cout << std::endl;

		switch (opcion) { //Submenu de puntuaciones
		case '1': mostrarPuntuaciones(puntuaciones); break;
		case '2': mostrarAlfabetico(alfabetico, puntuaciones); break;
		}
		break;

	case '3': reglas(); break; //Ver reglas
	}

	system("cls");

	return salir;
}
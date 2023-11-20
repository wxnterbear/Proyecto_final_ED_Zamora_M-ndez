#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

const int NUM_EQUIPOS = 48;
const int NUM_ESTADIOS = 20;

int simularPartido() {
    
    int golesEquipo1 = rand() % 5 + 1;  // Números aleatorios de 1 a 5
    int golesEquipo2 = rand() % 5 + 1;

    return max(golesEquipo1, golesEquipo2);
}

void obtenerNombresEstadios(string nombresEstadios[]) {
    ifstream archivo("estadios.txt");

    if (!archivo) {
        cerr << "Error al abrir el archivo de los estadios" << endl;
        exit(1);
    }

    for (int i = 0; i < NUM_ESTADIOS; ++i) {
        getline(archivo, nombresEstadios[i]);
    }

    archivo.close();
}

void mostrarResultados(string equipos[], int numEquipos, string nombresEstadios[]) {
    for (int i = 0; i < numEquipos; i += 2) {
        int golesEquipo1, golesEquipo2;

        do {
            golesEquipo1 = rand() % 5 + 1;
            golesEquipo2 = rand() % 5 + 1;
        } while (golesEquipo1 == golesEquipo2);

        int indiceEstadio = rand() % NUM_ESTADIOS;

        // Selecciona aleatoriamente los índices de los equipos que participan en el partido
        int indiceEquipo1 = rand() % numEquipos;
        int indiceEquipo2;
        
        do {
            indiceEquipo2 = rand() % numEquipos;
        } while (indiceEquipo2 == indiceEquipo1);

        cout << equipos[indiceEquipo1] << " " << golesEquipo1 << " - " << equipos[indiceEquipo2] << " " << golesEquipo2 << " en el Estadio: " << nombresEstadios[indiceEstadio] << endl;

        if (golesEquipo1 > golesEquipo2) {
            cout << "\nGanador: " << equipos[indiceEquipo1] << endl;
        } else {
            cout << "\nGanador: " << equipos[indiceEquipo2] << endl;
        }

        cout << endl;
    }
}

void mostrarMensajeBienvenida() {
    cout << "************************************************************************" << endl;
    cout << "*             Bienvenido a la Gran Simulacion Mundial 2023             *" << endl;
    cout << "*                 Dirigido por Nicolas Zamora Calderon                 *" << endl;
    cout << "*                         y Natali Mendez                              *" << endl;
    cout << "************************************************************************" << endl;
    cout << endl;
}

void mostrarIntroduccion() {
    cout << "Bienvenido a esta emocionante simulaciin del Mundial 2023!" << endl;
    cout << "En esta simulacion, experimentaras la emociin de los partidos de futbol," << endl;
    cout << "desde la fase de grupos hasta la gran final. Estas listo para empezar a jugar?" << endl;
    cout << endl;
}



int main() {
    mostrarMensajeBienvenida();
    mostrarIntroduccion();

    int opcion;

    do {
        // Opciones del usuario
        cout << "1. Mostrar Equipos" << endl;
        cout << "2. Empezar a Jugar" << endl;
        cout << "3. Salir" << endl;

        // Obtener la elección del usuario
        cout << "Ingrese el numero de la opcion deseada: ";
        cin >> opcion;
        cout << endl;

        // Procesar la elección del usuario
        switch (opcion) {
            case 1: {
                string equipos[NUM_EQUIPOS];
                ifstream archivoEquipos("NombreEquipos.txt");

                if (!archivoEquipos) {
                    cerr << "Error al abrir el archivo de equipos" << endl;
                    return 1;
                }
                
                cout << "-------- Grupos Del Mundial --------" << endl << endl;

                for (int i = 0; i < NUM_EQUIPOS; ++i) {
                    getline(archivoEquipos, equipos[i]);
                    cout << equipos[i] << endl;
                }

                archivoEquipos.close();
                
                random_shuffle(equipos, equipos + NUM_EQUIPOS);

                cout << endl << "Presiona Enter para volver al menu principal -->" << endl;
                cin.ignore();
                cin.get();

                break;
            }
            case 2: {
                string equipos[NUM_EQUIPOS];
                string nombresEstadios[NUM_ESTADIOS];

                ifstream archivoEquipos("NombreEquipos.txt");

                if (!archivoEquipos) {
                    cerr << "No se pudo abrir el archivo de equipos." << endl;
                    return 1;
                }

                for (int i = 0; i < NUM_EQUIPOS; ++i) {
                    getline(archivoEquipos, equipos[i]);
                }

                archivoEquipos.close();

                obtenerNombresEstadios(nombresEstadios);

                srand(static_cast<unsigned int>(rand()));

                int numEquipos = NUM_EQUIPOS;

                cout << "Fase de grupos:" << endl;
                while (numEquipos > 1) {
                    string equiposTemp[NUM_EQUIPOS];
                    copy(equipos, equipos + numEquipos, equiposTemp);

                    random_shuffle(equiposTemp, equiposTemp + numEquipos);

                    mostrarResultados(equiposTemp, numEquipos, nombresEstadios);

                    numEquipos /= 2;
                    cout << "Presiona Enter para avanzar a los " << (numEquipos == 24 ? "dieciseisavos" : (numEquipos == 12 ? "octavos" : (numEquipos == 6 ? "cuartos" : (numEquipos == 3 ? "semifinales" : "final")))) << "..." << endl;
                    cin.ignore();
                    cout << endl;
                }

                cout << "Final:" << endl;
                mostrarResultados(equipos, 2, nombresEstadios);
                cout << "El equipo ganador es: " << equipos[0] << "!" << endl;
                cout << "\n*********************************************************" << endl;

                break;
            }
            case 3:
                cout << "Gracias por jugar. Hasta la proxima!" << endl;
                break;
            default:
                cout << "Opcion no valida. Intentalo de nuevo." << endl;
                break;
        }
    } while (opcion != 3);

    return 0;
}

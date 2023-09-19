#include <iostream>
#include <string>
#include <cmath>
#include <random>


class NodoEventoTemporal {
public:
    NodoEventoTemporal(int datos, std::string cientifico, char tipoEvento) : datos_(datos), cientifico_(cientifico), tipoEvento_(tipoEvento), anterior_(nullptr), siguiente_(nullptr) {}

    int getDatos() const {
        return datos_;
    }

    std::string getCientifico() const {
        return cientifico_;
    }

    char getTipoEvento() const {
        return tipoEvento_;
    }

    NodoEventoTemporal* getAnterior() const {
        return anterior_;
    }

    NodoEventoTemporal* getSiguiente() const {
        return siguiente_;
    }

    void setAnterior(NodoEventoTemporal* anterior) {
        anterior_ = anterior;
    }

    void setSiguiente(NodoEventoTemporal* siguiente) {
        siguiente_ = siguiente;
    }

private:
    int datos_;
    std::string cientifico_;
    char tipoEvento_;
    NodoEventoTemporal* anterior_;
    NodoEventoTemporal* siguiente_;
};

class ListaDobleEventosTemporales {
public:

ListaDobleEventosTemporales(int numEventos) : cabeza_(nullptr), cola_(nullptr) {
    int contadorPrimosA = 0; // Contador de números primos para tipo A
    int contadorPrimosB = 0; // Contador de números primos para tipo B
    int contadorEventosA = 0; // Contador de eventos tipo A
    int contadorEventosB = 0; // Contador de eventos tipo B

    for (int i = 0; i < numEventos; ++i) {
        int datosAleatorios = generarNumeroAleatorio(1, 100);
        std::string cientificoAleatorio = generarCientificoAleatorio();
       char tipoEvento = 'n'; // Inicialmente, no hay tipo de evento
std::string cientifico = ""; // Inicialmente, el científico no está definido

if (esPrimo(datosAleatorios)) {
    if (contadorPrimosA == 0) {
        tipoEvento = 'A';
        contadorPrimosA++;
        cientifico = "Einstein"; // Científico 1 (Einstein) para eventos de tipo A
    } else if (contadorPrimosB == 0) {
        tipoEvento = 'B';
        contadorPrimosB++;
        // Científico 2 (Einstein o Rosen) para eventos de tipo B
        cientifico = (generarNumeroAleatorio(0, 1) == 0) ? "Einstein" : "Rosen";
    } else if (contadorEventosA > 0 && contadorEventosB > 0) {
        tipoEvento = 'C';
    }
}

        if (tipoEvento == 'A') {
            contadorEventosA++;
        } else if (tipoEvento == 'B') {
            contadorEventosB++;
        }

        agregarEvento(datosAleatorios, cientificoAleatorio, tipoEvento);
    }
}


    ~ListaDobleEventosTemporales() {
        while (cabeza_ != nullptr) {
            NodoEventoTemporal* temp = cabeza_;
            cabeza_ = cabeza_->getSiguiente();
            delete temp;
        }
    }
void calcularTotalEventos() const {
    int contadorEventosA = 0;
    int contadorEventosB = 0;
    int contadorEventosC = 0;

    NodoEventoTemporal* actual = cabeza_;

    while (actual != nullptr) {
        if (actual->getTipoEvento() == 'A') {
            contadorEventosA++;
        } else if (actual->getTipoEvento() == 'B') {
            contadorEventosB++;
        } else if (actual->getTipoEvento() == 'C') {
            contadorEventosC++;
        }

        actual = actual->getSiguiente();
    }

    int totalEventos = contadorEventosA + contadorEventosB + contadorEventosC;

    std::cout << "Total de eventos tipo A: " << contadorEventosA << std::endl;
    std::cout << "Total de eventos tipo B: " << contadorEventosB << std::endl;
    std::cout << "Total de eventos tipo C: " << contadorEventosC << std::endl;
    std::cout << "Total de eventos en la lista: " << totalEventos << std::endl;
}


    void imprimirEventos() const {
        NodoEventoTemporal* actual = cabeza_;
        int contadorNodos = 1;

        while (actual != nullptr) {
            std::cout << "Nodo " << contadorNodos << ": ";
            std::cout << "|";
            std::cout << actual->getDatos() << "|" << actual->getCientifico() << "|" << actual->getTipoEvento() << "|";
            std::cout << std::endl;
            actual = actual->getSiguiente();
            contadorNodos++;
        }
    }


int calcularMCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

  void verificarViaje() {
    NodoEventoTemporal* actualC = cabeza_;
    NodoEventoTemporal* actualA = nullptr; // Inicialmente no tenemos eventos A
    NodoEventoTemporal* actualB = nullptr; // Evento de tipo B
    int contadorEventosA = 0;
    int contadorEventosB = 0;

    // Buscar el primer evento de tipo B
    while (actualB == nullptr && actualC != nullptr) {
        if (actualC->getTipoEvento() == 'B') {
            actualB = actualC;
        }
        actualC = actualC->getSiguiente();
    }

    actualC = cabeza_; // Reiniciar para el bucle principal

    while (actualC != nullptr) {
        if (actualC->getTipoEvento() == 'A') {
            actualA = actualC; // Guarda el evento A más reciente
            contadorEventosA++;
        } else if (actualC->getTipoEvento() == 'B') {
            contadorEventosB++;
        }

        if (actualC->getTipoEvento() == 'C' && contadorEventosA > 0) {
            int mcd = calcularMCD(actualC->getDatos(), actualA->getDatos());

            if (mcd == 1) {
                std::cout << "Se viajó solo a observar: " << actualA->getDatos() << " -> " << actualC->getDatos() << std::endl;
            } else if (esPrimo(actualC->getDatos())) {
                std::cout << "Se viajó y se entregó información: " << actualA->getDatos() << " -> " << actualC->getDatos() << std::endl;

                if (actualA->getCientifico() == "Rosen" && actualC->getCientifico() == "Rosen") {
                    std::cout << "El científico Rosen no puede entregarse información a sí mismo" << std::endl;
                } else if (actualA->getCientifico() == "Einstein" || actualC->getCientifico() == "Rosen") {
                    std::cout << "El científico " << actualC->getCientifico() << " le entregó información al científico " << actualA->getCientifico() << std::endl;
                } else {
                    std::cout << "No se permite el intercambio de información entre científicos" << std::endl;
                }
            } else {
                std::cout << "Se viajó, pero no se entregó información: " << actualA->getDatos() << " -> " << actualC->getDatos() << std::endl;
            }
        }

        actualC = actualC->getSiguiente();
    }
}




    NodoEventoTemporal* cabeza_;
    NodoEventoTemporal* cola_;

    int generarNumeroAleatorio(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }

    std::string generarCientificoAleatorio() {
        std::vector<std::string> cientificos = {"Einstein", "Rossen"};
        int indiceAleatorio = generarNumeroAleatorio(0, cientificos.size() - 1);
        return cientificos[indiceAleatorio];
    }

    bool esPrimo(int num) {
        if (num <= 1) {
            return false;
        }
        for (int i = 2; i <= sqrt(num); ++i) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    void agregarEvento(int datos, std::string cientifico, char tipoEvento) {
        NodoEventoTemporal* nuevoEvento = new NodoEventoTemporal(datos, cientifico, tipoEvento);
        if (cabeza_ == nullptr) {
            cabeza_ = nuevoEvento;
            cola_ = nuevoEvento;
        } else {
            cola_->setSiguiente(nuevoEvento);
            nuevoEvento->setAnterior(cola_);
            cola_ = nuevoEvento;
        }
    }






};







int main() {
    ListaDobleEventosTemporales lista(22);
    lista.imprimirEventos();
    lista.verificarViaje();
    lista.calcularTotalEventos();
    return 0;
}


  
#include "iostream"
using namespace std;

struct nodo {
    int valor; // NIUP del paciente
    int edad;  // Edad del paciente
   
    nodo* izq;
    nodo* der;
};

nodo* raiz = NULL;
nodo* aux = NULL;
nodo* aux2 = NULL;
nodo* padre = NULL;


int posicionar() {
    if (aux->edad > aux2->edad) {
        if (aux2->izq == NULL) {
            aux2->izq = aux;
            return 0;
        }
        else {
            aux2 = aux2->izq;
            posicionar();
        }
    }
    else {
        if (aux2->der == NULL) {
            aux2->der = aux;
            return 0;
        }
        else {
            aux2 = aux2->der;
            posicionar();
        }
    }
}

int registrar() {
    aux = (nodo*)malloc(sizeof(nodo));
    cout << "Ingrese el NIUP del paciente: ";
    cin >> aux->valor;
    cout << "Ingrese la edad del paciente: ";
    cin >> aux->edad;
    aux->izq = aux->der = NULL;

    if (raiz == NULL) {
        raiz = aux;
        aux = NULL;
        free(aux);
    }
    else {
        aux2 = raiz;
        posicionar();
        aux = NULL;
        free(aux);
    }
    return 0;
}

int recorrer(nodo* a) {
    if (a != NULL) {
        cout << "NIUP: " << a->valor << ", Edad: " << a->edad << endl;
        recorrer(a->izq);
        recorrer(a->der);
    }
    return 0;
}

void mostrarOrden(struct Nodo* raiz) {
    if (raiz != NULL) {
        mostrarOrden(raiz->izquierda);
        cout << "Edad: " << raiz->edad << ", NIUP: " << raiz->niup << endl;
        mostrarOrden(raiz->derecha);
    }
}

struct Nodo* buscar(struct Nodo* raiz, int niup) {
    if (raiz == NULL || raiz->niup == niup) {
        return raiz;
    }
    if (niup < raiz->niup) {
        return buscar(raiz->izquierda, niup);
    }
    return buscar(raiz->derecha, niup);
}

int ubicar(nodo* a, int aguja) {
    if (a->valor == aguja) {
        aux2 = a;
        return 0;
    }
    else {
        if (a->izq != NULL) {
            ubicar(a->izq, aguja);
        }
        if (a->der != NULL) {
            ubicar(a->der, aguja);
        }
    }
    return 0;
}

int buscar(int aguja) {
    aux = NULL;
    if (raiz != NULL) {
        aux = raiz;
        ubicar(aux, aguja);
    }
    if (aux2) {
        cout << "Paciente encontrado: NIUP: " << aux2->valor << ", Edad: " << aux2->edad << endl;
    }
    else {
        cout << "Paciente no encontrado." << endl;
    }
}

int pedirAguja() {
    aux2 = NULL;
    int dato;
    cout << "Ingrese el NIUP del paciente a eliminar: ";
    cin >> dato;
    buscar(dato);
    if (aux2) {
        cout << "Paciente encontrado para eliminar." << endl;
    }
    else {
        cout << "El paciente no se encontró." << endl;
    }
}

int ubicarPadre(nodo* a) {
    if ((a->izq == aux2) || (a->der == aux2)) {
        padre = a;
    }
    else {
        if (a->izq != NULL) {
            ubicarPadre(a->izq);
        }
        if (a->der != NULL) {
            ubicarPadre(a->der);
        }
    }
}

int eliminar() {
    pedirAguja();
    if (aux2) {

        if (aux2->izq == NULL && aux2->der == NULL) {
            if (aux2 == raiz) {
                raiz = NULL;
            }
            else {
                ubicarPadre(raiz);
                if (padre->izq == aux2) {
                    padre->izq = NULL;
                }
                else {
                    padre->der = NULL;
                }
            }
            free(aux2);
        }

        else if (aux2->izq == NULL || aux2->der == NULL) {
            nodo* hijo = (aux2->izq != NULL) ? aux2->izq : aux2->der;
            if (aux2 == raiz) {
                raiz = hijo;
            }
            else {
                ubicarPadre(raiz);
                if (padre->izq == aux2) {
                    padre->izq = hijo;
                }
                else {
                    padre->der = hijo;
                }
            }
            free(aux2);
        }

        else {
            nodo* reemplazo = aux2->der;
            while (reemplazo->izq != NULL) {
                reemplazo = reemplazo->izq;
            }
            aux2->valor = reemplazo->valor;
            aux2->edad = reemplazo->edad;
            pedirAguja();  // Buscar y eliminar el reemplazo
        }
    }
}

int main() {
    int opc;
    do {
        cout << "1. Registrar paciente" << endl;
        cout << "2. Mostrar pacientes" << endl;
        cout << "3. Buscar paciente" << endl;
        cout << "4. Eliminar paciente" << endl;
        cout << "5. Salir" << endl;
        cin >> opc;
        switch (opc) {
        case 1: registrar(); break;
        case 2: mostrar(); break;
        case 3: {
            int niup;
            cout << "Ingrese el NIUP del paciente a buscar: ";
            cin >> niup;
            buscar(niup);
            break;
        }
        case 4: eliminar(); break;
        }
    } while (opc != 5);
    return 0;
}
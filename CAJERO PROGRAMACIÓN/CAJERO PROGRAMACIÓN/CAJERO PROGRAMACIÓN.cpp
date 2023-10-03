#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Registro {
    int correlativo;
    string nombre;
    int saldo;
};

void depositar(Registro& cliente, ofstream& archivo) {
    int monto;
    cout << "Ingrese el monto a depositar: Q";
    cin >> monto;
    archivo << cliente.correlativo << ", Deposito, +" << monto << endl;
    cliente.saldo += monto;
    cout << "Deposito exitoso de Q" << monto << endl;
}

void retirar(Registro& cliente, ofstream& archivo) {
    int monto;
    cout << "Ingrese el monto a retirar: Q";
    cin >> monto;
    if (monto > cliente.saldo) {
        cout << "No se puede retirar esa cantidad, el saldo es insuficiente" << endl;
    }
    else {
        archivo << cliente.correlativo << ", Retiro, -" << monto << endl;
        cliente.saldo -= monto;
        cout << "Retiro exitoso de Q" << monto << endl;
    }
}

void transferir(Registro& cliente, Registro& destinatario, ofstream& archivo) {
    int monto;
    cout << "Ingrese el monto a transferir: Q";
    cin >> monto;
    if (monto > cliente.saldo) {
        cout << "No se puede transferir esa cantidad, el saldo es insuficiente" << endl;
    }
    else {
        archivo << cliente.correlativo << ", Transferencia a " << destinatario.nombre << ", -" << monto << endl;
        archivo << destinatario.correlativo << ", Transferencia de " << cliente.nombre << ", +" << monto << endl;
        cliente.saldo -= monto;
        destinatario.saldo += monto;
        cout << "Transferencia exitosa de Q" << monto << " a " << destinatario.nombre << endl;
    }
}

void buscar(Registro& cliente, ifstream& archivo) {
    int correlativo;
    cout << "Ingrese el correlativo del cliente a buscar: ";
    cin >> correlativo;
    archivo.clear();
    archivo.seekg(0);
    string linea;
    while (getline(archivo, linea)) {
        int pos = linea.find(",");
        if (pos != string::npos) {
            int c = stoi(linea.substr(0, pos));
            if (c == correlativo) {
                cout << linea << endl;
                return;
            }
        }
    }
    cout << "Cliente con correlativo " << correlativo << " no encontrado" << endl;
}

int main() {
    int opcion;
    Registro cliente1 = { 1, "Juan Perez", 1000 };
    Registro cliente2 = { 2, "Maria Garcia", 500 };
    ofstream archivo("registro2.txt", ios::app);
    ifstream archivoLectura("registro2.txt");

    cout << "Bienvenido al cajero automatico" << endl;
    cout << "Ingrese su correlativo: ";
    int correlativo;
    cin >> correlativo;

    Registro* clienteActual = nullptr;
    if (correlativo == cliente1.correlativo) {
        clienteActual = &cliente1;
    }
    else if (correlativo == cliente2.correlativo) {
        clienteActual = &cliente2;
    }
    else {
        cout << "Correlativo invalido, saliendo del cajero automatico";
    }
// INTEGRANTES:
//MATOS ULISES; 
//EVELYN NARVAEZ; 
//ARACELI LUNA; 
//SANTIAGO ERCOLES; 
//GUIDO SABATINI


#include <iostream>
#include <string>
#include <limits>
#include <windows.h> 

using namespace std;

// Estructura para almacenar un pedido
struct Pedido {
    int id;
    string nombre_cliente;
    int cantidad;
};

// Función para mostrar el menú
void mostrarMenu() {
    cout << "Menú:\n";
    cout << "I: Ingresar un pedido\n";
    cout << "M: Modificar un pedido\n";
    cout << "R: Generar reporte\n";
    cout << "S: Salir\n";
}

// Función para ingresar un pedido
void ingresarPedido(Pedido* &pedidos, int &contador_id, int &total_churros, int &tamano, int &capacidad) {
    if (total_churros >= 1000) {
        cout << "Capacidad máxima de producción alcanzada para el día.\n";
        return;
    }

    if (tamano >= capacidad) {
        // Aumentar la capacidad
        capacidad *= 2;
        Pedido* nuevos_pedidos = new Pedido[capacidad];
        for (int i = 0; i < tamano; ++i) {
            nuevos_pedidos[i] = pedidos[i];
        }
        delete[] pedidos;
        pedidos = nuevos_pedidos;
    }

    Pedido nuevo_pedido;
    nuevo_pedido.id = ++contador_id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

    cout << "Ingrese el nombre del cliente: ";
    getline(cin, nuevo_pedido.nombre_cliente);

    cout << "Ingrese la cantidad de churros: ";
    cin >> nuevo_pedido.cantidad;

    if (total_churros + nuevo_pedido.cantidad > 1000) {
        cout << "No se puede aceptar el pedido. Excede la capacidad máxima de 1000 churros por día.\n";
        return;
    }

    total_churros += nuevo_pedido.cantidad;
    pedidos[tamano++] = nuevo_pedido;
    cout << "Pedido ingresado exitosamente.\n";
}

// Función para modificar un pedido
void modificarPedido(Pedido* pedidos, int tamano, int &total_churros) {
    int id;
    cout << "Ingrese el ID del pedido a modificar: ";
    cin >> id;

    for (int i = 0; i < tamano; ++i) {
        if (pedidos[i].id == id) {
            total_churros -= pedidos[i].cantidad; // Restar la cantidad actual de churros

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

            cout << "Ingrese el nuevo nombre del cliente: ";
            getline(cin, pedidos[i].nombre_cliente);

            cout << "Ingrese la nueva cantidad de churros: ";
            cin >> pedidos[i].cantidad;

            if (total_churros + pedidos[i].cantidad > 1000) {
                cout << "No se puede aceptar el cambio. Excede la capacidad máxima de 1000 churros por día.\n";
                total_churros += pedidos[i].cantidad; // Restaurar la cantidad original
                return;
            }

            total_churros += pedidos[i].cantidad; // Agregar la nueva cantidad de churros
            cout << "Pedido modificado exitosamente.\n";
            return;
        }
    }
    cout << "Pedido no encontrado.\n";
}

// Función para generar el reporte
void generarReporte(const Pedido* pedidos, int tamano) {
    cout << "Reporte de pedidos:\n";
    for (int i = 0; i < tamano; ++i) {
        cout << "ID: " << pedidos[i].id << ", Cliente: " << pedidos[i].nombre_cliente << ", Cantidad: " << pedidos[i].cantidad << " churros\n";
    }
}

int main() {
    // Configurar la consola para usar UTF-8 en Windows, caracteres como Ñ, acentos y demas
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int capacidad = 10;
    Pedido* pedidos = new Pedido[capacidad];
    int contador_id = 0;
    int total_churros = 0;
    int tamano = 0;
    char opcion;

    do {
        mostrarMenu();
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 'I':
            case 'i':
                ingresarPedido(pedidos, contador_id, total_churros, tamano, capacidad);
                break;
            case 'M':
            case 'm':
                modificarPedido(pedidos, tamano, total_churros);
                break;
            case 'R':
            case 'r':
                generarReporte(pedidos, tamano);
                break;
            case 'S':
            case 's':
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }
        cout << endl;
    } while (opcion != 'S' && opcion != 's');

    delete[] pedidos;
    return 0;
}

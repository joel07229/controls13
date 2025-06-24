#include <stdio.h>
#include "funciones.h"

int main() {
    Repuesto repuestos[MAX];
    Cliente clientes[MAX];
    Venta ventas[MAX];
    
    int num_repuestos = 0;
    int num_clientes = 0;
    int num_ventas = 0;
    
    // Cargar datos existentes
    cargarRepuestos(repuestos, &num_repuestos);
    cargarClientes(clientes, &num_clientes);
    cargarVentas(ventas, &num_ventas);
    
    int opcion;
    do {
        opcion = menu();
        
        switch(opcion) {
            case 1:
                agregarRepuesto(repuestos, &num_repuestos);
                guardarRepuestos(repuestos, num_repuestos);
                break;
            case 2:
                listarRepuestos(repuestos, num_repuestos);
                break;
            case 3:
                registrarCliente(clientes, &num_clientes);
                guardarClientes(clientes, num_clientes);
                break;
            case 4:
                listarClientes(clientes, num_clientes);
                break;
            case 5:
                realizarVenta(ventas, &num_ventas, repuestos, num_repuestos, clientes, num_clientes);
                guardarVentas(ventas, num_ventas);
                guardarRepuestos(repuestos, num_repuestos);
                break;
            case 6:
                listarVentas(ventas, num_ventas);
                break;
            case 7:
                verAlertasStock(repuestos, num_repuestos);
                break;
            case 8:
                restablecerStock(repuestos, num_repuestos);
                break;
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion no valida!\n");
        }
    } while(opcion != 0);
    
    return 0;
}
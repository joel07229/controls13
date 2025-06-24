#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu() {
    int opc;
    printf("\n--- SISTEMA DE GESTION DE REPUESTOS ---\n");
    printf("1. Agregar repuesto\n");
    printf("2. Listar repuestos\n");
    printf("3. Registrar cliente\n");
    printf("4. Listar clientes\n");
    printf("5. Realizar venta\n");
    printf("6. Listar ventas\n");
    printf("7. Ver alertas de stock bajo\n");
    printf("8. Restablecer stock\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opc);
    fflush(stdin);
    return opc;
}

void leerCadena(char *cadena, int longitud) {
    fgets(cadena, longitud, stdin);
    cadena[strcspn(cadena, "\n")] = '\0';
}

void agregarRepuesto(Repuesto repuestos[], int *num_repuestos) {
    if (*num_repuestos >= MAX) {
        printf("Inventario lleno!\n");
        return;
    }
    
    Repuesto *r = &repuestos[*num_repuestos];
    r->id = *num_repuestos + 1;
    
    printf("Nombre del repuesto: ");
    leerCadena(r->nombre, sizeof(r->nombre));
    
    printf("Precio: ");
    scanf("%f", &r->precio);
    
    printf("Stock inicial: ");
    scanf("%d", &r->stock);
    
    (*num_repuestos)++;
    printf("Repuesto agregado!\n");
}

void listarRepuestos(Repuesto repuestos[], int num_repuestos) {
    printf("\n--- INVENTARIO DE REPUESTOS ---\n");
    for (int i = 0; i < num_repuestos; i++) {
        printf("ID: %d | Nombre: %s | Precio: %.2f | Stock: %d\n", 
               repuestos[i].id, repuestos[i].nombre, 
               repuestos[i].precio, repuestos[i].stock);
    }
}

void verAlertasStock(Repuesto repuestos[], int num_repuestos) {
    int hayAlertas = 0;
    
    printf("\n--- ALERTAS DE STOCK BAJO ---\n");
    printf("(Repuestos con menos de %d unidades)\n", STOCK_MINIMO);
    printf("=====================================\n");
    
    for(int i = 0; i < num_repuestos; i++) {
        if(repuestos[i].stock < STOCK_MINIMO) {
            printf("[ALERTA] ID: %d | Nombre: %s | Stock actual: %d\n",
                  repuestos[i].id, repuestos[i].nombre, repuestos[i].stock);
            hayAlertas = 1;
        }
    }
    
    if(!hayAlertas) {
        printf("No hay repuestos con stock bajo. Todo en orden.\n");
    }
}

void guardarRepuestos(Repuesto repuestos[], int num_repuestos) {
    FILE *archivo = fopen("repuestos.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir archivo de repuestos\n");
        return;
    }
    fwrite(repuestos, sizeof(Repuesto), num_repuestos, archivo);
    fclose(archivo);
}

int cargarRepuestos(Repuesto repuestos[], int *num_repuestos) {
    FILE *archivo = fopen("repuestos.dat", "rb");
    if (archivo == NULL) {
        return 0;
    }
    *num_repuestos = fread(repuestos, sizeof(Repuesto), MAX, archivo);
    fclose(archivo);
    return 1;
}

void registrarCliente(Cliente clientes[], int *num_clientes) {
    if (*num_clientes >= MAX) {
        printf("Maximo de clientes alcanzado!\n");
        return;
    }
    
    Cliente *c = &clientes[*num_clientes];
    c->id = *num_clientes + 1;
    
    printf("Nombre del cliente: ");
    leerCadena(c->nombre, sizeof(c->nombre));
    
    printf("Telefono: ");
    leerCadena(c->telefono, sizeof(c->telefono));
    
    (*num_clientes)++;
    printf("Cliente registrado!\n");
}

void listarClientes(Cliente clientes[], int num_clientes) {
    printf("\n--- CLIENTES REGISTRADOS ---\n");
    for (int i = 0; i < num_clientes; i++) {
        printf("ID: %d | Nombre: %s | Telefono: %s\n", 
               clientes[i].id, clientes[i].nombre, clientes[i].telefono);
    }
}

void guardarClientes(Cliente clientes[], int num_clientes) {
    FILE *archivo = fopen("clientes.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir archivo de clientes\n");
        return;
    }
    fwrite(clientes, sizeof(Cliente), num_clientes, archivo);
    fclose(archivo);
}

int cargarClientes(Cliente clientes[], int *num_clientes) {
    FILE *archivo = fopen("clientes.dat", "rb");
    if (archivo == NULL) {
        return 0;
    }
    *num_clientes = fread(clientes, sizeof(Cliente), MAX, archivo);
    fclose(archivo);
    return 1;
}

void realizarVenta(Venta ventas[], int *num_ventas, Repuesto repuestos[], int num_repuestos, Cliente clientes[], int num_clientes) {
    if (*num_ventas >= MAX) {
        printf("Limite de ventas alcanzado!\n");
        return;
    }
    
    Venta *v = &ventas[*num_ventas];
    v->id = *num_ventas + 1;
    
    printf("ID del cliente: ");
    scanf("%d", &v->id_cliente);
    
    printf("ID del repuesto: ");
    scanf("%d", &v->id_repuesto);
    
    printf("Cantidad: ");
    scanf("%d", &v->cantidad);
    
    // Validar cliente
    int clienteValido = 0;
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id == v->id_cliente) {
            clienteValido = 1;
            break;
        }
    }
    
    if (!clienteValido) {
        printf("Cliente no encontrado!\n");
        return;
    }
    
    // Validar repuesto
    Repuesto *r = NULL;
    for (int i = 0; i < num_repuestos; i++) {
        if (repuestos[i].id == v->id_repuesto) {
            r = &repuestos[i];
            break;
        }
    }
    
    if (r == NULL) {
        printf("Repuesto no encontrado!\n");
        return;
    }
    
    if (r->stock < v->cantidad) {
        printf("Stock insuficiente!\n");
        return;
    }
    
    v->total = v->cantidad * r->precio;
    r->stock -= v->cantidad;
    
    (*num_ventas)++;
    printf("Venta realizada! Total: %.2f\n", v->total);
}

void listarVentas(Venta ventas[], int num_ventas) {
    printf("\n--- HISTORIAL DE VENTAS ---\n");
    for (int i = 0; i < num_ventas; i++) {
        printf("ID: %d | Cliente: %d | Repuesto: %d | Cant: %d | Total: %.2f\n", 
               ventas[i].id, ventas[i].id_cliente, 
               ventas[i].id_repuesto, ventas[i].cantidad, ventas[i].total);
    }
}

void guardarVentas(Venta ventas[], int num_ventas) {
    FILE *archivo = fopen("ventas.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir archivo de ventas\n");
        return;
    }
    fwrite(ventas, sizeof(Venta), num_ventas, archivo);
    fclose(archivo);
}

int cargarVentas(Venta ventas[], int *num_ventas) {
    FILE *archivo = fopen("ventas.dat", "rb");
    if (archivo == NULL) {
        return 0;
    }
    *num_ventas = fread(ventas, sizeof(Venta), MAX, archivo);
    fclose(archivo);
    return 1;
}
void restablecerStock(Repuesto repuestos[], int num_repuestos) {
    int id, nuevo_stock, encontrado;
    char opcion;
    do {
        printf("\n--- RESTABLECER STOCK DE REPUESTOS ---\n");
        listarRepuestos(repuestos, num_repuestos);
        printf("Ingrese el ID del repuesto a restablecer: ");
        scanf("%d", &id);
        encontrado = 0;
        for (int i = 0; i < num_repuestos; i++) {
            if (repuestos[i].id == id) {
                printf("Stock actual de '%s': %d\n", repuestos[i].nombre, repuestos[i].stock);
                printf("Nuevo stock: ");
                scanf("%d", &nuevo_stock);
                repuestos[i].stock = nuevo_stock;
                printf("Stock actualizado!\n");
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("ID no encontrado.\n");
        }
        printf("¿Desea restablecer otro repuesto? (s/n): ");
        fflush(stdin);
        scanf(" %c", &opcion);
    } while (opcion == 's' || opcion == 'S');
}
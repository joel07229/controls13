#define MAX 100
#define STOCK_MINIMO 5  // Umbral para alertas de stock bajo

typedef struct {
    int id;
    char nombre[50];
    float precio;
    int stock;
} Repuesto;

typedef struct {
    int id;
    char nombre[50];
    char telefono[15];
} Cliente;

typedef struct {
    int id;
    int id_cliente;
    int id_repuesto;
    int cantidad;
    float total;
} Venta;

// Prototipos de funciones
int menu();
void leerCadena(char *cadena, int longitud);

// Funciones de repuestos
void agregarRepuesto(Repuesto repuestos[], int *num_repuestos);
void listarRepuestos(Repuesto repuestos[], int num_repuestos);
void guardarRepuestos(Repuesto repuestos[], int num_repuestos);
int cargarRepuestos(Repuesto repuestos[], int *num_repuestos);
void verAlertasStock(Repuesto repuestos[], int num_repuestos);

// Funciones de clientes
void registrarCliente(Cliente clientes[], int *num_clientes);
void listarClientes(Cliente clientes[], int num_clientes);
void guardarClientes(Cliente clientes[], int num_clientes);
int cargarClientes(Cliente clientes[], int *num_clientes);

// Funciones de ventas
void realizarVenta(Venta ventas[], int *num_ventas, Repuesto repuestos[], int num_repuestos, Cliente clientes[], int num_clientes);
void listarVentas(Venta ventas[], int num_ventas);
void guardarVentas(Venta ventas[], int num_ventas);
int cargarVentas(Venta ventas[], int *num_ventas);
void restablecerStock(Repuesto repuestos[], int num_repuestos);
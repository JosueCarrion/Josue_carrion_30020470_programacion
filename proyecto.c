#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// numero de salida del menu
#define salida 5
//nuemro de departamentos
#define num_departamentos 6
//numero de cargos
#define num_cargos 6
//numeros de motivos de despido
#define num_eliminar 4

#define MAX 100

#ifdef _WIN32
#include <windows.h>
#endif
//funcion para limpiar la consola 
void limpiar_pantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// estructura trabajador
struct trabajador
{
    int cedula;
    char nombre[MAX];
    char apellido[MAX];
    char departamento[MAX];
    char cargo[MAX];
    float sueldo;
    char fecha_ingreso[MAX];
    int cod_departamento;
    int cod_cargo;
};
// Departamentos disponibles
char Departamentos[num_departamentos][20] = {"RRHH", "Consultoria", "Diseno", "Produccion", "Calidad", "Distribucion"};
// Cargos disponibles
char Cargos[num_cargos][20] = {"Gerente", "Supervisor", "Analista", "Disenador", "Desarrollador", "Auditor"};
// motivos de eliminacion disponibles
char Eliminaciones[num_eliminar][20] = {"Traslado", "Renuncia", "Despido", "Otro"};

//***************** FUNCIONES GLOBALES *******************
// imprime el munu por pantalla
void Menu(int t_trabajadores, struct trabajador trabajadores[]);
// Carga los trabajadores del archivo en un arreglo
int llenarTrabajadores(struct trabajador trabajadores[], char *nombre_archivo);

//***************** FUNCIONES OPTENER GLOBALES *******************
char get_departamento_por_caracter(int cod, int pos);
char get_cargo_por_caracter(int cod, int pos);
int get_codigo_arreglo(char palabra[20], char arreglo[6][20], int tamano);
void guardar_lista_en_archivo(char *nombre_archivo, struct trabajador trabajadores[], int t_trabajadores);

//***************** FUNCIONES MENU *******************
// ejecuta una opcion de menu
void Ejecuta_operacion(int op, struct trabajador trabajadores[], int t_trabajadores);
// pide una opcion de menu
int PedirOperacion();

//***************** MODULOS *******************

void Mod_Ingresar(struct trabajador trabajadores[], int t_trabajadores);
//***************** FUNCIONES MODULO INGRESAR *******************
// lista todos los trabajadores del arreglo
void listarTrabajadores(struct trabajador trabajadores[], int t_trabajadores);
// guarda un nuevo trabajador en un archivo
int Guardar_trabajador_en_archivo(struct trabajador trabajador, char *nombre_archivo);

void Mod_Consultar();
//***************** FUNCIONES MODULO CONSULTAR *******************
// ejecuta la consulta
void subMenu_consultar(int op, struct trabajador trabajadores[], int t_trabajadores);

void Mod_Modificar(struct trabajador trabajadores[], int t_trabajadores);
//***************** FUNCIONES MODULO CONSULTAR *******************
void modificar_trabajador(char *nombre_archivo, int lineaAEliminar, struct trabajador trabajador);

void Mod_Eliminar(struct trabajador trabajadores[], int t_trabajadores);
//************ ***** FUNCIONES MODULO ELIMINAR *******************
// elimina un trabajador
void eliminar_trabajador(char *nombre_archivo, int lineaAEliminar, char motivo[20], char fecha[20]);

//***************** FUNCIONES IMPRIMIR *******************
void imprimir_departamentos();
void imprimir_eliminaciones();
void imprimir_Cargos();
void imprimir_trabajador(struct trabajador trabajador);
void imprimir_error_archivo()
{
    printf("Error al abrir el fichero.\n");
    printf("Por favor verificar.\n");
}

int main()
{
    FILE *archivo_trabajadores;
    int total_trabajadores = 0;
    struct trabajador trabajadores[MAX];

    int op = 0;

    archivo_trabajadores = fopen("trabajadores.in", "r");
    if (archivo_trabajadores == NULL)
    {
        archivo_trabajadores = fopen("trabajadores.in", "w");
        if (archivo_trabajadores == NULL)
        {
            imprimir_error_archivo();
            exit(0);
        }
        fclose(archivo_trabajadores);
        main();
    }
    else
    {

        fclose(archivo_trabajadores);
        do
        {
            total_trabajadores = llenarTrabajadores(trabajadores, "trabajadores.in");
            // listarTrabajadores(trabajadores, total_trabajadores);
            Menu(total_trabajadores, trabajadores);

        } while (op != salida);
    }

    return 0;
}

void Menu(int t_trabajadores, struct trabajador trabajadores[])
{
    //  limpiar_pantalla();
    int eleccion = 0;
    printf("\n****************** MENU *******************\n");
    printf("*************** FUTURE, C.A ***************\n");
    printf("******* TOTAL DE TRABAJADORES: %i ********\n", t_trabajadores);
    printf("Seleccione la operacion que desea realizar:\n\n");
    printf("1) Ingresar nuevo trabajador.\n");
    printf("2) Consultar informacion de un trabajador.\n");
    printf("3) Modificar informacion de un trabajador.\n");
    printf("4) Eliminar informacion de un trabajador.\n");
    printf("%i) Salir.\n\n", salida);
    eleccion = PedirOperacion(t_trabajadores);
    Ejecuta_operacion(eleccion, trabajadores, t_trabajadores);
}

int PedirOperacion(int t_trabajadores)
{
    int op = 0;
    do
    {
        printf("Ingrese numero de operacion que desea realizar: ");
        scanf("%i", &op);
        if (op == 0 || op > salida)
        {
            printf("Numero invalido\n");
        }
        if (t_trabajadores == 0 && (op > 1 && op != salida))
        {
            printf("No hay trabajadores registrados.\n");
            printf("Registre al menos un trabajador para usar estas opciones.\n");
            op = 0;
        }
    } while (op == 0 || op > salida);
    return op;
}
void Ejecuta_operacion(int op, struct trabajador trabajadores[], int t_trabajadores)
{
    limpiar_pantalla();
    switch (op)
    {
    case 1:

        Mod_Ingresar(trabajadores, t_trabajadores);
        system("pause");

        break;
    case 2:

        Mod_Consultar(trabajadores, t_trabajadores);

        break;
    case 3:
        Mod_Modificar(trabajadores, t_trabajadores);
        system("pause");

        break;
    case 4:
        Mod_Eliminar(trabajadores, t_trabajadores);
        system("pause");

        break;
    case salida:
        exit(1);
        break;

    default:
        printf("Error.... Esto no deberia pasar, Saliendo... :')\n");

        break;
    }
}
//obtiene en que posicion de un arreglo esta una palabra nos sirve para obtener el cod de departamento/cargo... JC
int get_codigo_arreglo(char palabra[20], char arreglo[6][20], int tamano)
{
    for (int i = 0; i < tamano; i++)
    {
        //funcion que compara si dos string son iguales
        if (strcmp(palabra, arreglo[i]) == 0)
        {
            return i + 1;
        }
    }
    return -1;
}
//se encarga de llenar la informacion del archivo en un vector de trabajadores y devuelve cuantos trabajadores hay JC
int llenarTrabajadores(struct trabajador trabajadores[], char *nombre_archivo)
{

    FILE *archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL)
    {
        imprimir_error_archivo();
        exit(1);
        return 0;
    }
    int i = 0;

    while (!feof(archivo))
    {
        //lee la imformacion del archivo
        if (fscanf(archivo, "%i %s %s %s %s %f %s", &trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cargo, &trabajadores[i].sueldo, trabajadores[i].fecha_ingreso) == 7)
        {
            //esto nos ayuda a guardar el codigo del cargo y departamento para hacer busquedas mas faciles y rapidas JC
            trabajadores[i].cod_cargo = get_codigo_arreglo(trabajadores[i].cargo, Cargos, 6);
            trabajadores[i].cod_departamento = get_codigo_arreglo(trabajadores[i].departamento, Departamentos, 6);
            ;
            i++;
        }
    }
    fclose(archivo);
    return i;
}

// muestra los trabajadores de una lista fue usada para debbug 
void listarTrabajadores(struct trabajador trabajadores[], int t_trabajadores)
{
    int i = 0;

    if (t_trabajadores == 0)
    {
        // printf("El archivo esta vacio\n");
    }
    else
    {
        printf("Total de trabajadores en el archivo: %i\n", t_trabajadores);
        printf("\nCedula\tNombre\tApellido\tDepartamento\tCargo\tSueldo\tFecha de ingreso\n");
        for (i = 0; i < t_trabajadores; i++)
        {
            printf("%i %s %s %s %i %s %i %.2f %s\n", trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cod_departamento, trabajadores[i].cargo, trabajadores[i].cod_cargo, trabajadores[i].sueldo, trabajadores[i].fecha_ingreso);
        }
    }
}
//guarda un trabajador en un archivo indicado
int Guardar_trabajador_en_archivo(struct trabajador trabajador, char *nombre_archivo)
{
    FILE *archivo = fopen(nombre_archivo, "a");
    if (archivo == NULL)
    {
        imprimir_error_archivo();
        return 0;
    }
    else
    {
        fprintf(archivo, "%i %s %s %s %s %.2f %s\n", trabajador.cedula, trabajador.nombre, trabajador.apellido, trabajador.departamento, trabajador.cargo, trabajador.sueldo, trabajador.fecha_ingreso);
    }
    fclose(archivo);
    return 1;
}
//busca en el arreglo un trabajador por cedula
int buscar_por_cedula(struct trabajador trabajadores[], int t_trabajadores, int cedula)
{
    for (int i = 0; i < t_trabajadores; i++)
    {
        if (trabajadores[i].cedula == cedula)
        {
            return i;
        }
    }
    return -1;
}
//guarda toda una lista de trabajadores en un archivo
void guardar_lista_en_archivo(char *nombre_archivo, struct trabajador trabajadores[], int t_trabajadores)
{
    remove(nombre_archivo);
    FILE *archivo = fopen(nombre_archivo, "a");
    if (archivo == NULL)
    {
        imprimir_error_archivo();
        system("pause");
        return;
    }
    int i = 0;
    for (i = 0; i < t_trabajadores; i++)
    {
        fprintf(archivo, "%i %s %s %s %s %.2f %s\n", trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cargo, trabajadores[i].sueldo, trabajadores[i].fecha_ingreso);
    }
    fclose(archivo);
}

void Mod_Ingresar(struct trabajador trabajadores[], int t_trabajadores)
{
    struct trabajador trabajador_temp;
    printf("****************** MODULO *******************\n");
    printf("***************** INGRESAR ******************\n");
    do
    {
        printf("\nIngrese la cedula del nuevo trabajador: ");
        scanf("%i", &trabajador_temp.cedula);
        if (trabajador_temp.cedula <= 0)
        {
            printf("Numero de Cedula invalido\n");
        }
    } while (trabajador_temp.cedula <= 0);

    int index = buscar_por_cedula(trabajadores, t_trabajadores, trabajador_temp.cedula);
    if (index == -1)
    {

        printf("Ingrese el Nombre del nuevo trabajador:");
        scanf("%s", trabajador_temp.nombre);
        printf("Ingrese el apellido del nuevo trabajador: ");
        scanf("%s", trabajador_temp.apellido);
        int aux = 0;

        do
        {
            imprimir_departamentos();
            printf("Ingrese el Departamento del nuevo trabajor:");
            scanf("%i", &aux);
            if (aux == 0 || aux > num_departamentos)
            {
                printf("Numero de Departamento invalido\n");
            }
            else
            {
                int i = 0;
                for (i = 0; i < 20; i++)
                {
                    trabajador_temp.departamento[i] = get_departamento_por_caracter(aux - 1, i);
                }
            }
        } while (aux == 0 || aux > num_departamentos);

        aux = 0;
        do
        {
            imprimir_Cargos();
            printf("Ingrese el Cargo del nuevo trabajor:");
            scanf("%i", &aux);
            if (aux == 0 || aux > num_cargos)
            {
                printf("Numero de Cargo invalido\n");
            }
            else
            {
                int i = 0;
                for (i = 0; i < 20; i++)
                {
                    trabajador_temp.cargo[i] = get_cargo_por_caracter(aux - 1, i);
                }
            }
        } while (aux == 0 || aux > num_cargos);
        printf("Ingrese la fecha de ingreso (dd/mm/aa):");
        scanf("%s", trabajador_temp.fecha_ingreso);

        do
        {
            printf("Ingrese el Sueldo del nuevo trabajor:");
            scanf("%f", &trabajador_temp.sueldo);
            if (trabajador_temp.sueldo <= 0)
            {
                printf("Sueldo invalido\n");
            }
        } while (trabajador_temp.sueldo <= 0);
        imprimir_trabajador(trabajador_temp);
        int guardado = Guardar_trabajador_en_archivo(trabajador_temp, "trabajadores.in");
        if (guardado > 0)
        {
            printf("Trabajador Guardado con exito.\n");
        }
        else
        {
            printf("Error al intentar guardar el Trabajador.\n");
        }
    }
    else
    {
        printf("La CI indicada ya esta asociada a un trabajador de la empresa.\n");
        return;
    }
}

//imprime todos los departamentos disponibles
void imprimir_departamentos()
{
    printf("Departamentos:\n");
    int i = 0;
    for (i = 0; i < num_departamentos; i++)
    {
        printf("\t%i) %s\n", i + 1, Departamentos[i]);
    }
}
//imprime todos los motivos de eliminacion disponibles
void imprimir_eliminaciones()
{
    printf("Motivo:\n");
    int i = 0;
    for (i = 0; i < num_eliminar; i++)
    {
        printf("\t%i) %s\n", i + 1, Eliminaciones[i]);
    }
}
//imprime todos los cargos disponibles
void imprimir_Cargos()
{
    printf("Cargos:\n");
    int i = 0;
    for (i = 0; i < num_cargos; i++)
    {
        printf("\t%i) %s\n", i + 1, Cargos[i]);
    }
}
//imprime la informacion de un trabajador
void imprimir_trabajador(struct trabajador trabajador)
{
    printf("******** INFORMACION DEL TRABAJDAOR *********\n");
    printf("Cedula: %i\n", trabajador.cedula);
    printf("Nombre y Apellido: %s %s\n", trabajador.nombre, trabajador.apellido);
    printf("Departamento: %s\n", trabajador.departamento);
    printf("Cargo: %s\n", trabajador.cargo);
    printf("Sueldo: %f\n", trabajador.sueldo);
    printf("Fecha de ingreso: %s\n", trabajador.fecha_ingreso);
}

// Estas funciones se utilizan para obtener caracter por caracter un cargo/departamento y poder llenar una variable strig con el nombre completo CJ
char get_departamento_por_caracter(int cod, int pos)
{
    return Departamentos[cod][pos];
}
char get_motivo_por_caracter(int cod, int pos)
{
    return Eliminaciones[cod][pos];
}
char get_cargo_por_caracter(int cod, int pos)
{
    return Cargos[cod][pos];
}
// ******************************************

void Mod_Consultar(struct trabajador trabajadores[], int t_trabajadores)
{
    int eleccion = 0;
    printf("****************** MODULO *******************\n");
    printf("**************** CONSULTAR ******************\n");

    printf("Seleccione la operacion que desea realizar:\n\n");
    printf("1) Consulta por Cedula.\n");
    printf("2) Consulta por Departamento.\n");
    printf("3) Consulta por Cargo.\n");
    printf("4) Consulta por Sueldo.\n");
    printf("%i) Salir.\n\n", salida);
    eleccion = PedirOperacion(t_trabajadores);
    subMenu_consultar(eleccion, trabajadores, t_trabajadores);
}

void subMenu_consultar(int op, struct trabajador trabajadores[], int t_trabajadores)
{
    limpiar_pantalla();
    int i, x = 0;
    int cedula = 0;
    int cont_trabajadores = 0;
    float sueldos = 0;
    int aux = 0;

    struct trabajador trabajadores_temp[MAX];
    switch (op)
    {
    case 1:

        printf("************* CONSULTA POR CEDULA ************\n");
        do
        {
            printf("\nIngrese la cedula a buscar: ");
            scanf("%i", &cedula);
            if (cedula <= 0)
            {
                printf("Numero de Cedula invalido\n");
            }
        } while (cedula <= 0);

        int index = buscar_por_cedula(trabajadores, t_trabajadores, cedula);
        if (index == -1)
        {
            printf("La CI indicada no está asociada a ningún trabajador de la empresa.\n");
        }
        else
        {
            imprimir_trabajador(trabajadores[index]);
        }
        system("pause");

        break;
    case 2:

        printf("********** CONSULTA POR DEPARTAMENTO *********\n");
        do
        {
            imprimir_departamentos();
            printf("Ingrese el Departamento:");
            scanf("%i", &aux);
            if (aux == 0 || aux > num_departamentos)
            {
                printf("Numero de Departamento invalido\n");
            }
        } while (aux == 0 || aux > num_departamentos);

        for (i = 0; i < t_trabajadores; i++)
        {
            if (trabajadores[i].cod_departamento == aux)
            {
// se guarda toda la informacion del trabajador para luego generar el archivo de salida
                trabajadores_temp[cont_trabajadores].cedula = trabajadores[i].cedula;

                for (x = 0; x < MAX; x++)
                {
                    trabajadores_temp[cont_trabajadores].nombre[x] = trabajadores[i].nombre[x];
                    trabajadores_temp[cont_trabajadores].apellido[x] = trabajadores[i].apellido[x];
                    trabajadores_temp[cont_trabajadores].departamento[x] = trabajadores[i].departamento[x];
                    trabajadores_temp[cont_trabajadores].cargo[x] = trabajadores[i].cargo[x];
                    trabajadores_temp[cont_trabajadores].fecha_ingreso[x] = trabajadores[i].fecha_ingreso[x];
                }
                trabajadores_temp[cont_trabajadores].sueldo = trabajadores[i].sueldo;
                trabajadores_temp[cont_trabajadores].cod_departamento = trabajadores[i].cod_departamento;
                trabajadores_temp[cont_trabajadores].cod_cargo = trabajadores[i].cod_cargo;
                cont_trabajadores++;
                sueldos = sueldos + trabajadores[i].sueldo;
            }
        }
        guardar_lista_en_archivo("departamento.txt", trabajadores_temp, cont_trabajadores);
        printf("El Numero de trabajadores del departamento es: %i\n", cont_trabajadores);
        printf("El total de sueldos devengados del departamento es: %f\n", sueldos);

        system("pause");

        break;
    case 3:

        printf("************* CONSULTA POR CARGO *************\n");
        do
        {
            imprimir_Cargos();
            printf("Ingrese el Cargo:");
            scanf("%i", &aux);
            if (aux == 0 || aux > num_cargos)
            {
                printf("Numero de Cargo invalido\n");
            }
        } while (aux == 0 || aux > num_cargos);

        for (i = 0; i < t_trabajadores; i++)
        {
            if (trabajadores[i].cod_cargo == aux)
            {
                // se guarda toda la informacion del trabajador para luego generar el archivo de salida
                trabajadores_temp[cont_trabajadores].cedula = trabajadores[i].cedula;

                for (x = 0; x < MAX; x++)
                {
                    trabajadores_temp[cont_trabajadores].nombre[x] = trabajadores[i].nombre[x];
                    trabajadores_temp[cont_trabajadores].apellido[x] = trabajadores[i].apellido[x];
                    trabajadores_temp[cont_trabajadores].departamento[x] = trabajadores[i].departamento[x];
                    trabajadores_temp[cont_trabajadores].cargo[x] = trabajadores[i].cargo[x];
                    trabajadores_temp[cont_trabajadores].fecha_ingreso[x] = trabajadores[i].fecha_ingreso[x];
                }
                trabajadores_temp[cont_trabajadores].sueldo = trabajadores[i].sueldo;
                trabajadores_temp[cont_trabajadores].cod_departamento = trabajadores[i].cod_departamento;
                trabajadores_temp[cont_trabajadores].cod_cargo = trabajadores[i].cod_cargo;
                cont_trabajadores++;
                sueldos = sueldos + trabajadores[i].sueldo;
                        }
        }
        guardar_lista_en_archivo("cargo.txt", trabajadores_temp, cont_trabajadores);
        printf("El Numero de trabajadores con el cargo es: %i\n", cont_trabajadores);
        printf("El total de sueldos devengados del cargo es: %f\n", sueldos);
        system("pause");

        break;
    case 4:

        printf("************* CONSULTA POR SUELDO ***********\n");
        float trabajador_max = 0;
        int int_max = 0;

        float trabajador_min = trabajadores[0].sueldo;
        int int_min = 0;
        struct trabajador trabajadore_temp2;
        for (i = 0; i < t_trabajadores; i++)
        {
            if (trabajadores[i].sueldo > trabajador_max)
            {
                trabajador_max = trabajadores[i].sueldo;
                int_max = i;
            }
            if (trabajadores[i].sueldo <= trabajador_min)
            {
                trabajador_min = trabajadores[i].sueldo;
                int_min = i;
            }
        }
        printf("El trabajador con mayor sueldo es: %s %s\n", trabajadores[int_max].nombre, trabajadores[int_max].apellido);
        printf("El trabajador con menor sueldo es: %s %s\n", trabajadores[int_min].nombre, trabajadores[int_min].apellido);
        system("pause");

        break;
    case salida:
        return;
        break;

    default:
        printf("Error.... Esto no deberia pasar, Saliendo... :')\n");
        break;
    }
}

void Mod_Modificar(struct trabajador trabajadores[], int t_trabajadores)
{
    int i = 0;
    int cedula = 0;
    printf("****************** MODULO *******************\n");
    printf("***************** MODIFICAR *****************\n");
    do
    {
        printf("\nIngrese la cedula del trabajador a modificar: ");
        scanf("%i", &cedula);
        if (cedula <= 0)
        {
            printf("Numero de Cedula invalido\n");
        }
    } while (cedula <= 0);

    int index = buscar_por_cedula(trabajadores, t_trabajadores, cedula);
    if (index == -1)
    {
        printf("La CI indicada no está asociada a ningún trabajador de la empresa.\n");
        return;
    }
    else
    {
        struct trabajador trabajador_temp;
        trabajador_temp.cedula = cedula;
        imprimir_trabajador(trabajadores[index]);
        printf("\n***************** Modificacion ******************");
        printf("\nIngrese la nueva informacion del trabajador. \n");
        printf("Ingrese el nuevo Nombre del trabajador:");
        scanf("%s", trabajador_temp.nombre);
        printf("Ingrese el apellido del trabajador: ");
        scanf("%s", trabajador_temp.apellido);
        int aux = 0;

        do
        {
            imprimir_departamentos();
            printf("Ingrese el nuevo Departamento del trabajor:");
            scanf("%i", &aux);
            if (aux == 0 || aux > num_departamentos)
            {
                printf("Numero de Departamento invalido\n");
            }
            else
            {
                int i = 0;
                for (i = 0; i < 20; i++)
                {
                    trabajador_temp.departamento[i] = get_departamento_por_caracter(aux - 1, i);
                }
            }
        } while (aux == 0 || aux > num_departamentos);

        aux = 0;
        do
        {
            imprimir_Cargos();
            printf("Ingrese el nuevo Cargo del trabajor:");
            scanf("%i", &aux);
            if (aux == 0 || aux > num_cargos)
            {
                printf("Numero de Cargo invalido\n");
            }
            else
            {
                int i = 0;
                for (i = 0; i < 20; i++)
                {
                    trabajador_temp.cargo[i] = get_cargo_por_caracter(aux - 1, i);
                }
            }
        } while (aux == 0 || aux > num_cargos);
        printf("Ingrese la nuevo fecha de ingreso (dd/mm/aa):");
        scanf("%s", trabajador_temp.fecha_ingreso);

        do
        {
            printf("Ingrese el nuevo Sueldo del trabajor:");
            scanf("%f", &trabajador_temp.sueldo);
            if (trabajador_temp.sueldo <= 0)
            {
                printf("Sueldo invalido\n");
            }
        } while (trabajador_temp.sueldo <= 0);
        modificar_trabajador("trabajadores.in", index + 1, trabajador_temp);
    }
}

void Mod_Eliminar(struct trabajador trabajadores[], int t_trabajadores)
{
    int i = 0;
    int cedula = 0;
    printf("****************** MODULO *******************\n");
    printf("***************** ELIMINAR ******************\n");
    do
    {
        printf("\nIngrese la cedula del trabajador a eliminar: ");
        scanf("%i", &cedula);
        if (cedula <= 0)
        {
            printf("Numero de Cedula invalido\n");
        }
    } while (cedula <= 0);

    int index = buscar_por_cedula(trabajadores, t_trabajadores, cedula);
    if (index == -1)
    {
        printf("La CI indicada no está asociada a ningún trabajador de la empresa.\n");
        return;
    }
    else
    {
        int aux = 0;
        char motivo[20];
        char fecha[20];
        imprimir_trabajador(trabajadores[index]);
        do
        {
            imprimir_eliminaciones();
            printf("Ingrese el motivo de Eliminacion:");
            scanf("%i", &aux);
            if (aux == 0 || aux > num_eliminar)
            {
                printf("Motivo invalido\n");
            }
            else
            {
                int i = 0;
                for (i = 0; i < 20; i++)
                {
                    motivo[i] = get_motivo_por_caracter(aux - 1, i);
                }
            }
        } while (aux == 0 || aux > num_eliminar);
        printf("Ingrese la fecha de Eliminacion (dd/mm/aa):");
        scanf("%s", fecha);

        aux = 0;
        do
        {

            printf("Desea eliminar este trabajador? \n");
            printf("1) Si\n");
            printf("2) No\n");
            printf("Opcion: ");
            scanf("%i", &aux);
            if (aux == 0 || aux > 2)
            {
                printf("invalido 1 o 2\n");
            }
        } while (aux == 0 || aux > 2);

        if (aux == 1)
        {
            eliminar_trabajador("trabajadores.in", index + 1, motivo, fecha);
        }
        else
        {
            return;
        }
    }
}

void eliminar_trabajador(char *nombre_archivo, int lineaAEliminar, char motivo[20], char fecha[20])
{
    FILE *archivo_trabajadores, *archivo_temp;
    char linea_temp[1000];
    int count = 1;

    archivo_trabajadores = fopen(nombre_archivo, "r");
    if (archivo_trabajadores == NULL)
    {
        imprimir_error_archivo();
        return;
    }

    archivo_temp = fopen("temp.txt", "w");
    if (archivo_temp == NULL)
    {
        imprimir_error_archivo();
        fclose(archivo_trabajadores);
        return;
    }

    while (fgets(linea_temp, 1000, archivo_trabajadores))
    {
        if (count != lineaAEliminar)
        {
            fprintf(archivo_temp, "%s", linea_temp);
        }
        else
        {
            FILE *extrabajadores;
            extrabajadores = fopen("extrabajadores.txt", "a");
            if (extrabajadores == NULL)
            {
                imprimir_error_archivo();
                fclose(archivo_trabajadores);
                fclose(archivo_temp);
                return;
            }
            linea_temp[strcspn(linea_temp, "\n")] = ' ';
            fprintf(extrabajadores, "%s %s %s\n", linea_temp, motivo, fecha);
            fclose(extrabajadores);
        }
        count++;
    }
    fclose(archivo_trabajadores);
    fclose(archivo_temp);
    remove(nombre_archivo);
    rename("temp.txt", nombre_archivo);
    printf("Trabajador eliminado correctamente\n");
}

void modificar_trabajador(char *nombre_archivo, int lineaAEliminar, struct trabajador trabajador)
{
    FILE *archivo_trabajadores, *archivo_temp;
    char linea_temp[1000];
    int count = 1;

    archivo_trabajadores = fopen(nombre_archivo, "r");
    if (archivo_trabajadores == NULL)
    {
        imprimir_error_archivo();
        return;
    }

    archivo_temp = fopen("temp.txt", "w");
    if (archivo_temp == NULL)
    {
        imprimir_error_archivo();
        fclose(archivo_trabajadores);
        return;
    }

    while (fgets(linea_temp, 1000, archivo_trabajadores))
    {
        if (count != lineaAEliminar)
        {
            fprintf(archivo_temp, "%s", linea_temp);
        }
        else
        {
            fprintf(archivo_temp, "%i %s %s %s %s %.2f %s\n", trabajador.cedula, trabajador.nombre, trabajador.apellido, trabajador.departamento, trabajador.cargo, trabajador.sueldo, trabajador.fecha_ingreso);
        }
        count++;
    }

    fclose(archivo_trabajadores);
    fclose(archivo_temp);
    remove(nombre_archivo);
    rename("temp.txt", nombre_archivo);
    printf("Trabajador modificado correctamente\n");
    imprimir_trabajador(trabajador);
}

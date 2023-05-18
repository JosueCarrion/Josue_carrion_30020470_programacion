/* Escrinir un algoritmo que permita registrar las citas medicas de una clinica abc de n cantidad de paientes
permitiendo mostrar por pantalla:
1) cantidad de pacientes femeninos
2) cantidad de pacientes masculinos
3) cantidad de pacientes mayores de edad
4) cantidad de pacientes menores de edad
5) permita validar las fechas de nacimiento de cada paciente
6) los pacientes cuya cedula de identidad terminen en numero par y sean del sexo femennino tendran un descuento del 15%
sobre el costo de la consulta
7) los pacientes del sexo masculino que tengan una edad mayor a 60 años tendran un descuento del 30%
*/
#include <stdio.h>
#define mes_act 4
#define ano_act 2023
#define dia_act 10

struct fecha
{
    int dia;
    int mes;
    int ano;
};

struct paciente
{
    int cedula;
    char sexo;
    struct fecha fecha_nacimiento;
    int edad;
};
void introducir_paciente(struct paciente pacientes[100], int n);
int ult__dig_cedula_par(int cedula);
int mayorEdad(int edad);
void imprimir_resultados(struct paciente pacientes[100], int n);
int masculino(char sexo);

void main()
{

    int n = 0;
    struct paciente pacientes[100];
    do
    {
        printf("Escriba cuantos pacientes introducira: ");
        scanf("%i", &n);
        if (n < 1)
        {
            printf("Numero invalido\n");
        }

    } while (n < 1);
    introducir_paciente(pacientes, n);
    imprimir_resultados(pacientes, n);
}

void introducir_paciente(struct paciente pacientes[100], int n)
{
    int i = 0;
        struct paciente paciente_temp;
        int edad_temp = 0;
        int aux = 0;

    for (i = 0; i < n; i++)
    {

        printf("************** Paciente %i **************\n", i + 1);
        do
        {
            printf("Introduzca la cedula del paciente %i:", i + 1);
            scanf("%i", &paciente_temp.cedula);
            if (paciente_temp.cedula < 1)
            {
                printf("numero invalido\n");
            }
        } while (paciente_temp.cedula < 1);
        do
        {
            printf("Sexo del paciente %i:\n", i + 1);
            printf("1) Masculino\n");
            printf("2) Femenino\n");
            printf("Introduzca el sexo del paciente %i:", i + 1);
            scanf("%i", &aux);
            if (aux < 1 || aux > 2)
            {
                printf("numero invalido\n");
            }
        } while (aux < 1 || aux > 2);
        if (aux == 1)
        {
            paciente_temp.sexo = 'M';
        }
        else
        {
            paciente_temp.sexo = 'F';
        }

        printf("Introduzca la fecha de nacimiento del paciente %i:\n", i + 1);
        printf("Fecha actual: %i/%i/%i\n", dia_act, mes_act, ano_act);
        edad_temp = 0;
        do
        {
            printf("Introduzca el dia: ");
            scanf("%i", &paciente_temp.fecha_nacimiento.dia);
            if (paciente_temp.fecha_nacimiento.dia < 1 || paciente_temp.fecha_nacimiento.dia > 31)
            {
                printf("numero invalido\n");
            }
        } while (paciente_temp.fecha_nacimiento.dia < 1 || paciente_temp.fecha_nacimiento.dia > 31);

        do
        {
            printf("Introduzca el mes: ");
            scanf("%i", &paciente_temp.fecha_nacimiento.mes);
            if (paciente_temp.fecha_nacimiento.mes < 1 || paciente_temp.fecha_nacimiento.mes > 12)
            {
                printf("numero invalido\n");
            }
        } while (paciente_temp.fecha_nacimiento.mes < 1 || paciente_temp.fecha_nacimiento.mes > 12);

        do
        {
            printf("Introduzca el año: ");
            scanf("%i", &paciente_temp.fecha_nacimiento.ano);
            if (paciente_temp.fecha_nacimiento.ano < 1 || paciente_temp.fecha_nacimiento.ano > ano_act)
            {
                printf("numero invalido\n");
            }
        } while (paciente_temp.fecha_nacimiento.ano < 1 || paciente_temp.fecha_nacimiento.ano > ano_act);
        edad_temp = 2023 - paciente_temp.fecha_nacimiento.ano;
        if (paciente_temp.fecha_nacimiento.mes > mes_act)
        {

            edad_temp--;
        }
        else if (paciente_temp.fecha_nacimiento.mes == mes_act)
        {
            if (paciente_temp.fecha_nacimiento.dia < dia_act)
            {

                edad_temp--;
            }
        }

        printf("la edad del paciente es: %i\n", edad_temp);
        if (paciente_temp.sexo == 'M')
        {
            if (edad_temp > 60)
            {
                printf("El paciente tiene un descuento adicional del 30 porciento\n");
            }
        }
        else
        {
            if (ult__dig_cedula_par(paciente_temp.cedula) == 1)
            {
                printf("El paciente tiene un descuento adicional del 15 porciento\n");
            }
        }

        pacientes[i].cedula = paciente_temp.cedula;
        pacientes[i].sexo = paciente_temp.sexo;
        pacientes[i].edad = edad_temp;
        pacientes[i].fecha_nacimiento = paciente_temp.fecha_nacimiento;
        printf("************************************************\n");
    }
}

void imprimir_resultados(struct paciente pacientes[100], int n)
{
    int i = 0;

    int count_mas = 0;
    int count_fen = 0;
    int count_may = 0;
    int count_menor = 0;

    for (i = 0; i < n; i++)
    {
        if (masculino(pacientes[i].sexo) == 1)
        {
            count_mas++;
        }
        else
        {
            count_fen++;
        }

        if (mayorEdad(pacientes[i].edad) == 1)
        {
            count_may++;
        }
        else
        {
            count_menor++;
        }
    }

    printf("Cantidad de pacientes femeninos: %i\n", count_fen);
    printf("Cantidad de pacientes masculinos: %i\n", count_mas);
    printf("Cantidad de pacientes mayores de edad: %i\n", count_may);
    printf("Cantidad de pacientes menores de edad: %i\n", count_menor);
}

int masculino(char sexo)
{
    if (sexo == 'M')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int mayorEdad(int edad)
{
    if (edad >= 18)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int ult__dig_cedula_par(int cedula)
{

    int ult = cedula % 10;
    if ((ult % 2) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
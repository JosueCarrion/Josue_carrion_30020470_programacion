#include <stdio.h>

void menu();
void PedirNumeros();
void PedirOperacion();
float calculetor();
void imprimirRes(float result);
float factorial(float num);
float potencia(float num1,float num2);
int salida = 7;

float num1 = 0;
float num2 = 0;
int op = 0;


void main()
{
    do
    {
        menu();

    } while (op != salida);
}

void menu()
{

    printf("****************** MENU *******************\n");
    printf("*************** Abaco 2.500 ***************\n");
    printf("Seleccione la operacion que desea realizar:\n");
    printf("1) Suma\n");
    printf("2) Resta\n");
    printf("3) Multiplicacion\n");
    printf("4) Division\n");
    printf("5) Potencia\n");
    printf("6) Factorial\n");
    printf("%i) Salir\n", salida);
    PedirOperacion();
    if (op == salida)
        return;
    PedirNumeros();
    imprimirRes(calculetor());
}

void PedirNumeros()
{
    printf("Ingrese numero uno a operar: ");
    scanf("%f", &num1);
    if (op != 6)
    {

        if (op == 4)
        {
            do
            {
                printf("Ingrese numero dos a operar: ");
                scanf("%f", &num2);

            } while (num2 == 0);
        }
        else
        {
            printf("Ingrese numero dos a operar: ");
            scanf("%f", &num2);
        }
    }
}

void PedirOperacion()
{
    do
    {

        printf("Ingrese numero de operacion que desea realizar: ");
        scanf("%i", &op);
        if (op == 0 || op > salida)
        {
            printf("Numero invalido\n");
        }
    } while (op == 0 || op > salida);
}

float calculetor()
{
    float res = 0;
    switch (op)
    {
    case 1:
        res = num1 + num2;
        break;

    case 2:
        res = num1 - num2;
        break;
    case 3:
        res = num1 * num2;
        break;
    case 4:
        res = num1 / num2;
        break;
    case 5:
        res = potencia(num1, num2);
        break;
   

         case 6:
        res = factorial(num1);
        break;

    }
    return res;
}

void imprimirRes(float result)
{
    switch (op)
    {
    case 1:
        printf("El resultado de la suma de %f y %f es: %f", num1, num2, result);
        break;

    case 2:
        printf("El resultado de la resta de %f y %f es: %f", num1, num2, result);
        break;
    case 3:
        printf("El resultado de la multiplicacion de %f y %f es: %f", num1, num2, result);
        break;
    case 4:
        printf("El resultado de la division de %f y %f es: %f", num1, num2, result);
        break;
    case 5:
        printf("El resultado de %f elevado a la %f es: %f", num1, num2, result);
        break;
    case 6:
        printf("El factorial de %f  es: %f", num1, result);
        break;
    }
    printf("\n\n");
}

float factorial(float num){
    int i = 1;
float res = 1;
for (i = 1; i <= num; i++)
{
    res = res * i;
}
return res;

}

float potencia(float num1, float  num2){
       int i = 1;
float res = 1;

    for (i = 0; i < num2; i++)
{
    res = res * num1;
}
   
    return res;
}

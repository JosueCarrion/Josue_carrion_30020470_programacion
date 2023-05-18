/* Escrinir un algoritmo que pida por teclado n numeros enteros, cada uno de ellos debera ser introducidos.
Calcular:
1) cuantos son pares e impares
2) cuantos ceros se han introducido por teclado
3) cuantos son primos
*/

#include <stdio.h>
int num_impar(int num);
int num_primos(int num);
int num_ceros(int num);
void main()
{
    int n, i, aux = 0;
    int count_pares, count_impares, count_ceros, count_primos = 0;

    do
    {
        printf("Escriba cuantos numeros introducira: ");
        scanf("%i", &n);
        if (n < 1)
        {
            printf("Numero invalido\n");
        }

    } while (n < 1);
    count_pares = 0;
    count_impares = 0;
    count_ceros = 0;
    count_primos = 0;

    for (i = 0; i < n; i++)
    {
        printf("Escriba el numero %i: ", i + 1);
        scanf("%i", &aux);
        if (num_impar(aux) == 1)
        {
            count_impares++;
        }
        else
        {
            count_pares++;
        }
        count_primos += num_primos(aux);
        count_ceros += num_ceros(aux);
    }
    printf("Ingreso %i numeros impares.\n", count_impares);
    printf("Ingreso %i numeros pares.\n", count_pares);
    printf("Ingreso %i numeros primos.\n", count_primos);
    printf("Ingreso %i ceros.\n", count_ceros);
}

int num_impar(int num)
{
    if ((num % 2) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int num_primos(int num)
{
    if (num == 1 || num == 0)
    {
        return 0;
    }

    int i = 1;
    for (i = 2; i < num; i++)
    {
        if ((num % i) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int num_ceros(int num)
{
    int unidad = -1;
    int ceros = 0;

    do
    {
        unidad = num % 10;
        num = num / 10;
        if (unidad == 0)
            ceros++;
    } while (num != 0);
    return ceros;
}

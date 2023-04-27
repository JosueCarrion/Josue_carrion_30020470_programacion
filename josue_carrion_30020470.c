#include <stdio.h>

#ifdef _WIN32
  #include<windows.h>
#endif  

void limpiar_pantalla()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void ejercicio1();
void ejercicio2();
void ejercicio3();
void ejercicio4();
void ejercicio5();
void ejercicio6();
void ejercicio7();
void ejercicio8();
void linea();

void main()
{

    int ejercicio = -1;

    do
    {
        do
        {
            printf("Ingrese el numero del ejercicio entre 1 al 8. Ingrese 9 si quiere salir\n");
            scanf("%d", &ejercicio);

            if (ejercicio < 1 || ejercicio > 9)
            {
                printf("numero de ejercicio no existe. ingrese un numero de ejercicio valido\n");
            }
            
            

        } while (ejercicio < 1 || ejercicio > 9);
        limpiar_pantalla();

        //linea();

        switch (ejercicio)
        {
        case 1:

            ejercicio1();
            break;
        case 2:

            ejercicio2();
            break;
        case 3:
            ejercicio3();
            break;
        case 4:
            ejercicio4();
            break;
        case 5:
            ejercicio5();
            break;
        case 6:
            ejercicio6();
            break;
        case 7:
            ejercicio7();
            break;
        case 8:
            ejercicio8();
            break;
        case 9:
            printf("Saliendo.... Tenga lindo dia :)\n");
            break;
        default:
            printf("Error.... Esto no deberia pasar, Saliendo... :')\n");
            
            break;
        }
        linea();

    } while (ejercicio != 9 );
}

void linea()
{
    printf("_______________________________\n");
}

void ejercicio1()
{

    float nota1 = 0;
    float t_notas = 0;
    int n_notas = 3;

    printf("Ejercicio 1: Escribir en lenguaje C un programa que:\n1) Pida por teclado la nota de tres examenes (datos reales).\n2) Calcule la nota media de los tres examenes.\n3) Muestre por pantalla el resultado (dato real).\n\n");

    for (int i = 1; i < (n_notas + 1); i++)
    {

        do
        {
            printf("Ingrese nota %d: ", i);
            scanf("%f", &nota1);
            if (nota1 < 0 || nota1 > 20)
            {
                printf("nota invalida\n");
                printf("debe estar entre 0 y 20\n");
            }
            else
            {
                t_notas = t_notas + nota1;
            }
        } while (nota1 < 0 || nota1 > 20);
    }

    printf("El promedio es de: %0.2f\n", t_notas / n_notas);
    printf("Ejercicio 1 terminado\n");
}

void ejercicio2()
{
    float arista = 0;
    printf("Ejercicio 2: Escribir en lenguaje C un programa que:\n1) Pida por teclado la arista (dato real) de un cubo.\n2) Calcule el volumen del cubo.\n3) Muestre por pantalla el resultado (dato real).\n\n");

    do
    {
        printf("Ingrese la arista del cubo: ", arista);
        scanf("%f", &arista);
        if (arista < 1)
        {
            printf("numero invalido\n");
        }

    } while (arista < 1);

    printf("El area del cubo es de: %f\n", (arista * arista * arista));
    printf("Ejercicio 2 terminado\n");
}
void ejercicio3()
{
    const float p_azucar = 3;
    const float p_cafe = 0.72;
    float dinero = 0;
    float dinero_p_azu = 0;
    float dinero_p_cafe = 0;
    float k_azucar = 0;
    float k_cafe = 0;
    float resto = 0;
    printf("Ejercicio 3: Suponiendo que el kilo de azucar y de cafe estan a 3 y 0.72 euros respectivamente, escribir\nen lenguaje C un programa que:\n1) Pida por teclado una cantidad (dato real) en euros.\n2) Si la mitad de la cantidad introducida se destina a comprar azucar, una tercera parte a comprar\ncafe, y el resto no se gasta. Calcule cuantos kilos de azucar y cafe (datos reales) se pueden comprar\ncon dicha cantidad de dinero, asi como la cantidad (dato real) de dinero sobrante.\n3) Muestre por pantalla los resultados (datos reales).\n\n");

    do
    {
        printf("Ingrese la cantidad de dinero en euros: ");
        scanf("%f", &dinero);
        if (dinero < 0)
        {
            printf("Monto invalido\n");
        }
    } while (dinero < 0);

    dinero_p_azu = dinero / 2;
    dinero_p_cafe = dinero / 3;
    resto = dinero - dinero_p_cafe - dinero_p_azu;

    k_azucar = dinero_p_azu / p_azucar;
    k_cafe = dinero_p_cafe / p_cafe;

    printf("Dinero para azucar: %f\nDinero para cafe: %f\n", dinero_p_azu, dinero_p_cafe);
    printf("Puede comprar:\n %f KG de azucar y\n %f KG de cafe\n le quedan: %f euros.\n", k_azucar, k_cafe, resto);

    printf("Ejercicio 3 terminado\n");
}
void ejercicio4()
{
    int hh = 0;
    int mm = 0;
    int ss = 0;
    int ss_totales = 0;
    printf("Ejercicio 4: Escribir en lenguaje C un programa que:\n1) Pida por teclado una hora en horas, minutos y segundos (datos enteros).\n2) Calcule cuantos segundos han pasado desde las 0:0:0 horas.\n3) Muestre por pantalla el resultado (dato entero).\n\n");
    do
    {
        printf("Ingrese hora (formato 24 horas) [00 - 24]: ");
        scanf("%d", &hh);
        if (hh < 0 || hh > 24)
        {
            printf("numero invalido\n");
        }
    } while (hh < 0 || hh > 24);

    do
    {
        printf("Ingrese minutos [00 - 59]: ");
        scanf("%d", &mm);
        if (mm < 0 || mm > 59)
        {
            printf("numero invalido\n");
        }
    } while (mm < 0 || mm > 59);
    do
    {
        printf("Ingrese Segundos [00 - 59]: ");
        scanf("%d", &ss);
        if (ss < 0 || ss > 59)
        {
            printf("numero invalido\n");
        }
    } while (ss < 0 || ss > 59);

    ss_totales = ss + (hh * 3600) + (mm * 60);

    printf("Segundos Transcurridos desde la hora 00:00:00 hasta la hora %d:%d:%d = %d segundos\n", hh, mm, ss, ss_totales);
    printf("Ejercicio 4 terminado\n");
}
void ejercicio5()
{
    int v1 = 0;
    int v2 = 0;
    int aux = 0;
    printf("Ejercicio 5: Escribir en lenguaje C un programa que:\n1) Pida por teclado dos numeros (datos enteros) y sean almacenados en dos variables, llamadas v1\ny v2.\n2) Intercambie los valores de las variables.\n3) Muestre por pantalla los valores contendidos en las variables.\n\n");

    printf("ingrese numero 1: ");
    scanf("%d", &v1);
    printf("ingrese numero 2: ");
    scanf("%d", &v2);

    aux = v1;
    v1 = v2;
    v2 = aux;
    printf("El numero 1, ahora es: %d y\nEl numero 2,ahora es: %d\n", v1, v2);
    printf("Ejercicio 5 terminado\n");
}
void ejercicio6()
{
    float dolares = 0;
    const float tasa = 166.386;
    float res = 0;

    printf("Ejercicio 6: Escribir en lenguaje C un programa que:\n1) Pida por teclado una cantidad (dato entero) en dolares.\n2) Calcule su equivalente en euros.\n3) Muestre por pantalla el resultado (dato real).\nNota: 1 euro = 166,386 dolares.\n\n");
    do
    {

        printf("Ingrese cantidad de dolares: ");
        scanf("%f", &dolares);
        if (dolares < 0)
        {
            printf("Monto invalido");
        }
    } while (dolares < 0);

    res = dolares / tasa;
    printf("%0.3f dolares son %0.3f euros\ntasa: %0.3f\n", dolares, res, tasa);

    printf("Ejercicio 6 terminado\n");
}
void ejercicio7()
{
    int num = 0;
    printf("Ejercicio 7: Escribir en lenguaje C un programa que:\n1) Pida por teclado un numero (dato entero).\n2) Muestre por pantalla:\n\t \"ES PAR\", en el caso de que el numero sea divisible entre 2.\n\t \"ES IMPAR\", en el caso de que el numero no sea divisible entre 2.\n\n");
    printf("Ingrese un numero: ");
    scanf("%d", &num);

    if ((num % 2) == 0)
    {
        printf("ES PAR\n");
    }
    else
    {
        printf("ES IMPAR\n");
    }

    printf("Ejercicio 7 terminado\n");
}
void ejercicio8()
{
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num_M = 0;
    printf("Ejercicio 8: Escribir en lenguaje C un programa que:\n1) Pida por teclado tres numeros (datos enteros).\n2) Muestre el mayor de los tres numeros introducidos.\n\n");

    printf("Ingrese un numero 1: ");
    scanf("%d", &num1);
    printf("Ingrese un numero 2: ");
    scanf("%d", &num2);
    printf("Ingrese un numero 3: ");
    scanf("%d", &num3);

    num_M = num1;
    if (num2 > num1)
    {
        num_M = num2;
    }
    if (num3 > num2)
    {
        num_M = num3;
    }
    printf("El numero mayor es: %d\n", num_M);

    printf("Ejercicio 8 terminado\n");
}
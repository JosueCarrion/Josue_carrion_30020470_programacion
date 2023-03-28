#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif

void limpiar_pantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void linea()
{
    printf("_______________________________\n");
}

void ejercicio1();
void ejercicio2();
void ejercicio3();

void linea();

void main()
{
    int n_ejercicios = 3;
    int ejercicio = -1;

    do
    {
        do
        {
            printf("Ingrese el numero del ejercicio entre 1 al %i. Ingrese %i si quiere salir\n", n_ejercicios, n_ejercicios + 1);
            scanf("%i", &ejercicio);

            if (ejercicio < 1 || ejercicio > n_ejercicios + 1)
            {
                printf("numero de ejercicio no existe. ingrese un numero de ejercicio valido\n");
            }

        } while (ejercicio < 1 || ejercicio > n_ejercicios + 1);
        limpiar_pantalla();

        // linea();
        int caso_final = n_ejercicios + 1;

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
            printf("Saliendo.... Tenga lindo dia :)\n");
            break;
        default:
            printf("Error.... Esto no deberia pasar, Saliendo... :')\n");

            break;
        }
        printf("Ejercicio %i terminado\n", ejercicio);

        linea();

    } while (ejercicio != n_ejercicios + 1);
}

void ejercicio1()
{
    int num1 = 0;
    int num2 = 0;
    int index = 1;
    int res1 = 0;
    int res2 = 0;

    printf("Ingrese el numero 1: ");
    scanf("%i", &num1);
    printf("Ingrese el numero 2: ");
    scanf("%i", &num2);

    for (index = 1; index < num1; index++)
    {

        if ((num1 % index) == 0)
        {

            printf("%i + ", index);

            res1 = res1 + index;
        }
    }

    printf("= %i\n", res1);

    for (index = 1; index < num2; index++)
    {
        if ((num2 % index) == 0)
        {
            if (index != num2 - 1)
            {

                printf("%i + ", index);
            }
            res2 = res2 + index;
        }
    }

    printf("= %i\n", res2);

    if (res1 == num2 && res2 == num1)
    {
        printf("%i y %i son amigos\n", num1, num2);
    }
    else
    {
        printf("%i y %i no son amigos\n", num1, num2);
    }
}

void ejercicio2()
{
    int num = 0;
    int cont_3 = 0;
    int cont_5 = 0;
    int num_invert = 0;
    printf("Ingrese el numero: ");
    scanf("%i", &num);

    int num_res = num;

    do
    {
        int uni = num_res % 10;
        num_invert = (num_invert * 10) + uni;
        num_res = num_res / 10;

        if (uni == 3)
        {
            cont_3 = cont_3 + 1;
        }
        if (uni == 5)
        {
            cont_5 = cont_5 + 1;
        }
    } while (num_res != 0);
    if (num > 99)
    {

        printf("Numero invertido: %i\n", num_invert);
    }
    printf("Numeros de 3 ingresados: %i\n", cont_3);
    printf("Numeros de 5 ingresados: %i\n", cont_5);
}

void ejercicio3()
{
    float h_monto_total = 0;
    int h_cedula = 0;
    
   
    int cant_art = 0;
    int cedula = 0;
    int i = 1;
    int num_cli = 0;
    int des_total = 0;
    int cont_ganadores = 0;
    int cont_3 = 0;
     int cont_5 = 0;

    do
    {
        printf("Ingrese la cantidad de clientes: ");
        scanf("%i", &num_cli);
        if (num_cli < 1)
        {
            printf("EL numero debe ser mayor a 0\n");
        }
    } while (num_cli < 1);

    for (i = 1; i < num_cli + 1; i++)
    {
        printf("Ingrese la cedula del cliente %i: ", i);
        scanf("%i", &cedula);

        do
        {
            printf("Ingrese la cantidad de productos: ");
            scanf("%i", &cant_art);
            if (cant_art < 1)
            {
                printf("EL numero debe ser mayor a 0\n");
            }
        } while (cant_art < 1);
        int x = 1;
             float monto_total = 0;
             float cant_total = 0;
        for (x = 1; x < cant_art + 1; x++)
        {
            float monto_compra = 0;
        int cant_uni = 0;
        float precio_uni = 0;
         char etiqueta = 'M';
        
         do
        {
           printf("Ingrese el precio del articulo  %i: ", x);
            scanf("%f", &precio_uni);
            if (precio_uni < 0)
            {
                printf("EL numero debe ser mayor a 0\n");
            }
        } while (precio_uni < 0);

         do
        {
            printf("Ingrese la cantidad de unidades del articulo %i: ",x);
            scanf("%i", &cant_uni);
            if (cant_uni < 1)
            {
                printf("EL numero debe ser mayor a 0\n");
            }
        } while (cant_uni < 1);

        printf("Ingrese la etiqueta del producto %i: ", x);
            scanf(" %c", &etiqueta);
            linea();

            monto_compra = cant_uni * precio_uni;
            if(etiqueta == 'M' || etiqueta == 'A'){

            monto_total = monto_total + monto_compra; 
            cant_total = cant_total + cant_uni;
            }
        




        }

        if((monto_total >= 1000 && monto_total <= 5000) && cant_total > 3){
            des_total = des_total + 50;
            printf("Tiene descuento del 50 porciento\n");
            cont_ganadores = cont_ganadores + 1;
        }
        if ((cedula % 2) == 0)
        {
            des_total = des_total + 5;
           printf("Tiene descuento extra del 5 porciento\n");
           cont_5 = cont_5 + 1;
        }else{
            des_total = des_total + 3;
            printf("Tiene descuento extra del 3 porciento\n");
             cont_3 = cont_3 + 1;
        }
        if (monto_total > h_monto_total)
        {
            
            h_monto_total = monto_total;
            h_cedula = cedula;

        }
         printf("Tiene un descuento total del: %f porciento\n",des_total);
        
        
    }
float porcent = (num_cli * cont_ganadores)/ 100;
    printf("EL porcentaje de clientes que obtuvieron descuento del 50 porciento o mas: %0.2f\n", porcent);

     printf("El ganador de la Gif es el cliente con la cedula: %i\n",cedula);
      printf("Clientes que obtuvieron descuento extra de 5 porciento: %i\n",cont_5);
      printf("Clientes que obtuvieron descuento extra de 3 porciento: %i\n",cont_3);


    


}
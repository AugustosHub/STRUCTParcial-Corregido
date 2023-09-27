#include <stdio.h>
#include <stdlib.h>
#include<wchar.h>
#include<locale.h>
#include<time.h>
#include<unistd.h>
#include<string.h>

struct info{
    char nombre[20];
    char proveedor[20];
    float precio;
    int stock;
    int lugar;
}Productos[10];

struct infoVentas{
    int ID;
    int lugar;
    int cantidad;
    float total;
    char nombre[20];
}Ventas[20];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PUNTO 1 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Inicializador (struct Productos *info, struct Ventas *infoVentas){
    for(int i=0;i<10;i++){
        strcpy(Productos[i].nombre, "-");
        strcpy(Productos[i].proveedor, "-");
        Productos[i].precio = 0;
        Productos[i].stock = 0;
        Productos[i].lugar = 0;
    }

    for(int i=0;i<20;i++){
        Ventas[i].ID = 0;
        Ventas[i].total = 0;
        Ventas[i].cantidad = 0;
        strcpy(Ventas[i].nombre, "-");
        Ventas[i].lugar = 0;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PUNTO 2 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void calcularIVA(float *iva, float precio){

    *iva = ((precio*21)/100);
}

void calcularAumento(float *aumento, float precio){

    *aumento = ((precio*10)/100);
}

void AgregarProducto (struct Productos *info){
    int ocupado = 1;
    float precio,iva = 0,aumento = 0;

    for(int i=0; i<10; i++){
        if(Productos[i].lugar == 0){
            fflush(stdin);
            printf("Ingrese el nombre del producto: ");
            gets(Productos[i].nombre);
            fflush(stdin);
            printf("Ingrese el nombre del proveedor: ");
            gets(Productos[i].proveedor);
            printf("Ingrese la cantidad de productos: ");
            scanf("%d",&Productos[i].stock);

            while(Productos[i].stock<=0){
                puts("-------------------------------------");
                puts("Cantidad no valida, intente de nuevo...");
                puts("-------------------------------------");
                printf("Ingrese la cantidad de productos: ");
                scanf("%d",&Productos[i].stock);
            }

            printf("Ingrese el precio unitario: ");
            scanf("%f",&precio);

            while(precio<=0){
                puts("-------------------------------------");
                puts("Precio no valido, intente de nuevo...");
                puts("-------------------------------------");
                printf("Ingrese el precio unitario: ");
                scanf("%f",&precio);
            }

            if(precio>=150){
                calcularIVA(&iva,precio);
                Productos[i].precio = (precio + iva);

                printf("Precio total: %.1f\n",Productos[i].precio);
            }else if(precio<=100){
                calcularAumento(&aumento,precio);
                Productos[i].precio = (precio + aumento);

                printf("Precio total: %.1f\n",Productos[i].precio);
            }

            Productos[i].lugar = 1;

            puts("--------------------------------");
            puts("¡Producto agregado éxitosamente!");
            puts("--------------------------------");
            system("pause");
            break;
        }else{
            ocupado = ocupado + 1;
        }
    }

    if(ocupado > 10){
        puts("¡No hay lugares disponibles para más productos!");
        puts("-----------------------------------------------");
        system("pause");
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PUNTO 3 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void venderProductos(struct Productos *info, struct Ventas *infoVentas){
    int op,op2, cantidad,verificador = 1, j = 1;
    float total;
    static int numVenta = 1;
    puts("PRODUCTOS DISPONIBLES\n");

    for(int i=0; i<10; i++){
        if(Productos[i].lugar == 1){
            printf("%d. %s \n",i+1,Productos[i].nombre);
            j = j + 1;
        }
    }

    printf("%d. Salir\n", j);
    puts("----------------");
    printf("Opción: ");
    scanf("%d",&op);

    while(op>j || op<1){
        puts("------------------------------------");
        puts("Opción invalida, intente de nuevo...");
        puts("------------------------------------");
        printf("Opción: ");
        scanf("%d",&op);
    }

    for(int i=0; i<10; i++){
        if(op-1 == i){
            Stock(i, Productos);

            printf("\n");

            printf("¿Cuántos productos desea vender?\n");
            printf("Vender: ");
            scanf("%d",&cantidad);

            while(cantidad>Productos[i].stock || cantidad<=0){
                puts("--------------------------------------");
                puts("Cantidad invalida, intente de nuevo...");
                puts("--------------------------------------");
                printf("¿Cuántos productos desea vender?\n");
                printf("Vender: ");
                scanf("%d",&cantidad);
            }

            total = (cantidad * Productos[i].precio);

            printf("\nEl monto a pagar es: %.1f\n",total);
            puts("¿Desea realizar la venta?");
            puts("1. Si");
            puts("2. No");
            puts("--------------------------");
            printf("Opción: ");
            scanf("%d",&op2);
            while(op2>2 || op2<1){
                puts("------------------------------------");
                puts("Opción invalida, intente de nuevo...");
                puts("------------------------------------");
                printf("Opción: ");
                scanf("%d",&op2);
            }

            switch (op2){
                case 1:
                    for(int i=0;i<20;i++){
                        if(Ventas[i].lugar==0){
                            Ventas[i].total = total;

                            Ventas[i].cantidad = cantidad;

                            Productos[op-1].stock = Productos[op-1].stock - cantidad;

                            Ventas[i].ID = numVenta;

                            fflush(stdin);
                            strcpy(Ventas[i].nombre, Productos[op-1].nombre);

                            printf("El número de la venta es: %d\n",Ventas[i].ID);

                            Ventas[i].lugar = 1;
                            puts("----------------------------");
                            puts("¡Compra realizada con éxito!");
                            puts("----------------------------");
                            system("pause");
                            numVenta ++;
                            break;
                        }else{
                            verificador = verificador + 1;
                        }
                    }
                    if(verificador>20){
                        puts("----------------------------------------------------");
                        puts("¡No hay lugar para más ventas, intente eliminar una!");
                        puts("----------------------------------------------------");
                    }
                    break;
                case 2:
                    puts("----------------------------");
                    puts("¡Compra cancelada con éxito!");
                    puts("----------------------------");
                    system("pause");
                    break;
            }
        }
    }
}

void Stock(int i, struct Productos *info){
    puts("----------------------------------------------");
    printf("El stock del producto %s es: %d\n", Productos[i].nombre, Productos[i].stock);
    puts("----------------------------------------------");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PUNTO 4 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mostrarResultados(struct Productos *info, struct Ventas *infoVentas){
    int plegable;
    puts("TODOS LOS PRODUCTOS");
    for(int i=0;i<10;i++){
        if(Productos[i].lugar == 1){
            printf("%d. %s\n",i+1,Productos[i].nombre);
        }
    }
    puts("------------------------------------");
    puts("\nPRODUCTOS CON STOCK MAYOR/IGUAL 5\n");

    int verificador = 1, c = 1;

    for(int i=0; i<10; i++){
        if(Productos[i].stock>=5){
            printf("%d. %s (STOCK: %d) \n",c,Productos[i].nombre,Productos[i].stock);
            c = c + 1;
        }else{
            verificador = (verificador + 1);
        }
    }
    if(verificador>10){
        puts("¡No hay productos con stock mayor/igual a 5 unidades!\n");
    }
    puts("-------------------------------------");
    puts("\nPRODUCTOS CON PRECIO MAYOR A $150\n");

    int verificador2 = 1, j = 1;

    for(int i=0; i<10; i++){
        if(Productos[i].precio>=150){
            printf("%d. %s ($%.1f) \n",j,Productos[i].nombre,Productos[i].precio);
            j = j + 1;
        }else{
            verificador2 = (verificador2 + 1);
        }
    }
    if(verificador2>10){
        puts("¡No hay productos con precio mayor/igual a $150!\n");
    }
    puts("-------------------------------------------");
    puts("\nVENTAS LLEVADAS A CABO HASTA EL MOMENTO\n");

    int verificador3 = 1, k = 1;

    for(int i=0;i<20;i++){
        if(Ventas[i].lugar == 1){
            printf("%VENTA N° %d\n",k);
            printf("ID de la venta: %d\n",Ventas[i].ID);
            printf("Producto vendido: %s\n",Ventas[i].nombre);
            printf("Cantidad vendida: %d\n",Ventas[i].cantidad);
            printf("Total de la venta: %.1f\n",Ventas[i].total);
            puts("------------------------------------------");
            plegable = 1;
            k = k + 1;
        }else{
            verificador3 = verificador3 + 1;
        }
    }
    if(verificador3>20){
        puts("¡No se ha realizado ninguna venta!");
    }

    if(plegable!=1){
    puts("----------------------------------------");
    }
    puts("\nMONTO TOTAL DE LAS VENTAS REALIZADAS\n");

    int verificador4 = 1, l = 1;
    float montoTotal = 0;

    for(int i=0;i<20;i++){
        if(Ventas[i].total != 0){
            montoTotal = (montoTotal + Ventas[i].total);
            l = l + 1;
        }else{
            verificador4 = (verificador4 + 1);
        }
    }
    if(verificador3>20){
        puts("¡No se ha recaudado nada todavía!");
    }else{
        printf("EL TOTAL RECAUDADO DE LAS VENTAS ES: %.1f\n",montoTotal);
    }

    puts("---------------------------------");
    puts("\nSTOCK ACTUAL DE LOS PRODUCTOS\n");

    int v = 1;

    for(int i=0; i<10; i++){
        if(Productos[i].lugar == 1){
            printf("%d. %s (STOCK: %d) \n",v,Productos[i].nombre,Productos[i].stock);
        }
    }
    puts("--------------------------------------------------------------");
    system("pause");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PUNTO 5 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void eliminarVenta(struct Productos *info, struct Ventas *infoVentas){
    int op,op2,ID,stock,c = 1;
    char buscador[20];

    puts("VENTAS REALIZADAS\n");

    for(int i=0; i<20;i++){
        if(Ventas[i].lugar == 1){
            printf("%d. ID VENTA: %d\n",c,Ventas[i].ID);
            c = c + 1;
        }
    }
    printf("%d. Salir\n", c);
    puts("----------------------------");
    printf("Opción: ");
    scanf("%d",&op);
    while(op>c || op<1){
        puts("------------------------------------");
        puts("Opción invalida, intente de nuevo...");
        puts("------------------------------------");
        printf("Opción: ");
        scanf("%d",&op);
    }

    if(op == c){
        return 0;
    }else{
        puts("\n¿Está seguro de que quiere eliminar la venta?");
        puts("1. Si");
        puts("2. No");
        puts("----------------------------");
        printf("Opción: ");
        scanf("%d",&op2);
        while(op2>2 || op2<1){
            puts("------------------------------------");
            puts("Opción invalida, intente de nuevo...");
            puts("------------------------------------");
            printf("Opción: ");
            scanf("%d",&op2);
        }
        switch(op2){
            case 1:
                ID = op;
                for(int i=0; i<20;i++){
                    if(ID == Ventas[i].ID){
                        strcpy(buscador,Ventas[i].nombre);
                        stock = Ventas[i].cantidad;
                        for(int j=0;j<10;j++){
                            if(strcmp(buscador,Productos[j].nombre)==0){
                                Productos[j].stock = Productos[j].stock + stock;
                                break;
                            }
                        }

                        Ventas[i].ID = 0;
                        Ventas[i].total = 0;
                        Ventas[i].cantidad = 0;
                        strcpy(Ventas[i].nombre, "-");
                        Ventas[i].lugar = 0;

                        system("cls");
                        puts("----------------------------");
                        puts("¡Venta eliminada con éxito!");
                        puts("----------------------------");
                        system("pause");
                    }
                }
                break;
            case 2:
                return 0;
                break;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    int op,bandera;

    int inicio = 0, agregar = 0, vender = 0;

    bandera = 0;

    srand(time(NULL));
    setlocale(LC_ALL, "");

    struct Productos *info;
    struct Ventas *infoVentas;

    do{
        system("cls");
        puts("Primer parcial (Correción)");
        puts("\nMenú:");
        puts("1. Inicializar");
        puts("2. Agregar producto");
        puts("3. Realizar ventas");
        puts("4. Mostrar resultados");
        puts("5. Eliminar una venta");
        puts("6. Salir");
        puts("----------------------");
        printf("Opción: ");
        scanf("%d",&op);

        while(op>6 || op<1){
            puts("---------------------------------");
            puts("Opción invalida, intente de nuevo");
            puts("---------------------------------");
            printf("Opción: ");
            scanf("%d",&op);
        }

        switch(op){
            case 1:
                system("cls");
                puts("¡Si inicializa se borrarán todos los datos!");
                puts("¿Desea continuar?");
                puts("1. Si");
                puts("2. No");
                puts("-----------------");
                printf("Opción: ");
                scanf("%d",&op);
                while(op>2 || op<1){
                    puts("------------------------------------");
                    puts("Opción invalida, intente de nuevo...");
                    puts("------------------------------------");
                    printf("Opción: ");
                    scanf("%d",&op);
                }
                switch(op){
                    case 1:
                        system("cls");
                        puts("Inicializando el programa, espere...");
                        sleep(2);
                        Inicializador(Productos, Ventas);
                        system("cls");
                        puts("------------------------------");
                        puts("¡Sistema cargado éxitosamente!");
                        puts("------------------------------");
                        system("pause");
                        system("cls");
                        puts("Volviendo al menú...");
                        sleep(2);
                        inicio = 1;
                        break;
                    case 2:
                        system("cls");
                        puts("Volviendo al menú...");
                        sleep(2);
                        break;
                }
                break;
            case 2:
                if(inicio != 1){
                    system("cls");
                    puts("--------------------------------------");
                    puts("¡Debe inicializar primero el programa!");
                    puts("--------------------------------------");
                    system("pause");
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                    break;
                }else{
                    system("cls");
                    AgregarProducto(Productos);
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                    agregar = 1;
                    break;
                }
                break;
            case 3:
                if(inicio != 1){
                    system("cls");
                    puts("--------------------------------------");
                    puts("¡Debe inicializar primero el programa!");
                    puts("--------------------------------------");
                    system("pause");
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                    break;
                }else if (agregar!=1){
                    system("cls");
                    puts("----------------------------------");
                    puts("¡Debe agregar un producto primero!");
                    puts("----------------------------------");
                    system("pause");
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                }else{
                    system("cls");
                    venderProductos(Productos, Ventas);
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                    vender = 1;
                }
                break;
            case 4:
                if(inicio != 1){
                    system("cls");
                    puts("--------------------------------------");
                    puts("¡Debe inicializar primero el programa!");
                    puts("--------------------------------------");
                    system("pause");
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                    break;
                }else if (agregar!=1){
                    system("cls");
                    puts("----------------------------------");
                    puts("¡Debe agregar un producto primero!");
                    puts("----------------------------------");
                    system("pause");
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                }else if (vender !=1){
                    system("cls");
                    puts("---------------------------------");
                    puts("¡Debe realizar una venta primero!");
                    puts("---------------------------------");
                    system("pause");
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                }else{
                    system("cls");
                    mostrarResultados(Productos, Ventas);
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                }
                break;
            case 5:
                if(inicio != 1){
                    system("cls");
                    puts("--------------------------------------");
                    puts("¡Debe inicializar primero el programa!");
                    puts("--------------------------------------");
                    system("pause");
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                    break;
                }else if (agregar!=1){
                    system("cls");
                    puts("----------------------------------");
                    puts("¡Debe agregar un producto primero!");
                    puts("----------------------------------");
                    system("pause");
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                }else if (vender !=1){
                    system("cls");
                    puts("---------------------------------");
                    puts("¡Debe realizar una venta primero!");
                    puts("---------------------------------");
                    system("pause");
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                }else{
                    system("cls");
                    eliminarVenta(Productos, Ventas);
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                    vender = 1;
                }
                break;
            case 6:
                system("cls");
                puts("Saliendo del programa...");
                sleep(2);
                bandera = 1;
                break;
        }

    }while(bandera!=1);

    return 0;
}

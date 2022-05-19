#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct estructura
{
    int codigo;
    char nombre[10];
    struct estructura *hijoIzquierdo;
    struct estructura *hijoDerecho;
}nodo;

typedef nodo *pNodo;
typedef nodo *Arbol;

// Declaración de funciones
nodo* nuevo();
void insertar(Arbol*, int, char*);
void procesarIn(Arbol*);
void procesarPre(Arbol*);
void procesarPost(Arbol*);
pNodo perteneceArbol(Arbol*, int); // CAMBIADO
void encontrarArbol(Arbol*, int);
pNodo padreDeArbol(Arbol*, int, pNodo*);
void borrarArbol(Arbol*, int, pNodo*);
pNodo minimoHijoDerecho(Arbol*, int);

int main()
{

    Arbol miArbol = NULL;
    pNodo aux;

    // Creando el árbol
    insertar(&miArbol, 20, "Luis");
    insertar(&miArbol, 5, "Ana");
    insertar(&miArbol, 10, "Maya");
    insertar(&miArbol, 15, "Cara");
    insertar(&miArbol, 25, "Lara");
    insertar(&miArbol, 12, "Doce");
    insertar(&miArbol, 23, "Ventitres");


    /*
        INSERTAR: meter nodo a arbol
        BORRAR: meter nodo a arbol

        BUSCAR: PreInPost Orden

        BUSCAR: buscar nodo en arbol
        PADRE DE: codigo de padr

        SALIR
    */


    char nombre[10];
    int codigo = 0;

    int menu = 0;
    while(menu != 7){

        printf("\n");
        printf("0) Insertar elemento\n");
        printf("1) Borrar elemento\n");
        printf("2) Mostrar PreOden\n");
        printf("3) Mostrar InOrden\n");
        printf("4) Mostrar PostOrden\n");
        printf("5) Buscar Elemento\n");
        printf("6) Buscar Padre\n");
        printf("7) Salir\n");
        printf("Que quieres hacer: ");
        scanf("%i", &menu);
        fseek(stdin,0,SEEK_END);
        printf("\n");
        system("cls");

        switch(menu){
            case 0:
                // PEDIR DATOS
                printf("Dime codigo: ");
                scanf("%i", &codigo);
                printf("Dime nombre: ");
                scanf("%s", &nombre);
                fseek(stdin,0,SEEK_END);

                // AÑADIR a COLA
                insertar(&miArbol, codigo, nombre);

                // MOSTRAR RESULTADO
                procesarIn(&miArbol);

                break;
            case 1:
                printf("Dime codigo: ");
                scanf("%i", &codigo);
                borrarArbol(&miArbol, codigo, &miArbol);
                procesarIn(&miArbol);
                break;
            case 2:
                procesarPre(&miArbol);
                break;
            case 3:
                procesarIn(&miArbol);
                break;
            case 4:
                procesarPost(&miArbol);
                break;
            case 5:
                printf("Dime codigo: ");
                scanf("%i", &codigo);
                printf("\nBuscando %d en el %crbol...\n",codigo, 181);
                aux = perteneceArbol(&miArbol, codigo);
                if(aux==NULL)
                {
                    printf("El elemento buscando no se encuentra\n");
                }
                else
                {
                    printf("\nEl nombre del elemento es %s\n", aux->nombre);
                }

                break;
            case 6:
                printf("Dime codigo: ");
                scanf("%i", &codigo);
                aux = padreDeArbol(&miArbol, codigo, NULL);
                if((miArbol->codigo)==codigo)
                {
                    printf("\nEl %d es ra%cz del %crbol, no tiene padre\n", codigo,161, 160);
                }
                else
                {
                    aux = padreDeArbol(&miArbol, codigo, NULL);
                    if(aux==NULL)
                    {
                        printf("El elemento buscando no se encuentra\n");
                    }
                    else
                    {
                        printf("\nEl padre de %d es %d\n", codigo, aux->codigo);
                    }
                }
                break;
            case 7 :
                printf("Bye :)\n");
                break;
            default:
                printf("\nNo te he entendido.\n\n");

        }
    }

    return 0;
}

// Implementación de funciones
nodo* nuevo()
{
    nodo *p;
    p = (nodo*) malloc(sizeof(nodo));
    p->hijoIzquierdo = NULL;
    p->hijoDerecho = NULL;
    return(p);
}

void insertar(Arbol *arbol, int v, char* n)
{
    pNodo miNodo; // Variable auxiliar para manipular un nodo
    pNodo recorrer; // Variable auxiliar para recorrer el árbol
    recorrer = *arbol; // Hacemos que apunte al árbol, a su raiz

    // Crear un nodo nuevo
    miNodo = nuevo();
    miNodo->codigo = v;
    strcpy(miNodo->nombre, n);

    // Averiguar el lugar a colocar el nuevo nodo
    if(*arbol==NULL) // Árbol vacío
    {
        *arbol = miNodo; // Colocamos el nodo como raiz
    }
    else if((recorrer->codigo)>=(miNodo->codigo)) // Insertar por la izquierda
    {
        insertar(&(recorrer->hijoIzquierdo), miNodo->codigo, miNodo->nombre); // Llamada recursiva
    }
    else // Insertar por la derecha
    {
         insertar(&(recorrer->hijoDerecho), miNodo->codigo, miNodo->nombre); // Llamada recursiva
    }
}

void procesarPre(Arbol *arbol)
{
    pNodo miNodo; // Variable auxiliar para manipular un nodo

    // miNodo apunta al primer elemento del árbol, la raiz
    miNodo = *arbol;
    if(miNodo!=NULL)
    {
        // Procesamos raiz
        printf("C%cdigo: %d\t", 162, miNodo->codigo);
        printf("Nombre: %s\n", miNodo->nombre);
        // Procesamos subárbol izquierdo
        procesarIn(&(miNodo->hijoIzquierdo));
        // Procesamos subárbol derecho
        procesarIn(&(miNodo->hijoDerecho));
    }
}

void procesarIn(Arbol *arbol)
{
    pNodo miNodo; // Variable auxiliar para manipular un nodo

    // miNodo apunta al primer elemento del árbol, la raiz
    miNodo = *arbol;
    if(miNodo!=NULL)
    {
        // Procesamos subárbol izquierdo
        procesarIn(&(miNodo->hijoIzquierdo));
        // Procesamos raiz
        printf("C%cdigo: %d\t", 162, miNodo->codigo);
        printf("Nombre: %s\n", miNodo->nombre);
        // Procesamos subárbol derecho
        procesarIn(&(miNodo->hijoDerecho));
    }
}

void procesarPost(Arbol *arbol)
{
    pNodo miNodo; // Variable auxiliar para manipular un nodo

    // miNodo apunta al primer elemento del árbol, la raiz
    miNodo = *arbol;
    if(miNodo!=NULL)
    {
        // Procesamos subárbol izquierdo
        procesarIn(&(miNodo->hijoIzquierdo));
        // Procesamos subárbol derecho
        procesarIn(&(miNodo->hijoDerecho));
        // Procesamos raiz
        printf("C%cdigo: %d\t", 162, miNodo->codigo);
        printf("Nombre: %s\n", miNodo->nombre);
    }
}












pNodo perteneceArbol(Arbol *arbol, int buscado)
{
    pNodo codigoPadre = NULL;
    pNodo miNodo; // Variable auxiliar para manipular un nodo

    // miNodo apunta al primer elemento del árbol, la raiz
    miNodo = *arbol;
    if((miNodo->codigo)==(buscado))
    {
        codigoPadre = miNodo;
    }
    else if(((miNodo->codigo)<(buscado))&&(miNodo->hijoDerecho!=NULL))
    {
        printf("Buscando por la Derecha\n");
        codigoPadre = perteneceArbol(&(miNodo->hijoDerecho), buscado);
    }
    else if(((miNodo->codigo)>(buscado))&&(miNodo->hijoIzquierdo!=NULL))
    {
        printf("Buscando por la Izquierda\n");
        codigoPadre = perteneceArbol(&(miNodo->hijoIzquierdo), buscado);
    }
    return codigoPadre;
}
















void encontrarArbol(Arbol *arbol, int buscado)
{
    // Primero comprobamos si existe o no
    pNodo aux;
    aux = perteneceArbol(arbol, buscado);
    if(aux!=NULL)
    {
        pNodo miNodo; // Variable auxiliar para manipular un nodo

        // miNodo apunta al primer elemento del árbol, la raiz
        miNodo = *arbol;
        if((miNodo->codigo)==(buscado))
        {
            printf("C%cdigo: %d\t", 162, miNodo->codigo);
            printf("Nombre: %s\n", miNodo->nombre);
        }
        else if(((miNodo->codigo)<(buscado))&&(miNodo->hijoDerecho!=NULL))
        {
            printf("Buscando por la Derecha\n");
            encontrarArbol(&(miNodo->hijoDerecho), buscado);
        }
        else if(((miNodo->codigo)>(buscado))&&(miNodo->hijoIzquierdo!=NULL))
        {
            printf("Buscando por la Izquierda\n");
            encontrarArbol(&(miNodo->hijoIzquierdo), buscado);
        }
    }
    else
    {
         printf("El elemento buscando no se encuentra\n");
    }
}

pNodo padreDeArbol(Arbol *arbol, int buscado, pNodo *padre)
{
    // Hay dos posibilidades:
    // No se encuentra, devolveremos NULL
    // Se encuentra, devolvemos el valor del padre del nodo correspondiente
    pNodo codigoPadre = NULL;
     // Primero comprobamos si existe o no
     pNodo aux;
    aux = perteneceArbol(arbol, buscado);

    if(aux!=NULL)
    {
        pNodo miNodo; // Variable auxiliar para manipular un nodo

        // miNodo apunta al primer elemento del árbol, la raiz
        miNodo = *arbol;
        if(((miNodo->codigo)<(buscado))&&(miNodo->hijoDerecho!=NULL))
        {
            printf("Buscando por la Derecha\n");
            codigoPadre = padreDeArbol(&(miNodo->hijoDerecho), buscado, &miNodo);
        }
        else if(((miNodo->codigo)>(buscado))&&(miNodo->hijoIzquierdo!=NULL))
        {
            printf("Buscando por la Izquierda\n");
            codigoPadre = padreDeArbol(&(miNodo->hijoIzquierdo), buscado, &miNodo);
        }
        else
        {
            codigoPadre = *padre;
        }
    }
    return codigoPadre;
}

void borrarArbol(Arbol *arbol, int buscado, pNodo *padre)
{
     pNodo aux;
    aux = perteneceArbol(arbol, buscado);
    if(aux==NULL) // No se encuentra o está vacío
    {
        printf("El elemento a eliminar no se encuentra\n");
    }
    else
    {
        pNodo miNodo; // Variable auxiliar para manipular un nodo
        pNodo otroNodo;
        // miNodo apunta al primer elemento del árbol, la raiz
        miNodo = *arbol;
        otroNodo = *padre;
        int codigoPadre = otroNodo->codigo;
        if ((miNodo->codigo)==buscado)
        {
            // Hay cuatro casos:
            // Que no tenga hijos
            if(((miNodo->hijoIzquierdo)==NULL)&&((miNodo->hijoDerecho)==NULL))
            {
                if(codigoPadre<buscado)
                {
                    printf("Borramos hijo derecho\n");
                    (*padre)->hijoDerecho = NULL;
                }
                else if(codigoPadre<buscado)
                {
                    printf("Borramos hijo izquierdo\n");
                    (*padre)->hijoIzquierdo = NULL;
                }
                else // Estamos borrando la raiz del árbol
                {
                    printf("Borramos raiz\n");
                    // Si borramos la raiz, y en este caso no tiene hijos
                    // Estamos VACIANDO el árbol
                    *arbol = NULL;
                }
            }
            // Que tenga dos hijos
            else if(((miNodo->hijoIzquierdo)!=NULL)&&((miNodo->hijoDerecho)!=NULL))
            {
                if(codigoPadre>buscado)
                {
                    (*padre)->hijoDerecho = miNodo->hijoIzquierdo;
                }
                else if(codigoPadre<buscado)
                {
                    (*padre)->hijoIzquierdo = miNodo->hijoDerecho;
                }
                else // Estamos borrando la raiz del árbol
                {
                    printf("Borramos raiz\n");
                    // Colocar como raiz el nodo más pequeño del hijo derecho
                    // O el más grande del hijo izquierdo...
                    pNodo otroNodoMas;
                    otroNodoMas = minimoHijoDerecho(&miNodo, 0);
                    if(buscado!=(padreDeArbol(arbol, otroNodoMas->codigo, padre))->codigo)
                    {
                        (padreDeArbol(arbol, otroNodoMas->codigo, padre))->hijoIzquierdo = NULL;
                    }
                    else
                    {
                        (padreDeArbol(arbol, otroNodoMas->codigo, padre))->hijoDerecho = NULL;
                    }
                    (miNodo->codigo)=(otroNodoMas->codigo);
                    strcpy((miNodo->nombre),(otroNodoMas->nombre));
                }
            }
            // Que tenga solo el hijo izquierdo
            else if((miNodo->hijoIzquierdo)!=NULL)
            {
                if(codigoPadre>buscado)
                {
                    (*padre)->hijoIzquierdo = miNodo->hijoDerecho;
                }
                else if(codigoPadre<buscado)
                {
                    (*padre)->hijoDerecho = miNodo->hijoIzquierdo;
                }
                else // Estamos borrando la raiz del árbol
                {
                    printf("Borramos raiz\n");
                    // Colocar como raiz el nodo apuntado por miNodo->hijoIzquierdo
                    *arbol = miNodo->hijoIzquierdo;
                }
            }
            // Que tenga solo el hijo derecho
            else if((miNodo->hijoDerecho)!=NULL)
            {
                if(codigoPadre>buscado)
                {
                    (*padre)->hijoIzquierdo = miNodo->hijoDerecho;
                }
                else if(codigoPadre<buscado)
                {
                    (*padre)->hijoIzquierdo = miNodo->hijoDerecho;
                }
                else // Estamos borrando la raiz del árbol
                {
                    printf("Borramos raiz\n");
                    // Colocar como raiz el nodo apuntado por miNodo->hijoDerecho
                    *arbol = miNodo->hijoDerecho;
                }
            }
        }
        else if(((miNodo->codigo)<(buscado))&&(miNodo->hijoDerecho!=NULL))
        {
            // Seguimos avanzando por la derecha
            borrarArbol(&(miNodo->hijoDerecho), buscado, &miNodo);
        }
        else if(((miNodo->codigo)>(buscado))&&(miNodo->hijoIzquierdo!=NULL))
        {
            // Seguimos avanzando por la izquierda
            borrarArbol(&(miNodo->hijoIzquierdo), buscado, &miNodo);
        }
    }
}

pNodo minimoHijoDerecho(Arbol *arbol, int fase)
{
    pNodo miNodo; // Variable auxiliar para manipular un nodo
    miNodo = *arbol;

    if((miNodo->hijoIzquierdo)==NULL)
    {
        return (miNodo);
    }
    else
    {
        if(fase==0)
        {
            return(minimoHijoDerecho(&(miNodo->hijoDerecho), 1));
        }
        else
        {
            return(minimoHijoDerecho(&(miNodo->hijoIzquierdo), 1));
        }

    }
}

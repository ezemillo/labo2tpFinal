#include "clientes.h"


int idClienteNuevo(char archivo[])
{
    FILE *archi;
    archi = fopen(archivo, "rb");
    stCliente a;
    int i = 0;
    if (archi != NULL)
    {
        fseek(archi, sizeof(stCliente), SEEK_END);
        i = ftell(archi) / sizeof(stCliente);
    }
    return i++;
}


void bajaDeCliente(char archivo[])
{
    stCliente cliente;
    FILE *archivito;
    archivito = fopen(archivo, "r+b");
    int aux = 0;
    char ok = 's';
    char myUserName[20];

    printf("Ingrese el usuario que quiere dar de baja\n");
    fflush(stdin);
    scanf("%s", myUserName);

    if (archivito != NULL && ok == 's')
    {
        while (aux == 0 && (fread(&cliente, sizeof(stCliente), 1, archivito) > 0))
        {

            if (strcmp(cliente.userName, myUserName) == 0)
            {
                cliente.activo = 0;
                fseek(archivito, (-1) * sizeof(stCliente), SEEK_CUR);
                fwrite(&cliente, sizeof(stCliente), 1, archivito);
                aux = 1;
            }
        }
    }
    fclose(archivito);
}



void altaDeCliente(char archivo[], int rol)
{
    stCliente cliente;
    FILE *archivito;
    archivito = fopen(archivo, "ab");
    int var;

    if (archivito != NULL)
    {
        cliente.idCliente = idClienteNuevo(archivo);

        do
        {
            printf("Ingrese nombre: ");
            fflush(stdin);
            scanf("%s", cliente.nombre);
        }
        while (strlen(cliente.nombre) > 30);
        do
        {
            printf("Ingrese apellido: ");
            fflush(stdin);
            scanf("%s", cliente.apellido);
        }
        while (strlen(cliente.apellido) > 30);
        do
        {
            printf("Ingrese username: ");
            fflush(stdin);
            scanf("%s", cliente.userName);
            var = verificarClienteYaExiste(archivo, cliente);
        }
        while (var == 0 || strlen(cliente.userName) > 20);
        do
        {
            printf("Ingrese password: ");
            fflush(stdin);
            scanf("%s", cliente.password);
        }
        while (strlen(cliente.password) > 20);

        do
        {
            printf("Ingrese email: ");
            fflush(stdin);
            scanf("%s", cliente.mail);
        }
        while (strlen(cliente.mail) > 30);
        do
        {
            printf("Ingrese genero (M/F): ");
            fflush(stdin);
            scanf("%c", &cliente.genero);
        }
        while (cliente.genero != 'm' && cliente.genero != 'f');
        if (rol == 1)
        {
            cliente.rol = 1;
        }
        else
        {
            cliente.rol = 0;
        }
        cliente.activo = 1;

        fwrite(&cliente, sizeof(stCliente), 1, archivito);
        fclose(archivito);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
}

int verificarClienteYaExiste(char archivo[], stCliente clienteIngreso)
{
    FILE *archivito;
    stCliente cliente;
    archivito = fopen(archivo, "rb");
    int resultado;

    if (archivito != NULL)
    {
        while (fread(&cliente, sizeof(stCliente), 1, archivito) > 0)
        {
            resultado = strcmp(cliente.userName, clienteIngreso.userName);

            if (resultado == 0)
            {
                printf("YA EXISTE EL USERNAME\n");
            }
        }
    }
    return resultado;
}


int login(char archivo[], int *idCliente)
{
    FILE *archivito;
    stCliente cliente;
    stCliente clienteIngreso;
    archivito = fopen(archivo, "rb");
    int rol, resultadoUser, resultadoPass = 2;

    // se usa solo en el primer login cuando no hay admin y no existe el archivo de clientes

    if (archivito == NULL)
    {
        puts("No se encontro el usuario admin, vamos a crearlo");
        altaDeClienteAdmin(archivo);
        system("cls");
        archivito = fopen(archivo, "rb");
    }
    if (archivito != NULL)
    {
        puts("--Login--");
        printf("Ingrese username\n");
        fflush(stdin);
        scanf("%s", clienteIngreso.userName);
        printf("Ingrese password\n");
        fflush(stdin);
        scanf("%s", clienteIngreso.password);
        while (resultadoUser != 0 && resultadoPass != 0 && fread(&cliente, sizeof(stCliente), 1, archivito) > 0)
        {
            resultadoUser = strcmpi(cliente.userName, clienteIngreso.userName);
            if (resultadoUser == 0)
            {
                resultadoPass = strcmpi(cliente.password, clienteIngreso.password);
            }
        }
    }
    if (resultadoUser == 0 && resultadoPass == 0 && cliente.activo == 1)
    {
        printf("\nIngresaste con exito\n");
        rol = cliente.rol;
        Sleep(500);
        *idCliente = cliente.idCliente;
    }
    else if (resultadoUser != 0)
    {
        printf("\tEL USUARIO INGRESADO NO EXISTE\n");
        printf("\tPOR FAVOR, REGISTRE UN NUEVO USUARIO\n");
        Sleep(1000);
    }
    else if (resultadoPass != 0)
    {
        printf("\tContrase%ca incorrecta\n", 164);
        Sleep(500);
    }
    else if (cliente.activo == 0)
    {

        puts("Tu cuenta se encuentra inactiva, comunicate con el administrador");
        Sleep(2000);
    }

    fclose(archivito);

    return rol;
}

void MostrarArchivoClientes(char archivo[])
{
    FILE *archivito;
    stCliente cliente;
    archivito = fopen(archivo, "rb");
    int i = 0;

    if (archivito != NULL)
    {
        while (fread(&cliente, sizeof(stCliente), 1, archivito) > 0)
        {
            printf("\n Registro numero %d", i++);
            puts("\n-------------------------------------");
            printf("\n IdCliente: %d", cliente.idCliente);
            printf("\n Nombre: %s", cliente.nombre);
            printf("\n Apellido: %s", cliente.apellido);
            printf("\n Username: %s", cliente.userName);
            printf("\n Password: %s", cliente.password);
            printf("\n Mail: %s", cliente.mail);
            printf("\n Genero: %c", cliente.genero);
            printf("\n Rol: %d", cliente.rol);
            printf("\n Activo: %d", cliente.activo);
            puts("\n-------------------------------------");
        }
    }
    fclose(archivito);
}


void gestionarModificarCliente(char pedidos[], char productos[], char clientes[], int *id, int opcionSeleccionada, int rol)
{
    stCliente cliente;
    FILE *archivito;
    archivito = fopen(clientes, "r+b");
    int resultado = 0;
    char usuario[20];
    if (archivito != NULL)
    {
        while (fread(&cliente, sizeof(stCliente), 1, archivito) > 0)
        {

            if (cliente.idCliente == *id)
            {
                switch (opcionSeleccionada)
                {
                case 0:
                    printf("\nIngrese nuevo nombre:");
                    fflush(stdin);
                    scanf("%s", cliente.nombre);
                    break;
                case 1:
                    printf("\nIngrese nuevo apellido:");
                    fflush(stdin);
                    scanf("%s", cliente.apellido);
                    break;
                case 2:
                    do
                    {
                        printf("\nIngrese nuevo usuario: ");
                        fflush(stdin);
                        scanf("%s", cliente.userName);
                        resultado = verificarClienteYaExiste(clientes, cliente);
                    }
                    while (resultado == 0);
                    break;
                case 3:
                    printf("\nIngrese nueva password: ");
                    fflush(stdin);
                    scanf("%s", cliente.password);
                    break;
                case 4:
                    printf("\nIngrese nuevo mail: ");
                    fflush(stdin);
                    scanf("%s", cliente.mail);
                    break;
                case 5:
                    if (rol == 1)
                    {
                        volverAlMenuAdministrador(clientes, pedidos, productos, id);
                    }
                    else
                    {
                        volverAlMenuClientes(clientes, pedidos, productos, id);
                    }
                    break;
                }

                fseek(archivito, (-1) * sizeof(stCliente), SEEK_CUR);
                fwrite(&cliente, sizeof(stCliente), 1, archivito);
                fseek(archivito, sizeof(stCliente), SEEK_END);
            }
        }
    }
    fclose(archivito);
    if (rol == 1)
    {
        volverAlMenuAdministrador(clientes, pedidos, productos, id);
    }
    else
    {
        volverAlMenuClientes(clientes, pedidos, productos, id);
    }
}



void altaDeClienteAdmin(char archivo[])
{
    altaDeCliente(archivo, 1);
}

int archivoClienteToArray (char clientes[],stCliente arrayClientes[], int dimension)
{

    FILE * puntFile = fopen(clientes,"rb");
    stCliente unCliente;
    int i=0;

    if(puntFile)
    {
        while(i<dimension && fread(&unCliente,sizeof(stCliente),1,puntFile)>0)
        {
            arrayClientes[i] = unCliente;
            i++;
        }
        fclose(puntFile);

    }

return i;



}

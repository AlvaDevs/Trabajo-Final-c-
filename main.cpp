/*
    Integrantes del grupo:
    Álvaro Álvarez - T00070257
    Mariana Oliver - 
    David Pelaez - 
    Camila Amador - 
*/

//líbrerias y namespace
#include <iostream> //líbreria para la entrada/salida de datos
#include <iomanip> //líbreria para controlar el formato de entrada/salida
#include <fstream> //líbreria para el manejo de archivos
#include <cmath> //líbreria para funciones matemáticas
using namespace std;  //namespace para evitar poner todo el nombre al principio de las funciones o variables
string linea; //variable global linea usada en todo

//estructura de los estudiantes
struct Estudiante {
    string codigoEst; //varibale que guarda el codigo del estudiante en un string
    string apellidoEst; //varibale que guarda el apellido del estudiante en un string
    string nombreEst; //varibale que guarda el nombre del estudiante en un string
    double corte1; //varibale que guarda la nota del corte 1 del estudiante en un double
    double corte2; //varibale que guarda la nota del corte 2 del estudiante en un double
    double corte3; //varibale que guarda la nota del corte 3 del estudiante en un double
    double banner; //varibale que guarda la nota final del banner del estudiante en un double
} est[50]; //se define el arreglo tipo estructura

//prototipo de las funciones
void menu(); //funcion que muestra el menu
void contarLineas(int &); //función para leer la cantidad de lineas en el archivo
void cargarDatos(Estudiante[], int); //función para la obtención de los datos apartir de la base "datos.csv"
void imprimirDatos(Estudiante[], int); //función para imprimir los datos de los estudiantes
double promedioCurso(Estudiante[], int); //función para calcular e imprimir el promedio (de la calificación final) de los estudiantes
void superioresInferiores(Estudiante[], int, double); //función para imprimir los estudiantes superiores e inferiores
void mejorRegular(Estudiante[], int); //función para imprimir los estudiantes que obtuvieron la mejor y peor nota
void mejorRegularCortes(Estudiante[], int); //función para imprimir los estudiantes que obtuvieron la mejor y peor nota por corte
void calcularModa(Estudiante[], int); //función para calcular la moda de los estudiantes
void calcularNotaRequerida(Estudiante[], int); //función para calcular la nota requerida para aprobar

//inicio del programa principal
int main() {
    int cantidadEst = 0; //variable que guarda el número de estudiantes
    char opcion = '0'; //variable que guarda la opción del usuario
    cout << fixed << setprecision(1); //formato global de salida a exepción de ser cambiado explicitamente

    contarLineas(cantidadEst); //llamada a la función contarLineas para tener la cantidad de estudiantes
    cargarDatos(est, cantidadEst); //llamada a la función cargarDatos para cargar los datos de los estudiantes
    double promedio = promedioCurso(est, cantidadEst); //promedio global de los estudiantes

    //menú de opciones
    while (opcion != 8){
        system("clear"); //limpiar la pantalla

        menu(); //llamada a la función menu para mostrar el menú
        cin >> opcion;

        switch (opcion) {
        case '1':
            imprimirDatos(est, cantidadEst);
            break;
        case '2':
            system("clear"); //limpiar la pantalla
            cout << "El promedio del curso es: " << fixed << setprecision(2) << promedio << endl;
            cin.ignore(); cin.get(); //esperar a que el usuario teclee para continuar
            break;
        case '3':
            superioresInferiores(est, cantidadEst, promedio);
            break;
        case '4':
            mejorRegular(est, cantidadEst);
            break;
        case '5':
            mejorRegularCortes(est, cantidadEst);
            break;
        case '6':
            calcularModa(est, cantidadEst);
            break;
        case '7':
            calcularNotaRequerida(est, cantidadEst);
            break;
        default:
            cout << "\n\n\t¡OPCIÓN INVALIDA!";
            cin.ignore(); cin.get(); //esperar a que el usuario teclee para continuar
            opcion = '0';
        }

        fflush(stdin); //limpiar el buffer de entrada
    }

    cout << "CHAU!!!";

    return 0;
} //fin del programa principal

void menu() {
    cout << "\n\tMENÚ PRINCIPAL" << endl;
    cout << ">> 1. Ver los datos basico de los estudiantes." << endl;
    cout << ">> 2. Ver el promedio del curso en general." << endl;
    cout << ">> 3. Ver a los estudiantes superiores e inferiores al promedio." << endl;
    cout << ">> 4. Ver a los mejores y regulares." << endl;
    cout << ">> 5. Ver a los mejores y regulares de cada corte." << endl;
    cout << ">> 6. Ver la moda (calificación más repetida) del curso." << endl;
    cout << ">> 7. Calculadora de la nota final requerida" << endl;
    cout << ">> 8. Salir del programa" << endl;
    cout << "Digite la opción deseada: ";
}

//ejecución de las funciones
void contarLineas(int &cantidadEst) {
    ifstream archivo; //variable de tipo archivo
    archivo.open("datos.csv"); //abrimos el archivo "datos.csv"

    //confirmar la correcta lectura de un archivo
    if (archivo.good() == 1) {
        cout << "Existe el archivo" << endl;
        //ciclo para contar las lineas del archivo
        while (!archivo.eof()) {
            getline(archivo, linea);
            cantidadEst++; //aumentamos en 1 la variable cantidadEst
        }
        cout << "Tiene " << cantidadEst << " lineas" << endl;
    } else {
        cout << "No existe el archivo" << endl;
    }
    archivo.close(); //cerramos el archivo "datos.csv"
    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(); cin.get(); //esperar a que el usuario teclee para continuar
}

void cargarDatos(Estudiante est[], int n) {
    ifstream archivo; //variable de tipo archivo
    archivo.open("datos.csv"); //abrimos el archivo "datos.csv"

    //ciclo para obtener los datos por linea
    for (int i = 0; i < n; i++) { 
        getline(archivo, linea, ';'); est[i].codigoEst = linea; //obtenemos el codigo del estudiante
        getline(archivo, linea, ';'); est[i].apellidoEst = linea; //obtenemos el apellido del estudiante
        getline(archivo, linea, ';'); est[i].nombreEst = linea; //obtenemos el nombre del estudiante
        getline(archivo, linea, ';'); est[i].corte1 = atof(linea.c_str()); //obtenemos la nota del corte 1 del estudiante
        getline(archivo, linea, ';'); est[i].corte2 = atof(linea.c_str()); //obtenemos la nota del corte 2 del estudiante
        getline(archivo, linea); est[i].corte3 = atof(linea.c_str()); //obtenemos la nota del corte 3 del estudiante

        est[i].banner = est[i].corte1 * 0.3 + est[i].corte2 * 0.35 + est[i].corte3 * 0.35; //calculamos la nota final del banner
        est[i].banner = round(est[i].banner * 10) / 10; //redondeamos la nota final del banner
    }
    archivo.close(); //cerramos el archivo "datos.csv"
}

void imprimirDatos(Estudiante est[], int n) {
    system("clear"); //limpiar la pantalla

    cout << "Codigo\tApellido\tNombre\tCorte1\tCorte2\tCorte3\tBanner" << endl;
    for (int i = 0; i < n; i++) {
        cout << est[i].codigoEst << "\t"; //imprimimos el codigo del estudiante
        cout << setw(7.5) << est[i].apellidoEst << "\t"; //imprimimos el apellido del estudiante
        cout << setw(9) << est[i].nombreEst << "\t"; //imprimimos el nombre del estudiante
        cout << setw(7.5) << est[i].corte1 << "\t"; //imprimimos la nota del corte 1 del estudiante
        cout << setw(7.5) << est[i].corte2 << "\t"; //imprimimos la nota del corte 2 del estudiante
        cout << setw(7.5) << est[i].corte3 << "\t"; //imprimimos la nota del corte 3 del estudiante
        cout << setw(7.5) << est[i].banner << endl; //imprimimos la nota final del banner del estudiante
    }

    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(); cin.get(); //esperar a que el usuario teclee para continuar
}

double promedioCurso(Estudiante est[], int n) {
    system("clear"); //limpiar la pantalla

    double promedio = 0.0; //variable para guardar el promedio

    //calculo del promedio mediante un ciclo y una posterior división
    for(int i = 0; i < n; i++) {
        promedio += est[i].banner;
    }
    promedio = promedio / n;

    return promedio; //retornar el promedio
}

void superioresInferiores(Estudiante est[], int n, double prom) {
    system("clear"); //limpiar la pantalla

    cout << "Teniendo en cuenta el promedio (" << fixed << setprecision(2) << prom << "), clasificamos a los estudiantes en: " << endl;

    cout << "\n\tESTUDIANTES SUPERIORES E IGUALES AL PROMEDIO: " << endl;
    cout << "Codigo\tApellido\tNombre\tBanner" << endl;
    //evaluar que cumpla los criterios
    for (int i = 0; i < n; i++) {
        if (est[i].banner >= prom) {
            cout << est[i].codigoEst << "\t"; //imprimimos el codigo del estudiante
            cout << setw(7.5) << est[i].apellidoEst << "\t"; //imprimimos el apellido del estudiante
            cout << setw(9) << est[i].nombreEst << "\t"; //imprimimos el nombre del estudiante
            cout << setw(7.5) << est[i].banner << endl; //imprimimos la nota final del banner del estudiante
        }
    }

    cout << "\n\tESTUDIANTES INFERIORES AL PROMEDIO: " << endl;
    cout << "Codigo\tApellido\tNombre\tBanner" << endl;
    //evaluar que cumpla los criterios
    for (int i = 0; i < n; i++) {
        if (est[i].banner < prom) {
            cout << est[i].codigoEst << "\t"; //imprimimos el codigo del estudiante
            cout << setw(7.5) << est[i].apellidoEst << "\t"; //imprimimos el apellido del estudiante
            cout << setw(9) << est[i].nombreEst << "\t"; //imprimimos el nombre del estudiante
            cout << setw(7.5) << est[i].banner << endl; //imprimimos la nota final del banner del estudiante
        }
    }

    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(); cin.get(); //esperar a que el usuario teclee para continuar
}

void mejorRegular(Estudiante est[], int n) {
    system("clear"); //limpiar la pantalla

    //crear por defecto de las notas más altas y bajas
    double notaMasAlta = 0.0;
    double notaMasBaja = 5.0;

    //cliclo para verificar el valor de la notas
    for (int i = 0; i < n; i++) {
        if (est[i].banner > notaMasAlta) {
            notaMasAlta = est[i].banner;
        }
        if (est[i].banner < notaMasBaja) {
            notaMasBaja = est[i].banner;
        }
    }

    cout << "\n\tNOTA MÁS ALTA: " << endl;
    cout << "Codigo\tApellido\tNombre\tBanner" << endl;
    //evaluar que cumpla los criterios
    for (int i = 0; i < n; i++) {
        if (est[i].banner == notaMasAlta) {
            cout << est[i].codigoEst << "\t"; //imprimimos el codigo del estudiante
            cout << setw(7.5) << est[i].apellidoEst << "\t"; //imprimimos el apellido del estudiante
            cout << setw(9) << est[i].nombreEst << "\t"; //imprimimos el nombre del estudiante
            cout << setw(7.5) << est[i].banner << endl; //imprimimos la nota final del banner del estudiante
        }
    }

        cout << "\n\tNOTA MÁS BAJA: " << endl;
    cout << "Codigo\tApellido\tNombre\tBanner" << endl;
    //evaluar que cumpla los criterios
    for (int i = 0; i < n; i++) {
        if (est[i].banner == notaMasBaja) {
            cout << est[i].codigoEst << "\t"; //imprimimos el codigo del estudiante
            cout << setw(7.5) << est[i].apellidoEst << "\t"; //imprimimos el apellido del estudiante
            cout << setw(9) << est[i].nombreEst << "\t"; //imprimimos el nombre del estudiante
            cout << setw(7.5) << est[i].banner << endl; //imprimimos la nota final del banner del estudiante
        }
    }

    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(); cin.get(); //esperar a que el usuario teclee para continuar
}

void mejorRegularCortes(Estudiante est[], int n) {
    system("clear"); //limpiar la pantalla

    //crear por defecto de las notas más altas y bajas
    //corte 1
    double notaMasAlta1 = 0.0;
    double notaMasBaja1 = 5.0;

    //corte 2
    double notaMasAlta2 = 0.0;
    double notaMasBaja2 = 5.0;

    //corte 3
    double notaMasAlta3 = 0.0;
    double notaMasBaja3 = 5.0;

    //cliclo para verificar el valor de la notas
    //corte1
    for (int i = 0; i < n; i++) {
        if (est[i].corte1 > notaMasAlta1) {
            notaMasAlta1 = est[i].corte1;
        }
        if (est[i].corte1 < notaMasBaja1) {
            notaMasBaja1 = est[i].corte1;
        }
    }

    //corte2
    for (int i = 0; i < n; i++) {
        if (est[i].corte2 > notaMasAlta2) {
            notaMasAlta2 = est[i].corte2;
        }
        if (est[i].corte2 < notaMasBaja2) {
            notaMasBaja2 = est[i].corte2;
        }
    }

    //corte3
    for (int i = 0; i < n; i++) {
        if (est[i].corte3 > notaMasAlta3) {
            notaMasAlta3 = est[i].corte3;
        }
        if (est[i].corte3 < notaMasBaja3) {
            notaMasBaja3 = est[i].corte3;
        }
    }

    cout << "\n\tNOTA MÁS ALTA DEL CORTE 1: " << endl;
    cout << "Codigo\tApellido\tNombre\tcorte1" << endl;
    //evaluar que cumpla los criterios
    for (int i = 0; i < n; i++) {
        if (est[i].corte1 == notaMasAlta1) {
            cout << est[i].codigoEst << "\t"; //imprimimos el codigo del estudiante
            cout << setw(7.5) << est[i].apellidoEst << "\t"; //imprimimos el apellido del estudiante
            cout << setw(9) << est[i].nombreEst << "\t"; //imprimimos el nombre del estudiante
            cout << setw(7.5) << est[i].corte1 << endl; //imprimimos la nota final del corte 1 del estudiante
        }
    }

    cout << "\n\tNOTA MÁS BAJA DEL CORTE 1: " << endl;
    cout << "Codigo\tApellido\tNombre\tcorte1" << endl;
    //evaluar que cumpla los criterios
    for (int i = 0; i < n; i++) {
        if (est[i].corte1 == notaMasBaja1) {
            cout << est[i].codigoEst << "\t"; //imprimimos el codigo del estudiante
            cout << setw(7.5) << est[i].apellidoEst << "\t"; //imprimimos el apellido del estudiante
            cout << setw(9) << est[i].nombreEst << "\t"; //imprimimos el nombre del estudiante
            cout << setw(7.5) << est[i].corte1 << endl; //imprimimos la nota final del corte 1 del estudiante
        }
    }

    cout << "\n\t----------------------------------" << endl; //separación

    cout << "\n\tNOTA MÁS ALTA DEL CORTE 2: " << endl;
    cout << "Codigo\tApellido\tNombre\tcorte2" << endl;
    //evaluar que cumpla los criterios
    for (int i = 0; i < n; i++) {
        if (est[i].corte2 == notaMasAlta2) {
            cout << est[i].codigoEst << "\t"; //imprimimos el codigo del estudiante
            cout << setw(7.5) << est[i].apellidoEst << "\t"; //imprimimos el apellido del estudiante
            cout << setw(9) << est[i].nombreEst << "\t"; //imprimimos el nombre del estudiante
            cout << setw(7.5) << est[i].corte2 << endl; //imprimimos la nota final del corte 1 del estudiante
        }
    }

    cout << "\n\tNOTA MÁS BAJA DEL CORTE 2: " << endl;
    cout << "Codigo\tApellido\tNombre\tcorte2" << endl;
    //evaluar que cumpla los criterios
    for (int i = 0; i < n; i++) {
        if (est[i].corte2 == notaMasBaja2) {
            cout << est[i].codigoEst << "\t"; //imprimimos el codigo del estudiante
            cout << setw(7.5) << est[i].apellidoEst << "\t"; //imprimimos el apellido del estudiante
            cout << setw(9) << est[i].nombreEst << "\t"; //imprimimos el nombre del estudiante
            cout << setw(7.5) << est[i].corte2 << endl; //imprimimos la nota final del corte 1 del estudiante
        }
    }

    cout << "\n\t----------------------------------" << endl; //separación

    cout << "\n\tNOTA MÁS ALTA DEL CORTE 3: " << endl;
    cout << "Codigo\tApellido\tNombre\tcorte3" << endl;
    //evaluar que cumpla los criterios
    for (int i = 0; i < n; i++) {
        if (est[i].corte3 == notaMasAlta3) {
            cout << est[i].codigoEst << "\t"; //imprimimos el codigo del estudiante
            cout << setw(7.5) << est[i].apellidoEst << "\t"; //imprimimos el apellido del estudiante
            cout << setw(9) << est[i].nombreEst << "\t"; //imprimimos el nombre del estudiante
            cout << setw(7.5) << est[i].corte3 << endl; //imprimimos la nota final del corte 1 del estudiante
        }
    }

    cout << "\n\tNOTA MÁS BAJA DEL CORTE 3: " << endl;
    cout << "Codigo\tApellido\tNombre\tcorte3" << endl;
    //evaluar que cumpla los criterios
    for (int i = 0; i < n; i++) {
        if (est[i].corte3 == notaMasBaja3) {
            cout << est[i].codigoEst << "\t"; //imprimimos el codigo del estudiante
            cout << setw(7.5) << est[i].apellidoEst << "\t"; //imprimimos el apellido del estudiante
            cout << setw(9) << est[i].nombreEst << "\t"; //imprimimos el nombre del estudiante
            cout << setw(7.5) << est[i].corte3 << endl; //imprimimos la nota final del corte 1 del estudiante
        }
    }

    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(); cin.get(); //esperar a que el usuario teclee para continuar
}

void calcularModa(Estudiante est[], int n) {
    system("clear"); //limpiar la pantalla

    int contador1 = 0, contador2 = 0; //contadores para la moda
    double moda; //variable que almacenara la moda

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (est[i].banner == est[j].banner && i != j) { //no contar el mismo número como repetición
                contador1++; //aumento en 1 si se cumple las condiciones de repetición
            }
        }    

        if (contador1 > contador2) {
            contador2 = contador1;
            moda = est[i].banner; //definir el valor de la moda
        }

        contador1 = 0; //reiniciar el contador para la siguiente iteración
    }

    cout << "La moda es: " << moda << endl;

    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(); cin.get(); //esperar a que el usuario teclee para continuar
}

void calcularNotaRequerida(Estudiante est[], int n) {
    system("clear"); //limpiar la pantalla

    cout << "\n\tBIENVENIDO A LA CALCULADORA DE NOTA!" << endl;
    cout << "Ingrese el codigo de un estudiante para saber que nota mínima requiere en el tercer corte para aprobar la materia" << endl;
    cout << "\nEJEMPLO: \"COD00\"" << endl;

    string codigoEstudiante; //variables para leer y comprara el codigo del estudiante
    char continuar = 'n'; //variable para que el usuario pueda salir del programa

    do { //bucle para la solicitud de codigos
        cout << "\n\nIngres el codigo (en mayúsculas): ";
        cin >> codigoEstudiante;

        for (int i = 0; i < n; i++) {
            if (codigoEstudiante == est[i].codigoEst) {
                cout << "El estudiante con el codigo " << codigoEstudiante << " tiene las siguientes notas: " << endl;
                cout << "Corte1\tCorte2\n" << endl;
                cout << est[i].corte1 << "\t"; //imprimimos la nota del corte 1 del estudiante
                cout << setw(7.5) << est[i].corte2 << endl; //imprimimos la nota del corte 2 del estudiante

                double notaMinima = (3.0 - (0.3 * est[i].corte1) - (0.35 * est[i].corte2)) / 0.35; // calculo del mínimo requerido

                if(notaMinima <= 0.0){
                    cout << "\nPor lo que el estudiante tiene la materia a salvo, no necesita nota en el tercer corte.";
                } else{
                    cout << "\nPor lo que la nota minima requerida en el tercer corte es de: " << notaMinima; 
                }
                break;
            } else if (i == n-1 && codigoEstudiante != est[i].codigoEst) {
                cout << "CODIGO NO ENCONTRADO";
            }
        }

        cout << "\n\n\t¿Desea continuar? s/n: ";
        cin >> continuar;
        fflush(stdin); //limpiar el buffer de entrada
    } while (continuar != 'n' && continuar != 'N');

    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(); cin.get(); //esperar a que el usuario teclee para continuar
}
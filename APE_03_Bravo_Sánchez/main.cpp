#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <stdexcept>

using namespace std;

struct Estudiante {
    string nombreEstudiante;
    char paralelo;
    float n1, n2, practicas, promedio, asistencias;
    string estado;
    string categoria;
    string rendimiento;
};

string LeerNombre(string mensaje){
    string nombreEstudiante;

    while(true){
        cout<<mensaje;
        getline(cin>> ws, nombreEstudiante);

        bool valido = true;

        for(char c : nombreEstudiante){
            if(!isalpha(c) && !isspace(c)){
                valido = false;
                break;
            }
        }

        if(nombreEstudiante.empty()){
            cout<<"Error: El nombre del estudiante se encuentra vacio."<<endl;
        }else if(!valido){
            cout<<"Error: El nombre solo debe contener letras y espacios."<<endl;
        }else{
            return nombreEstudiante;
        }
    }
}

char LeerParalelo(string mensaje){
    char paralelo;

    while(true){
        cout<<mensaje;
        cin>> paralelo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        paralelo = toupper(paralelo);

        if(paralelo == 'A' || paralelo == 'B' || paralelo == 'C'){
            return paralelo;
        }else{
            cout << "Error: El paralelo solo puede ser A, B o C." << endl;
        }
    }
}

float LeerNotas(string mensaje, float min, float max){
    float nota;
    string texto;
    while(true){
        cout<<mensaje;
        getline(cin>> ws, texto);

        if(texto.empty()){
            cout<<"Error: El campo se encuentra vacio, Ingrese una nota."<<endl;
            continue;
        }

        try{
            nota = stof(texto);
            if(nota > max || nota < min){
               cout<<"Error: Ingrese una nota dentro del rango de "<<min<<" a "<<max<<" ."<<endl;
               continue;
            }
            return nota;

        }catch(invalid_argument& e){
            cout<<"Error: Ingrese una nota real."<<endl;
        }catch(out_of_range& e){
            cout<<"Error: El numero es demasiado grande."<<endl;
        }catch(...){
            cout<<"Error: Ingrese olo numeros."<<endl;
        }
    }
}

int LeerEstudiantes(string mensaje, int min){
    string texto;
    int n;

    while(true){
        cout<< mensaje;
        getline(cin >> ws, texto);
        if(texto.empty()){
            cout<<"Error.Llene el campo solicitado."<<endl;
            continue;
        }
        try{
            n = stoi(texto);
            if(n < min){
                cout << "Error: La cantidad debe ser al menos " << min << "." << endl;
                continue;
            }
            return n;

        }catch(invalid_argument& e){
            cout<<"Error.Ingrese solo numeros ."<<endl;
        }catch(out_of_range& e){
            cout<<"Error.El numero es muy grande."<<endl;
        }catch(...){
            cout<<"Error.Solo numeros."<<endl;
        }
    }
}

int main() {

    char repetir;

    do{
        system("cls");

            //Numero de estudiantes
            int total = LeerEstudiantes("Ingrese la cantidad de estudiantes a procesar: ", 1);


            // Contadores de categorias y estados

            // Estudiantes por paralelo
            int contadorCursoA = 0, contadorCursoB = 0, contadorCursoC = 0;

            // Categorias por calificacion del estudiante
            int contadorExcelente = 0, contadorMuyBueno = 0, contadorBueno = 0
            , contadorRiesgo = 0, cReprobadoNota = 0;

            //Contadores de estado y rendimiento

            // Estados
            int contadorReprobadosAsistencia = 0, contadorAprobados = 0;


            int contadorNotasEstable = 0, contadorNotasInestable = 0;


            // Acumuladores para promedios
            float sumaTotal = 0, sumaPromedioA = 0, sumaPromedioB = 0, sumaPromedioC = 0;


            // Para el mejor y peor estudiante
            float mejorPromedio = -1, peorPromedio = 11;
            string notaMejor, notaPeor;


            Estudiante* lista = new Estudiante[total];

            for (int i = 0; i < total; i++) {

                //Sistema de datos
                cout << "\n----------------------------------------";
                cout << "\nDATOS DEL ESTUDIANTE #" << i + 1 << endl;

                lista[i].nombreEstudiante = LeerNombre("Nombre del Estudiante (Completo): ");
                lista[i].paralelo = LeerParalelo("Paralelo del Estudiante (A/B/C): ");
                lista[i].n1 = LeerNotas("Nota del Primer Parcial : ", 0, 10);
                lista[i].n2 = LeerNotas("Nota del Segundo Parcial : ", 0, 10);
                lista[i].practicas = LeerNotas("Nota de Practicas del Estudiante: ", 0, 10);
                lista[i].asistencias = LeerNotas("Porcentaje de Asistencia (0-100): ", 0, 100);

                //Promedio Final Ponderado
                lista[i].promedio = (lista[i].n1 * 0.30) + (lista[i].n2 * 0.30) + (lista[i].practicas * 0.40);


                //Clasificacion del estudiante
                if (lista[i].promedio >= 9) lista[i].categoria = "Excelente";
                else if (lista[i].promedio >= 8) lista[i].categoria = "Muy bueno";
                else if (lista[i].promedio >= 7) lista[i].categoria = "Bueno";
                else if (lista[i].promedio >= 6) lista[i].categoria = "En riesgo";
                else lista[i].categoria = "Reprobado";


                //Sistema de asistencia
                if (lista[i].asistencias < 70) {
                    lista[i].estado = "Reprobado por asistencia";
                } else {
                    lista[i].estado = "Aprobado";
                    if (lista[i].promedio >= 9 && lista[i].asistencias < 80) {
                        lista[i].estado = "ALERTA ACADEMICA (Inconsistencia)";
                    }
                }


                //Sistema de Rendimiento
                float notaMax = max({lista[i].n1, lista[i].n2, lista[i].practicas});
                float notaMin = min({lista[i].n1, lista[i].n2, lista[i].practicas});

                if (lista[i].n1 == lista[i].n2 && lista[i].n2 == lista[i].practicas) {
                    lista[i].rendimiento = "Estable";
                }

                else if ((notaMax - notaMin) > 4) {
                    lista[i].rendimiento = "Inestable";
                }
                else {
                    lista[i].rendimiento = "Normal";
                }

                // 1. Acumuladores
                sumaTotal += lista[i].promedio;

                // 2. Por Paralelo
                if (lista[i].paralelo == 'A') {
                    contadorCursoA++;
                    sumaPromedioA += lista[i].promedio;

                } else if (lista[i].paralelo == 'B') {
                    contadorCursoB++;
                    sumaPromedioB += lista[i].promedio;

                } else if (lista[i].paralelo == 'C') {
                    contadorCursoC++;
                    sumaPromedioC += lista[i].promedio;
                }

                // 3 y 4. Categoría y Estado
                if (lista[i].categoria == "Excelente") contadorExcelente++;
                else if (lista[i].categoria == "Muy bueno") contadorMuyBueno++;
                else if (lista[i].categoria == "Bueno") contadorBueno++;
                else if (lista[i].categoria == "En riesgo") contadorRiesgo++;

                // Manejo preciso de reprobados y aprobados
                if (lista[i].estado == "Reprobado por asistencia") {
                    contadorReprobadosAsistencia++;

                } else if (lista[i].promedio < 6) { // Regla de la imagen anterior
                    cReprobadoNota++;

                } else {
                    contadorAprobados++;
                }

                // 5. Rendimiento
                if (lista[i].rendimiento == "Estable") contadorNotasEstable++;
                else if (lista[i].rendimiento == "Inestable") contadorNotasInestable++;

                // 6. Extremos (Mejor y Peor)
                if (lista[i].promedio > mejorPromedio) {
                    mejorPromedio = lista[i].promedio;
                    notaMejor = lista[i].nombreEstudiante;

                }
                if (lista[i].promedio < peorPromedio) {
                    peorPromedio = lista[i].promedio;
                    notaPeor = lista[i].nombreEstudiante;

                }

            }

            //1. Encabezadp
            cout << "\n" << setfill('=') << setw(105) << "=" << endl;
            cout << setfill(' ') << left
                 << setw(35) << "Nombre"
                 << setw(10) << "Prom"
                 << setw(12) << "Asis (%)"
                 << setw(28) << "Estado"
                 << "Rendimiento" << endl;
            cout << setfill('-') << setw(105) << "-" << setfill(' ') << endl;

            // 2. Cuerpo de la tabla
            for (int i = 0; i < total; i++) {

                string asisConSigno = to_string((int)lista[i].asistencias) + "%";

                cout << left
                     << setw(35) << lista[i].nombreEstudiante
                     << setw(10) << fixed << setprecision(2) << lista[i].promedio
                     << setw(12) << asisConSigno
                     << setw(28) << lista[i].estado
                     << lista[i].rendimiento << endl;
            }
            cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;

                // --- REPORTE GENERAL FINAL ---
            cout << fixed << setprecision(2);
            cout << "\n" << setfill('*') << setw(65) << "*" << endl;
            cout << setfill(' ') << "                RESUMEN ESTADISTICO DEL CURSO" << endl;
            cout << setfill('*') << setw(65) << "*" << setfill(' ') << endl;

            // 1, 2 y 3. Conteos básicos
            cout << "1. Total de estudiantes procesados: " << total << endl;
            cout << "2. Estudiantes por paralelo: [A: " << contadorCursoA
                 << "] [B: " << contadorCursoB << "] [C: " << contadorCursoC << "]" << endl;
            cout << "3. Categorias: [Exc: " << contadorExcelente << "] [MB: " << contadorMuyBueno
                 << "] [B: " << contadorBueno << "] [Riesgo: " << contadorRiesgo << "]" << endl;

            // 4 y 5. Reprobados
            cout << "4. Cantidad de reprobados por nota: " << cReprobadoNota << endl;
            cout << "5. Cantidad de reprobados por asistencia: " << contadorReprobadosAsistencia << endl;

            // 6 y 7. Promedios con validación
            cout << "6. Promedio general del curso: " << (total > 0 ? sumaTotal / total : 0.0) << endl;
            cout << "7. Promedio por paralelo: " << endl;
            cout << "   - Paralelo A: " << (contadorCursoA > 0 ? sumaPromedioA / contadorCursoA : 0.0) << endl;
            cout << "   - Paralelo B: " << (contadorCursoB > 0 ? sumaPromedioB / contadorCursoB : 0.0) << endl;
            cout << "   - Paralelo C: " << (contadorCursoC > 0 ? sumaPromedioC / contadorCursoC : 0.0) << endl;

            // 8 y 9. Extremos
            cout << "8. Mayor promedio: " << mejorPromedio << " (Estudiante: " << notaMejor << ")" << endl;
            cout << "9. Menor promedio: " << peorPromedio << " (Estudiante: " << notaPeor << ")" << endl;

            // 10, 11 y 12. Porcentajes
            if (total > 0) {
                cout << "10. Porcentaje de aprobados: " << (float)contadorAprobados / total * 100.0 << "%" << endl;
                cout << "11. Porcentaje rendimiento estable: " << (float)contadorNotasEstable / total * 100.0 << "%" << endl;
                cout << "12. Porcentaje rendimiento inestable: " << (float)contadorNotasInestable / total * 100.0 << "%" << endl;
            }

            cout << setfill('=') << setw(65) << "=" << setfill(' ') << endl;

        delete[] lista;

        cout << "\n" << setfill('-') << setw(65) << "-" << endl;
        cout << "   ¿Desea procesar todo el proceso para otro curso? (S/N): ";
        cin >> repetir;

        repetir = toupper(repetir);


    }while(repetir == 'S');

    cout << "\nSistema finalizo con exito. Presione una tecla para salir..." << endl;
    return 0;
}

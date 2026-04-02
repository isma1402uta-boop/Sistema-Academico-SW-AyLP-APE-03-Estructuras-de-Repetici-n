Algoritmo Gestion_Academica_Estudiantes
    // 1. Declaracion de Variables
    Definir total, i Como Entero
    Definir cA, cB, cC, cExc, cMB, cBno, cRiesgo, cRepNota, cRepAsis, cAprob, cEst, cInest Como Entero
    Definir n1, n2, prac, asis, prom, sumaT, sumaA, sumaB, sumaC, mejorP, peorP, nMax, nMin Como Real
    Definir nombre, paralelo, estado, categoria, rendimiento, mejorEst, peorEst, repeti Como Cadena
		
		Repetir
			// 2. Inicializacion de contadores y acumuladores
			cA<-0; cB<-0; cC<-0; cExc<-0; cMB<-0; cBno<-0; cRiesgo<-0
			cRepNota<-0; cRepAsis<-0; cAprob<-0; cEst<-0; cInest<-0
			sumaT<-0; sumaA<-0; sumaB<-0; sumaC<-0; mejorP<--1; peorP<-11
			
			Escribir "Ingrese la cantidad de estudiantes a procesar:"
			Leer total
			
			Para i <- 1 Hasta total Hacer
				Escribir "--- DATOS DEL ESTUDIANTE #", i, " ---"
				
				Escribir "Nombre Completo:"
				Leer nombre
				Escribir "Paralelo (A/B/C):"
				Leer paralelo
				paralelo <- Mayusculas(paralelo)
				
				Escribir "Nota Parcial 1 (0-10):"
				Leer n1
				Escribir "Nota Parcial 2 (0-10):"
				Leer n2
				Escribir "Nota Practicas (0-10):"
				Leer prac
				Escribir "Porcentaje de Asistencia (0-100):"
				Leer asis
				
				// 3. Calculos Academicos
				prom <- (n1 * 0.30) + (n2 * 0.30) + (prac * 0.40)
				sumaT <- sumaT + prom
				
				// Clasificacion por nota (Categoria)
				Si prom >= 9 Entonces 
					categoria <- "Excelente"
					cExc <- cExc + 1
				Sino 
					Si prom >= 8 Entonces 
						categoria <- "Muy Bueno"
						cMB <- cMB + 1
					Sino 
						Si prom >= 7 Entonces 
							categoria <- "Bueno"
							cBno <- cBno + 1
						Sino 
							Si prom >= 6 Entonces 
								categoria <- "En Riesgo"
								cRiesgo <- cRiesgo + 1
							Sino 
								categoria <- "Reprobado"
							FinSi
						FinSi
					FinSi
				FinSi
				
				// Estado por Asistencia
				Si asis < 70 Entonces
					estado <- "Reprobado por asistencia"
					cRepAsis <- cRepAsis + 1
				Sino
					Si prom < 6 Entonces
						estado <- "Reprobado por nota"
						cRepNota <- cRepNota + 1
					Sino
						estado <- "Aprobado"
						cAprob <- cAprob + 1
					FinSi
				FinSi
				
				// 4. Analisis de Rendimiento (Estabilidad)
				// Encontrar Maximo
				nMax <- n1
				Si n2 > nMax Entonces nMax <- n2 
				FinSi
		
			Si prac > nMax Entonces nMax <- prac 
			FinSi
				
				// Encontrar Minimo
				nMin <- n1
				Si n2 < nMin Entonces nMin <- n2 
				FinSi
			
			Si prac < nMin Entonces nMin <- prac 
			FinSi
				
				Si (n1 = n2 Y n2 = prac) Entonces
					rendimiento <- "Estable"
					cEst <- cEst + 1
				Sino 
					Si (nMax - nMin) > 4 Entonces
						rendimiento <- "Inestable"
						cInest <- cInest + 1
					Sino
						rendimiento <- "Normal"
					FinSi
				FinSi
				
				// 5. Estadisticas por Paralelo y Extremos
				Si paralelo = "A" Entonces 
					cA <- cA + 1
					sumaA <- sumaA + prom
				Sino 
					Si paralelo = "B" Entonces 
						cB <- cB + 1
						sumaB <- sumaB + prom
					Sino 
						cC <- cC + 1
						sumaC <- sumaC + prom
					FinSi
				FinSi
				
				Si prom > mejorP Entonces 
					mejorP <- prom
					mejorEst <- nombre
				FinSi
				
				Si prom < peorP Entonces 
					peorP <- prom
					peorEst <- nombre
				FinSi
				
				Escribir "Resultado: ", nombre, " - Promedio: ", prom, " - Estado: ", estado
			Fin Para
			
			// 6. Reporte Final
			Escribir "========================================="
			Escribir "RESUMEN ESTADISTICO"
			Escribir "Total Procesados: ", total
			Si total > 0 Entonces
				Escribir "Promedio General del Curso: ", sumaT / total
				Escribir "Mejor Estudiante: ", mejorEst, " (", mejorP, ")"
				Escribir "Peor Estudiante: ", peorEst, " (", peorP, ")"
				Escribir "Porcentaje de Aprobados: ", (cAprob / total) * 100, "%"
				Escribir "Rendimiento Estable: ", (cEst / total) * 100, "%"
			FinSi
			Escribir "========================================="
			
			Escribir "¿Desea procesar otro curso? (S/N):"
			Leer repeti
			Hasta Que(repeti = "N" O repeti = "n")
					
FinAlgoritmo
    
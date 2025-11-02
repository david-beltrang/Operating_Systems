#!/usr/bin/perl
#**************************************************************
#         		Pontificia Universidad Javeriana
#     Autor: David Esteban Beltrán Gómez
#     Fecha: 30 Octubre 2025
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización ejecución por lotes 
#****************************************************************/

# Se Obtiene el path del directorio actual
$Path = `pwd`;
# Si existe un salto de linea en el path se elimina
chomp($Path);


# Obtiene el nombre del ejecutable que se va a ejecutar
$Nombre_Ejecutable = "MM_ejecutable";
# Tamaños de las matrices a usar en un "Array"
@Size_Matriz = ("2","10","20");
# Cantidad de hilos con los que se ejecutara el programa en un "Array"
@Num_Hilos = (1,2,4,8,16,20);
# Cantidad de veces que se ejecutarán las combinaciones
$Repeticiones = 4;

# Variable para contar la cantidad de ejecuciones
$p = 0;

# Primer ciclo que itera en los tamaños de matriz que se definieron
foreach $size (@Size_Matriz){
	# Segundo ciclo anindado que itera en los hilos que se definieron
	foreach $hilo (@Num_Hilos) {
		# Genera el archivo de salida referente a la combinación de Matrices e Hilos
		$file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";
		# Tercer ciclo anidado que realiza las repeticiones indicadas
		for ($i=0; $i<$Repeticiones; $i++) {
			# Ejecuta el programa y lo que genere se guarda en el archivo
			system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");
			# Verificar si se ejecuto todo bien porque si no la funcion system() retorna un valor !=0
			if ($? != 0) {
    			print "Hubo un error al ejecutar el comando\n";
			}
			printf("$Path/$Nombre_Ejecutable $size $hilo \n");
			
			# Al completar otra ejecucion aumentar $p
        	$p = $p + 1;
        	print "Ejecución número $p completada\n";
		}
	}
}

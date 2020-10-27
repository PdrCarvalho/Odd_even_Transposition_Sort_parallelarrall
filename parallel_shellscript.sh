#!/bin/bash

#INFORMAÇÕES- Para rodar no computador pessoal.
# EXECUTAR NO TERMINAL: ./shellscript_start.sh
	#Caso não funcione, conceda permissão máxima ao este arquivo: chmod 777 shellscript_start.sh

#OPCIONAL: apagar arquivos temporários (gerados ou não pelo .c).
rm parallel_time.txt
rm parallel_code

#Compilação de Código. Modifique para o que mais se adequa a você.
mpicc -g -Wall parallel_code.c -o parallel_code

#OBRIGATÓRIO: Laço de iteração para resgate dos tempos de acordo com "cores" e "size"

#Loop principal de execuções. São 10 tentativas
	tentativas=1 #Quantas vezes o código será executado dado um par (cores,size)

	for cores in 4  #números de cores utilizados
	do
			for size in 20 #tamanho do problema
			do   	
				echo -e "\n$cores\t$size\t\t\c" >> "parallel_time.txt" 

				for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"
				do
					#Executar o código. Modifique para o que mais se adequa a você.
					mpirun -np  $cores --oversubscribe ./parallel_code $size $cores
					#no meu PC, tive que utilizar "--oversubscrive" para rodar. No seu pode não ser necessário. 
				done
			done

	done
	
	exit 




exit

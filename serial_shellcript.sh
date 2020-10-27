#!/bin/bash

#INFORMAÇÕES- Para rodar no computador pessoal.
# EXECUTAR NO TERMINAL: ./shellscript_start.sh
	#Caso não funcione, conceda permissão máxima ao este arquivo: chmod 777 shellscript_start.sh

#OPCIONAL: apagar arquivos temporários (gerados ou não pelo .c).
rm serial_time.txt
rm serial_code

#Compilação de Código. Modifique para o que mais se adequa a você.
g++ -g -Wall serial_code.c -o serial_code

#OBRIGATÓRIO: Laço de iteração para resgate dos tempos de acordo com "cores" e "size"

#Loop principal de execuções. São 10 tentativas
	tentativas=5 #Quantas vezes o código será executado dado um par (cores,size)

for size in  1000000 #tamanho do problema
        do   	
            echo -e "\n$size\t\t\c" >> "serial_time.txt" 

            for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"
            do
                #Executar o código. Modifique para o que mais se adequa a você.
                ./serial_code $size 
            done
        done

	exit 

exit
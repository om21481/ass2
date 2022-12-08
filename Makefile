om_2021481:
	gcc 1.1.c -o 1.1 -pthread
	gcc 1.2.c -o 1.2

	chmod u+x kernel1.sh
	chmod u+x kernel2.sh
	chmod u+x kernel3.sh

clean:
	rm ./1.1
	rm ./1.2
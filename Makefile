all: kbstore  
kbstore: main.c kbstore.c persistence.c  
	gcc -pthread -o kbstore main.c kbstore.c persistence.c  
clean:  
	rm -f kbstore

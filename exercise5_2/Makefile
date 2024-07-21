all:
	gcc -fPIC -c contact_list.c -o contact_list.o -std=c99
	gcc -shared contact_list.o libcontact_list.so
	gcc main.c -o main -ldl
clean:
	rm -f main contact_list.o libcontact_list.so

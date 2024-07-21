all:
	gcc -c contact_list.c -o contact_list.o -std=c99
	ar rc libcontact_list.a contact_list.o
	gcc main.c -o main -L. -lcontact_list
clean:
	rm -f main contact_list.o libcontact_list.a

test: structure_point_polygone.c gen_point.c test_gen_point.c
	gcc -c structure_point_polygone.c gen_point.c test_gen_point.c
	gcc -o test structure_point_polygone.o gen_point.o test_gen_point.o
	rm *.o

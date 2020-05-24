test: structure_point_polygone.c gen_point.c test_gen_point.c
	gcc -c structure_point_polygone.c gen_point.c test_gen_point.c
	gcc -o test structure_point_polygone.o gen_point.o test_gen_point.o
	rm *.o
test_entree:	test_entree.o entree_kml.o structure_point_polygone.o 
	cc test_entree.o entree_kml.o structure_point_polygone.o -o test_entree
test_entree.o:	structure_point_polygone.h entree_kml.h test_entree.c
	cc -c test_entree.c
entree_kml.o:	structure_point_polygone.h entree_kml.h entree_kml.c
	cc -c entree_kml.c
structure_point_polygone.o:	structure_point_polygone.h structure_point_polygone.c
	cc -c structure_point_polygone.c

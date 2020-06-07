all :	test_io	test_entree	test 	exe


exe:	structure_point_polygone.c gen_point.c exe.c entree_kml.c gen_graph.c
	cc structure_point_polygone.c entree_kml.c gen_point.c gen_graph.c exe.c sortie_pdf.c -c -I/usr/local/dislin -lm
	cc structure_point_polygone.o entree_kml.o gen_point.o sortie_pdf.o gen_graph.o exe.o -o exe -ldislin -L/usr/local/dislin -lm
	rm *.o



	

	
sortie_pdf.o :	structure_point_polygone.h sortie_pdf.c	
	cc -c sortie_pdf.c -I/usr/local/dislin
	

#entree


	
entree_kml.o :	structure_point_polygone.h entree_kml.h entree_kml.c
	cc -c entree_kml.c
	
	
#structures
	
#test_point_polygone :	test_point_polygone.o structure_point_polygone.o 
#	cc test_point_polygone.o structure_point_polygone.o -o test_point_polygone
#test_point_polygone.o :	structure_point_polygone.h test_point_polygone.c
#	cc -c test_point_polygone.c
	
structure_point_polygone.o :	structure_point_polygone.h structure_point_polygone.c
	cc -c structure_point_polygone.c
	

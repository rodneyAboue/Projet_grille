all :	exe

#Executable

exe:	structure_point_polygone.c gen_point.c exe.c entree_kml.c gen_graph.c
	gcc -c structure_point_polygone.c entree_kml.c gen_point.c gen_graph.c exe.c
	gcc -o exe structure_point_polygone.o entree_kml.o gen_point.o gen_graph.o exe.o -lm
	rm *.o


#PDF

test_io:	structure_point_polygone.o test_io.o entree_kml.o sortie_pdf.o
	cc test_io.o sortie_pdf.o entree_kml.o structure_point_polygone.o -o test_io -ldislin -L/usr/local/dislin

test_io.o:	entree_kml.h structure_point_polygone.h test_io.c
	cc -c test_io.c -I/usr/local/dislin

sortie_pdf.o:	structure_point_polygone.h sortie_pdf.c
	cc -c sortie_pdf.c -I/usr/local/dislin



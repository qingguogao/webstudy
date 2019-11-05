CC = gcc
OBJNAME = WebStudy

OBJECTS = main.o general.o service.o webStudy.o reg.o initfile.o HyperLink.o

$(OBJNAME): $(OBJECTS)
	$(CC) -fexec-charset=UTF-8 -finput-charset=GBK $(OBJECTS) -lgdi32 -lcomctl32 -mwindows -o $(OBJNAME) 

main.o: main.c main.h
	$(CC) -c main.c

HyperLink.o: HyperLink.c HyperLink.h
	$(CC) -c HyperLink.c 

general.o: general.c general.h
	   $(CC) -c general.c	

reg.o: reg.c reg.h
	$(CC) -c reg.c 

initfile.o: initfile.c initfile.h general.c general.h
	   $(CC) -c initfile.c 

service.o: service.c service.h general.c general.h
	   $(CC) -c service.c	

webStudy.o: webStudy.rc
	windres webStudy.rc webStudy.o


clean:
	rm $(OBJECTS)

OBJS = ./src/Cap_Converter.o ./src/Safe_Input.o #./src/FileFunctions.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
DS = ./src/
DH = ./headers/

Cap_Converter: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o Cap_Converter

Cap_Converter.o: $(DS)Cap_Converter.cpp $(DH)Safe_Input.h
	$(CC) $(CFLAGS) $(DS)Cap_Converter.cpp -o $(DS)Cap_Converter.o

Safe_Input.o: $(DS)Safe_Input.cpp $(DH)Safe_Input.h
	$(CC) $(CFLAGS) $(DS)Safe_Input.cpp -o $(DS)Safe_Input.o

#FileFunctions.o: $(DS)FileFunctions.cpp $(DH)FileFunctions.h
#	$(CC) $(CFLAGS) $(DS)FileFunctions.cpp -o $(DS)FileFunctions.o

clean:
	rm $(OBJS)

tar:
	tar -zcvf ../Sandbox.tar.gz ../Sandbox/


OBJ=obj/main.o obj/bmp.o obj/stego.o
CFLAGS:= -Iinclude -Wall -Wextra

.PHONY: all clean directories
all: hw-01_bmp

directories: obj

obj:
	mkdir -p obj

obj/main.o: src/main.c include/bmp.h include/stego.h | obj
	gcc -c $(CFLAGS) src/main.c -o obj/main.o

obj/bmp.o: src/bmp.c include/bmp.h | obj
	gcc -c $(CFLAGS) src/bmp.c -o obj/bmp.o

obj/stego.o: src/stego.c include/bmp.h include/stego.h | obj
	gcc -c $(CFLAGS) src/stego.c -o obj/stego.o

hw-01_bmp: $(OBJ)
	gcc -o hw-01_bmp $(OBJ)
	
clean:
	rm -rf obj/
	rm -rf hw-01_bmp

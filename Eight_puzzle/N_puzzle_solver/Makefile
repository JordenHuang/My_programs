CC=gcc
CFLAGS=-Wall -Wextra -std=c11 # -fsanitize=address -g
INCLUDE_PATH=-Isrc -Ithirdparty

main: src/main.c src/da.h src/ht.h src/arena.h thirdparty/stb_ds.h
	$(CC) $(CFLAGS) src/main.c -o main.exe $(INCLUDE_PATH)

checker: tools/checker.c
	$(CC) $(CFLAGS) tools/checker.c -o checker.exe

scrambler: tools/scrambler.c
	$(CC) $(CFLAGS) tools/scrambler.c -o scrambler.exe
#Compiler
CC=gcc
CFLAGS=-Wall -Wno-unused-result `pkg-config --cflags gtk+-3.0`
LIBS=`pkg-config --libs gtk+-3.0`

#Files
SRC=src/avl_app.c src/avl_win.c src/avl_entry.c src/avl_text_view.c src/avl_entry_button.c src/avl_text_button.c src/avltree.c src/resources.c
INCLUDE=include/
MAIN1=src/main.c
BIN1=prog

#Tools
RM=rm -vf


all: $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(MAIN1) $(SRC) -o $(BIN1) $(LIBS)

gresources:
	glib-compile-resources resource/avl_app.gresource.xml --target=src/resources.c --generate-source

clean:
	$(RM) *~ */*~

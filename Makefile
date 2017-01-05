#Compiler
CC=gcc
CFLAGS=-Wall -O3 -Wno-unused-result `pkg-config --cflags gtk+-3.0`
LIBS=`pkg-config --libs gtk+-3.0`

#Files
SRC=src/avl_app.c src/avl_win.c src/avl_entry.c src/avl_text_box.c	\
    src/avl_entry_button.c src/avl_text_button.c src/avltree.c		\
    src/avl_about_win.c src/resources.c
INCLUDE=include/
MAIN1=src/main.c
BIN1=prog
RSRC=resource/app_menu.ui resource/avl_app.gresource.xml resource/avl_text_box.ui resource/avl_win.ui

#Tools
RM=rm -vf


all: $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(MAIN1) $(SRC) -o $(BIN1) $(LIBS)

src/resources.c: $(RSRC)
	glib-compile-resources resource/avl_app.gresource.xml --target=$@ --generate-source

clean:
	$(RM) *~ */*~

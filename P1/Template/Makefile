CC=gcc
CFLAGS=-g

SRCDIR=src
INCLDIR=include
LIBDIR=lib

mapreduce: $(SRCDIR)/mapreduce.c $(LIBDIR)/utils.o mapper reducer
	$(CC) $(CFLAGS) -I$(INCLDIR) $(LIBDIR)/utils.o $(SRCDIR)/mapreduce.c -o mapreduce

mapper: $(SRCDIR)/mapper.c $(LIBDIR)/utils.o
	$(CC) $(CFLAGS) -I$(INCLDIR) $(LIBDIR)/utils.o $(SRCDIR)/mapper.c -o mapper

reducer: $(SRCDIR)/reducer.c $(LIBDIR)/utils.o
	$(CC) $(CFLAGS) -I$(INCLDIR)  $(LIBDIR)/utils.o $(SRCDIR)/reducer.c -o reducer

.PHONY: clean t1

#500KB
t1:
# 	make -i clean
	make
	./mapreduce 5 2 test/T1/F1.txt

clean:
	rm mapreduce mapper reducer
	rm -rf output
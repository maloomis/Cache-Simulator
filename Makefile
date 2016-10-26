# First target is default target, if you just type:  make

FILE=cache-sim.c

default: run

#add the cache-size, data block size, n associative, and whether it's
#a special case of not (direct, fully, or none)
run: cache
	./cache 128 8 1 direct
	./cache 64 8 2 none
	./cache 128 16 1 direct
	./cache 64 8 8 fully

cache: ${FILE}
	gcc -g -O0 -o cache ${FILE} -lm


# 'make' views $v as a make variable and expands $v into the value of v.
# By typing $$, make will reduce it to a single '$' and pass it to the shell.
# The shell will view $dir as a shell variable and expand it.
dist:
	dir=`basename $$PWD`; cd ..; tar cvf $$dir.tar ./$$dir; gzip $$dir.tar
	dir=`basename $$PWD`; ls -l ../$$dir.tar.gz
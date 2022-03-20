file = voidscript
cc = clang++
bindir = /usr/bin/

all:
	${cc} ${file}.cpp -o ${file}

clean:
	rm -f ${file}

install:
	cp ${file} ${bindir}
file = voidscript
cc = clang++

all:
	${cc} ${file}.cpp -o ${file}

clean:
	rm -f ${file}
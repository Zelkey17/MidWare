

all:
	as as.asm -o ob.obj
	ld ob.obj -e main -o Run
	./Run

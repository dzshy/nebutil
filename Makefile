src =$(shell ls src/*.c)
obj = $(src:.c=.o)

tests=$(shell ls tests/*.c)
tests_bin=$(tests:.c=.elf)

all: libnebutil.a
	-rm -rf build/
	-@mkdir -p build/include/nebutil/
	-@mkdir -p build/lib
	mv libnebutil.a build/lib/
	cp src/*.h build/include/nebutil

libnebutil.a: $(obj)
	ar cr $@ $^

test: $(tests_bin)
	@echo
	@echo "Run tests:"
	@./runall.sh $^

$(obj):%.o:%.c
	gcc -c -g $< -o $@

$(tests_bin):%.elf:%.c libnebutil.a
	gcc -g -Isrc/ $^ -o $@

clean:
	-rm tests/*.elf src/*.o ./*.a
	-rm -rf build


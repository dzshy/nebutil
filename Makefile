src =$(shell ls ./*.c)
obj = $(src:.c=.o)

tests=$(shell ls tests/*.c)
tests_bin=$(tests:.c=.elf)

all: libcdatastruct.a
	-rm -rf build/
	-@mkdir -p build
	-@mkdir -p build/include/
	-@mkdir -p build/lib
	mv libcdatastruct.a build/lib/
	cp *.h build/include/

libcdatastruct.a: $(obj)
	ar cr $@ $^

test: $(tests_bin)
	@echo
	@echo "Run tests:"
	@./runall.sh $^

$(obj):%.o:%.c
	gcc -c -g $< -o $@

$(tests_bin):%.elf:%.c libcdatastruct.a
	gcc -g -I./ $^ -o $@

clean:
	-rm *.elf *.o
	-rm -rf build


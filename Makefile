src =$(shell ls src/*.c)
obj = $(src:.c=.o)

tests=$(shell ls tests/*.c)
tests_bin=$(tests:.c=.bin)

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
	@scripts/runall.sh $^

$(obj):%.o:%.c
	cc -c -g $< -MD -MF $@.d -o $@

$(tests_bin):%.bin:%.c libnebutil.a
	cc -g -Isrc/ $< libnebutil.a -MD -MF $@.d -o $@

clean:
	-rm tests/*.bin src/*.o ./*.a
	-rm -rf build

DEPS := $(shell find . -name *.d)
ifneq ($(DEPS),)
include $(DEPS)
endif

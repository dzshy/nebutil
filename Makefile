tests: test_rbtree \
       test_pque \
       test_crc32
	@echo
	@echo "Run tests:"
	@./test_rbtree && \
	./test_pque && \
	./test_crc32

test_rbtree: rbtree.c rbtree.h tests/test_rbtree.c
	gcc -g -I./ tests/test_rbtree.c rbtree.c -o test_rbtree

test_pque: pque.c pque.h tests/test_pque.c
	gcc -g -I./ tests/test_pque.c pque.c -o test_pque

test_crc32: crc32.c crc32.h tests/test_crc32.c
	gcc -g -I./ tests/test_crc32.c crc32.c -o test_crc32

clean:
	-rm test_*

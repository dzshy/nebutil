tests: test_rbtree test_pque
	@echo
	@echo "Run tests:"
	@./test_rbtree && \
	./test_pque

test_rbtree: rbtree.c rbtree.h tests/test_rbtree.c
	gcc -g -I./ tests/test_rbtree.c rbtree.c -o test_rbtree

test_pque: pque.c pque.h tests/test_pque.c
	gcc -g -I./ tests/test_pque.c pque.c -o test_pque

clean:
	-rm test_*

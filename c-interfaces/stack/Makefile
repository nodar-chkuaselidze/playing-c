
AINT_FILES=stack_aint.h stack_aint.c
ARRINT_FILES=stack_arrint.h stack_arrint.c
HRTIME=hrtime.h hrtime.c
CFLAGS:=$(CFLAGS)

.PHONE: clean run_arrint_test run_aint_test run_arrint_bench run_aint_bench

run_arrint_test: arrint_test
	./arrint_test

run_aint_test: aint_test
	./aint_test

run_aint_bench: aint_bench
	./aint_bench

run_arrint_bench: arrint_bench
	./arrint_bench

clean:
	- rm arrint_test arrint_bench aint_test aint_bench

arrint_test:
	$(CC) $(CFLAGS) $(ARRINT_FILES) stack_arrint_test.c -o arrint_test

aint_test:
	$(CC) $(CFLAGS) $(AINT_FILES) stack_aint_test.c -o aint_test

aint_bench:
	$(CC) $(CFLAGS) $(AINT_FILES) $(HRTIME) stack_aint_bench.c -o aint_bench

arrint_bench:
	$(CC) $(CFLAGS) $(ARRINT_FILES) $(HRTIME) stack_arrint_bench.c -o arrint_bench

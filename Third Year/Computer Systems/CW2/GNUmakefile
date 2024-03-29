# Default optimization level
O ?= -O2

TESTS = $(patsubst %.c,%,$(sort $(wildcard test[0-9][0-9][0-9].c)))

RUN_OPTIONS = ASAN_OPTIONS=allocator_may_return_null=1

all: $(TESTS) hhtest

-include build/rules.mk
LIBS = -lm

%.o: %.c $(BUILDSTAMP)
	$(call run,$(CC) $(CPPFLAGS) $(CFLAGS) $(O) $(DEPCFLAGS) -o $@ -c,COMPILE,$<)

all:
	@echo "*** Run 'make check' or 'make check-all' to check your work."

test%: test%.o cs0019.o basealloc.o
	$(call run,$(CC) $(CFLAGS) $(O) -o $@ $^ $(LDFLAGS) $(LIBS),LINK $@)

hhtest: hhtest.o cs0019.o basealloc.o
	$(call run,$(CC) $(CFLAGS) $(O) -o $@ $^ $(LDFLAGS) $(LIBS),LINK $@)

check: $(patsubst %,run-%,$(TESTS))
	@echo "*** All tests succeeded!"

check-all: $(TESTS)
	@good=true; for i in $(TESTS); do $(MAKE) --no-print-directory run-$$i || good=false; done; \
	if $$good; then echo "*** All tests succeeded!"; fi; $$good

check-%:
	@any=false; good=true; j=`echo "$*" | sed s/^test//`; \
	for i in $(TESTS); do if expr "$$i" : "test0*$$j$$" >/dev/null; then \
	    any=true; $(MAKE) run-$$i || good=false; fi; done; \
	if $$any; then $$good; else echo "*** No such test" 1>&2; $$any; fi

run-:
	@echo "*** No such test" 1>&2; exit 1

run-%: %
	@test -d out || mkdir out
	@-$(RUN_OPTIONS) sh -c "./$^ > out/$<.output 2>&1" >/dev/null 2>&1; true
	@perl check.pl out/$<.output $<.c $<

clean: clean-main
clean-main:
	$(call run,rm -f $(TESTS) hhtest *.o core *.core,CLEAN)
	$(call run,rm -rf out *.dSYM $(DEPSDIR))

distclean: clean

MALLOC_CHECK_=0
export MALLOC_CHECK_

.PRECIOUS: %.o
.PHONY: all clean clean-main check check-all check-% run- run-%

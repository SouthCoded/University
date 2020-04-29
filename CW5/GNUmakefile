# Default optimization level
O ?= 2

all: sh0019

-include build/rules.mk

%.o: %.c sh0019.h $(BUILDSTAMP)
	$(call run,$(CC) $(CPPFLAGS) $(CFLAGS) $(O) $(DEPCFLAGS) -o $@ -c,COMPILE,$<)

sh0019: sh0019.o helpers.o
	$(call run,$(CC) $(CFLAGS) $(O) -o $@ $^ $(LDFLAGS) $(LIBS),LINK $@)

sleep61: sleep61.c
	$(call run,$(CC) $(CFLAGS) $(O) -o $@ $^ $(LDFLAGS) $(LIBS),BUILD $@)

check: sh0019
	perl check.pl

check-%: sh0019
	perl check.pl $(subst check-,,$@)

clean: clean-main
clean-main:
	$(call run,rm -rf sh0019 *.o *~ *.bak core *.core,CLEAN)
	$(call run,rm -rf $(DEPSDIR) out *.dSYM)

realclean: clean
	@echo + realclean
	$(V)rm -rf $(DISTDIR) $(DISTDIR).tar.gz

.PRECIOUS: %.o
.PHONY: all clean clean-main check check-%

HEADERS = vest_defs.h vest_spec.h vest_common.h vest.h
all: dist
dist: tmpfile
	-rm -rf dist
	cat $(HEADERS) | grep -v '\#include \"vest' > tmpfile
	mkdir dist
	mv tmpfile dist/vest.h

tmpfile:
	-rm -f tmpfile
	touch tmpfile
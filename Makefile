
CC := gcc
LDFLAGS = $(shell pkgconf --libs libcras)

OBJECTS = src/acpi.o src/client.o src/wcras.o

PREFIX = /usr

acras: $(OBJECTS)
	@echo "CC	$@"
	@$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.c
	@echo "CC	$@"
	@$(CC) -o $@ -c $<

.PHONY: install
install:
	@echo "INSTALL	acras"
	@install -d $(DESTDIR)$(PREFIX)/bin
	@install -m 755 acras $(DESTDIR)$(PREFIX)/bin/
	@echo "INSTALL	acras.service"
	@install -d $(DESTDIR)$(PREFIX)/lib/systemd/system
	@install -m 644 etc/acras.service $(DESTDIR)$(PREFIX)/lib/systemd/system/
	@echo "INSTALL	README"
	@install -d $(DESTDIR)$(PREFIX)/share/doc/acras
	@install -m 644 README $(DESTDIR)$(PREFIX)/share/doc/acras/
	@echo "INSTALL	LICENSE"
	@install -m 644 LICENSE $(DESTDIR)$(PREFIX)/share/doc/acras/

.PHONY: uninstall
uninstall:
	@echo "UNINSTALL	acras"
	@rm $(DESTDIR)$(PREFIX)/bin/acras
	@echo "UNINSTALL	acras.service"
	@rm $(DESTDIR)$(PREFIX)/lib/systemd/system/acras.service
	@echo "UNINSTALL	README"
	@echo "UNINSTALL	LICENSE"
	@rm -rf $(DESTDIR)$(PREFIX)/share/doc/acras

.PHONY: clean
clean:
	@echo "CLEAN $(OBJECTS) acras"
	@rm -f $(OBJECTS) acras

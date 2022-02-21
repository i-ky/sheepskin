CFLAGS:=-fPIC -I$(ZABBIX_SOURCE)/include $(CFLAGS)
OBJECTS:=$(patsubst %.c,%.o,$(wildcard src/*.c))

.PHONY: all clean sheepskin-cgo.so

all: sheepskin.so sheepskin-cgo.so

sheepskin.so: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) -ldl -shared -o $@

sheepskin-cgo.so:
	CGO_CFLAGS="-I$(ZABBIX_SOURCE)/include $(CFLAGS) -Wno-unused-parameter -Wno-sign-compare" go build -o $@ -buildmode c-shared

clean:
	rm -rf $(OBJECTS) sheepskin.so sheepskin-cgo.*

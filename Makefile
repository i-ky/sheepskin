CFLAGS:=-fPIC -I$(ZABBIX_SOURCE)/include $(CFLAGS)
OBJECTS:=$(patsubst %.c,%.o,$(wildcard src/*.c))

.PHONY: all clean

all: sheepskin.so

sheepskin.so: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) `curl-config --libs` -shared -o $@

clean:
	rm -rf $(OBJECTS) sheepskin.so

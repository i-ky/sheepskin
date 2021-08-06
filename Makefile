CFLAGS:=-fPIC -I$(ZABBIX_SOURCE)/include $(CFLAGS)
OBJECTS:=$(patsubst %.c,%.o,$(wildcard src/*.c))

sheepskin.so: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) `curl-config --libs` -shared -o $@

all: sheepskin.so

clean:
	rm -rf $(OBJECTS) sheepskin.so

led: gpio_led.c 
	gcc gpio_led.c -o gpio_led.o

all: gpio_led

clean:
	rm -rf *.o

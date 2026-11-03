CFLAGS = -Wall -g -pthread

sync_car: sync_car-runner.o sync_car.o
	gcc $(CFLAGS) -o sync_car $^

%.o: %.c sync_car.h
	gcc $(CFLAGS) -c $<

run: sync_car
	./sync_car

clean:
	rm -f *.o sync_car

.PHONY: run clean
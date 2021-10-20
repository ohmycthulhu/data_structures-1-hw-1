objects = normal binomial chi student f_distribution
all: $(objects)

test_objects = distribution_test math_test
tests: $(test_objects)

CC = gcc
CFLAGS = -lm
IDIRS = -Ilib

obj/%.o : %.c
	$(CC) -c $(CFLAGS) $(IDIRS) $< -o $@

obj/%.o : tests/%.c
	$(CC) -c $(CFLAGS) $(IDIRS) $< -o $@

normal: obj/normal.o
	$(CC) $(IDIRS) $^ -o bin/$@ $(CFLAGS)

binomial: obj/binomial.o
	$(CC) $(IDIRS) $^ -o bin/$@ $(CFLAGS)

chi: obj/chi.o
	$(CC) $(IDIRS) $^ -o bin/$@ $(CFLAGS)

student: obj/student.o
	$(CC) $(IDIRS) $^ -o bin/$@ $(CFLAGS)

f_distribution: obj/f_distribution.o
	$(CC) $(IDIRS) $^ -o bin/$@ $(CFLAGS)

distribution_test: obj/distribution_test.o
	$(CC) $(IDIRS) -Itests $^ -o bin/$@ $(CFLAGS)

math_test: obj/math_test.o
	$(CC) $(IDIRS) -Itests $^ -o bin/$@ $(CFLAGS)

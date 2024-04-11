CC=gcc
CFLAGS=-Wall -Werror -Wextra -g -std=c11 -c
OPTIONALFLAGS=-lm
BUILDFOLDER=../build/
OBJSFORTEST=$(addprefix $(BUILDFOLDER),user_string.o parsing.o stack.o input.o postfix_calc.o test.o)
OBJS=$(addprefix $(BUILDFOLDER),user_string.o parsing.o stack.o input.o postfix_calc.o graph.o)

.PHONY: clean

all: build clean_objs

build: graph.o user_string.o stack.o parsing.o input.o postfix_calc.o
	$(CC) $(OBJS) -o $(BUILDFOLDER)graph $(OPTIONALFLAGS)

test_parsing: test.o user_string.o stack.o parsing.o input.o postfix_calc.o
	$(CC) $(OBJSFORTEST) -o $(BUILDFOLDER)test_parsing $(OPTIONALFLAGS)

test.o: test.c parsing.h user_string.h input.h
	$(CC) $(CFLAGS) $< -o $(BUILDFOLDER)$@

graph.o: graph.c graph.h input.h parsing.h postfix_calc.h
	$(CC) $(CFLAGS) $< -o $(BUILDFOLDER)$@

user_string.o: user_string.c user_string.h
	$(CC) $(CFLAGS) $< -o $(BUILDFOLDER)$@

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) $< -o $(BUILDFOLDER)$@

parsing.o: parsing.c parsing.h stack.h
	$(CC) $(CFLAGS) $< -o $(BUILDFOLDER)$@

input.o: input.c input.h
	$(CC) $(CFLAGS) $< -o $(BUILDFOLDER)$@

postfix_calc.o: postfix_calc.c postfix_calc.h parsing.h
	$(CC) $(CFLAGS) $< -o $(BUILDFOLDER)$@

clean:
	rm -rf $(OBJS) $(OBJSFORTEST) $(BUILDFOLDER)test_* $(BUILDFOLDER)graph

clean_objs:
	rm -rf $(OBJS)

clean_testing_objs:
	rm -rf $(OBJSFORTEST)

rebuild: clean all
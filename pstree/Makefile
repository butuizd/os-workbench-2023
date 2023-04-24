NAME := $(shell basename $(PWD))
export MODULE := M1
all: $(NAME)-64 $(NAME)-32

include ../Makefile

test: all
	./$(NAME)-64 -np
	./$(NAME)-64 -V
	./$(NAME)-64 -z
	./$(NAME)-64 --show-pids
	./$(NAME)-64 --numeric-sort
	./$(NAME)-64 --version
	./$(NAME)-64 --falsearg
	./$(NAME)-32 -np
	./$(NAME)-32 -V
	./$(NAME)-32 -z
	./$(NAME)-32 --show-pids
	./$(NAME)-32 --numeric-sort
	./$(NAME)-32 --version
	./$(NAME)-32 --falsearg

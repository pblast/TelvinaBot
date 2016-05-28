
# SALIDA
TARGET=TVBot

# DIRECTORIOS
SRCDIR=src
INCDIR=inc
OBJDIR=obj

#ARCHIVOS
SRCS:=$(wildcard $(SRCDIR)/*.c)
OBJS:=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# COMPILACION
CC=gcc
CFLAGS=-Wall
#=-O2 -Wall -Wextra -std=c99
CFLAGS+=-I./$(INCDIR)

# LINKER
LINKER   = gcc
LFLAGS   = -Wall -I. -lm
POSTLFLAGS= -lcurl
$(TARGET):$(OBJS)
	@$(LINKER)  $(LFLAGS) $(OBJS) -o $@ $(POSTLFLAGS)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

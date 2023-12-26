## на данный момент НЕ ОТСЛЕЖИВАЕТ изменение заголовочников \TODO

.PHONY: clean all run

PRJNAME=task

##########

COMPILER=gcc

CFLAGS=-ggdb3 -Wall -pedantic

CINCLUDES=

##########

SRC_PATH=src

OBJ_PATH=obj

BUILD_PATH=build

##########

CFILES=main.c

CSRC=$(addprefix $(SRC_PATH)/,$(CFILES))

COBJS=$(addprefix $(OBJ_PATH)/,$(notdir $(CSRC:.c=.o)))

TARGETS=$(BUILD_PATH)/$(PRJNAME)

##########

all: $(TARGETS)

run: $(TARGETS)
	@./$(TARGETS)


$(BUILD_PATH)/$(PRJNAME):  $(COBJS)
	@if [ ! -d $(BUILD_PATH) ]; then mkdir $(BUILD_PATH); fi
	$(COMPILER)  -o $@ $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@if [ ! -d $(OBJ_PATH) ]; then mkdir $(OBJ_PATH); fi
	$(COMPILER) $(CFLAGS) $(CINCLUDES)  -c $< -o $@

clean:
	@rm -rfv *~ *.out \#*\# 
	@rm -rfv */*~ */*.out */\#*\#
	@rm -rfv $(BUILD_PATH) $(OBJ_PATH)

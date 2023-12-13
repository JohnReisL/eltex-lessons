.PHONY: clean all run

FINAL_FILE_NAME=execute

all:
	gcc my_list.c main.c -o $(FINAL_FILE_NAME)

run: all
	./$(FINAL_FILE_NAME)

clean:
	rm -rfv *~ *.out  $(FINAL_FILE_NAME)

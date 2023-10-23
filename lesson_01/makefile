.PHONY: clean all

filename=file.txt
foldername=folder

hard_name=hard_$(filename)
soft_name=soft_$(filename)

links=$(hard_name) \
	$(soft_name)

all: clean
	touch $(filename)
	@echo "Некоторый текст внутри файла" > $(filename)
	ln $(filename) $(hard_name)
	ln -s $(filename) $(soft_name)

	@echo  "\n\n\nНа данный момент созданы ссылки, и мы можем увидеть их индексные дескрипторы. \n"

	ls -lhi

	@echo "\n"

	@if ! [ -d $(foldername) ]; then\
        mkdir $(foldername);\
	fi
	mv $(soft_name) $(foldername)/$(soft_name)
	mv $(hard_name) $(foldername)/$(hard_name)

	@echo  "\n\nДалее мы наблюдаем содержание папки, в которую были пермещены файлы. \n"

	ls -lhi $(foldername)

	@echo  "\nПри обращении к файлу через жесткую ссылку мы увидем: \n"
	@cat $(foldername)/$(hard_name)

	@echo  "\nПри попытке вывести мягкую ссылку, будет получена ощибка.\n\"Нет такого файла или каталога\" \n"
	# @cat $(foldername)/$(soft_name)



clean:
	@rm -rfv *~
	@rm -fv $(links)
	@rm -rfv $(foldername)

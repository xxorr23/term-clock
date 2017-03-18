all:
	gcc -o term-clock clock.c sigintHandler.c gotoxy.c -I .
install:
	mkdir -p /usr/local/term-clock
	cp term-clock /usr/local/bin
	cp -R ascii /usr/local/term-clock/
uninstall:
	rm -rf /usr/local/term-clock
	rm /usr/local/bin/term-clock

nullshell - a less than minimal shell
=====================================

Purpose:
	I wanted to grant some friends access to my SSH server,
	just letting them create SSH tunnels without further shell
	related functions.

Setup:
	1. compile nullshell.c
	   You need the ubuntu package libreadline5-dev (or just
	   the source of libreadline).

	   # gcc -o nullshell -lreadline nullshell.c

	2. copy the binary as executable to /usr/local/bin
	   # cp nullshell /usr/local/bin

	3. create a user account with nullshell as default shell
	   # useradd -s /usr/local/bin/nullshell LOGINNAME

	4. set the user's password with passwd or use
	   ~/.ssh/authorized_keys to grant him access without
	   password with his personal public SSH key.


Roman Hoog Antink, 28.4.2011

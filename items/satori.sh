#!/usr/bin/env python2
# -*- coding: utf-8 -*-
from pwn import*

context(os = 'linux', arch = 'amd64', log_level = 'debug', terminal = ['tmux', 'new-window'])
def debug(cmd=''):
	cmd += "b main\n"
	gdb.attach(p, cmd)
	pause()

host = ""
port = 0
p = process("./satori")
#p = remote(host, port)

p.send("KomeijiSatori".ljust(0x20,"\x00"))

p.interactive()
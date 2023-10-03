#!/usr/bin/env python2
# -*- coding: utf-8 -*-
from pwn import*

# context(os = 'linux', arch = 'amd64', log_level = 'debug', terminal = ['tmux', 'new-window'])
# def debug(cmd=''):
# 	cmd += "b main\n"
# 	gdb.attach(p, cmd)
# 	pause()

host = "43.156.14.141"
port = 1141
p = process("./pwn")
# p = remote(host, port)

p.recvuntil("?(y/n)\n")
p.sendline("y")
p.recvuntil("?(y/n)\n")
p.sendline("y")

for i in range(100):
	a = int(p.recvuntil(" ")[:-1])
	x = p.recvn(1)
	p.recvuntil(" ")
	b = int(p.recvuntil(" ")[:-1])
	print(a)
	print(b)
	if(x == "+"):
		ans = a+b
	else:
		ans = a-b
	p.sendlineafter("?\n",str(ans).encode())


p.interactive()
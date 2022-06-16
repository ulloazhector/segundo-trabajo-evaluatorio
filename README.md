# Segundo trabajo evaluatorio

---

## 03 - Sincronización
`g++ *.cpp -pthread -o <nombre_ejecutable>`

## 04 - Sockets

Compilar server y client(s) con:
`g++ *.cpp -o <nombre_ejecutable>`

1. Ejecutar **primero** servidor con
`./<nombre_ejecutable> <SERVER_IP> <PORT>`

ejemplo: `./server 192.168.0.0 4000`

2. Luego ejecutar cliente
`./<nombre_ejecutable> <SERVER_IP> <PORT>`

ejemplo: `./client 192.168.0.0 4000`
import socket
import threading
from time import sleep


class P2pChatRoom:
    def __init__(self):
        self.yourIp = socket.gethostbyname(socket.gethostname())
        #print('Your Ip address:', self.yourIp)

    def server(self, port=50005):
        #Ip = input('Enter server IP: ')
        server_address = (self.yourIp, port)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(server_address)
        print('Your Ip address and port:', server_address)
        while True:
            try:
                print('Listening')
                recv_data, addr = self.sock.recvfrom(1024)
                #print(addr, ',data:', recv_data.decode('utf-8'))
                recv_data = recv_data.decode('utf-8')
                if recv_data == 'request':
                    send_data = 'connected successfully / 連線成功!'
                    self.sock.sendto(send_data.encode('utf-8'), addr)
                    print(f'user {addr} connect!')
                    break
                else:
                    print(recv_data)
                    continue
            except:
                pass
        self.users(addr)

    def connect(self):
        user_address = (self.yourIp, 50000)
        print('Your Ip address and port:', user_address)
        server_address = input('Enter server Ip: ')
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(user_address)
        send_data = 'request'
        self.sock.sendto(send_data.encode('utf-8'), (server_address, 50005))
        while True:
            try:
                recv_data, addr = self.sock.recvfrom(1024)
                #print(addr, ',data:', recv_data.decode('utf-8'))
                print(recv_data.decode('utf-8'))
                if recv_data.decode('utf-8') == 'connected successfully / 連線成功!':
                    break
                else:
                    continue
            except:
                pass
        self.users(addr)

    def users(self, addr):
        print("HINT: type ':help' to get helps")

        def help(message):
            if message == ':help':
                print(' [:help]      show help ')
                print(' [:end]       leave the chatroom and close the program')
                print(' [:shutdown]  shutdown the program, leave the chatroom immediately')
            elif message == ':end':
                print('Leaving, connection lost!\nClose in 1 sec...')
                leaving_message = 'SYSTEM: {尚未完成的功能} left!'
                #print(leaving_message[0:6])
                self.sock.sendto(leaving_message.encode('utf-8'), addr)
                self.sock.close()
                sleep(1)
                exit()
            elif message == ':shutdown':
                print('shutdown!')
                self.sock.close()
                exit()
            else:
                self.sock.sendto(message.encode('utf-8'), addr)

        def receive():
            while True:
                try:
                    recv_data, recv_addr = self.sock.recvfrom(1024)
                    if recv_data.decode('utf-8')[0:6] == 'SYSTEM':
                        print('\r' + recv_data.decode('utf-8')+ '\n➤ ', end='')
                    else:
                        print('\r<{},{}>: '.format(recv_addr[0], recv_addr[1]) + recv_data.decode('utf-8') + '\n➤ ', end='')
                except:
                    pass

        def send():
            while True:
                message = input('➤ ')
                if message != '' and message[0] == ':':
                    help(message)
                elif message == '':
                    pass
                else:
                    #print(message)
                    #print(addr)
                    self.sock.sendto(message.encode('utf-8'), addr)

        receive_thread = threading.Thread(target=receive, daemon=True)
        receive_thread.start()
        send_thread = threading.Thread(target=send)
        send_thread.start()


    def start(self):
        mode = input('Host or Join (h/j):')
        if mode == 'H' or mode == 'h':
            self.server()
        elif mode == 'J' or mode == 'j':
            self.connect()
        else:
            return self.start()


if __name__ == '__main__':
    start = P2pChatRoom()
    start.start()
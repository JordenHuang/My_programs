import socket
import threading
from sys import exit
from time import sleep


class P2pChatRoom:
    def __init__(self):
        self.yourIp = socket.gethostbyname(socket.gethostname())
        self.nickname_list = []
        self.nickname = input('Administrator nickname: ')

    def server(self, port=55655):
        self.server_address = (self.yourIp, port)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(self.server_address)
        self.nickname_list.append([self.server_address, self.nickname])
        print('Server Ip address and port:', self.server_address)
        print('Waiting for other users...')

        def receive():
            while True:
                try:
                    data, addr = self.sock.recvfrom(1024)
                    data = data.decode('utf-8')
                    if data.startswith('$Request:'):
                        nickname = data[9:]
                        broadcast(mode='Request', data=None, addr=addr, nickname=nickname)
                    elif data == '$:end':
                        left_user = ''
                        for users in self.nickname_list:
                            if users[0] == addr:
                                left_user = users[1]
                                self.nickname_list.remove(users)
                        broadcast(mode=':end', data=f'SYSTEM: <{left_user}> left!', addr=addr)
                    elif data == '$:users':
                        broadcast(mode=':users', data='$:users', addr=addr)
                    else:
                        print(f'\r{data}\n➤ ', end='')
                        broadcast(mode='broadcast', data=data, addr=addr)
                except:
                    pass

        def broadcast(mode, data, addr=None, nickname=None):
            if mode == 'Request':
                self.nickname_list.append([addr, nickname])
                send_success_data = '$Connected successfully!'
                self.sock.sendto(send_success_data.encode('utf-8'), addr)
                print(f'\r[{addr}, {nickname}] connect! \n➤ ', end='')
                for users in self.nickname_list:
                    if users[0] != self.server_address:
                        self.sock.sendto(f'SYSTEM: <{nickname}> joined!'.encode('utf-8'), users[0])
            elif mode == ':end':
                print(data)
                for users in self.nickname_list:
                    if users[0] != self.server_address:
                        self.sock.sendto(data.encode('utf-8'), users[0])
            elif mode == ':users':
                users_name = []
                for users in self.nickname_list:
                    users_name.append(users[1])
                self.sock.sendto(str(users_name).encode('utf-8'), addr)
            else:
                for users in self.nickname_list:
                    if users[0] != addr and users[0] != self.server_address:
                        self.sock.sendto(data.encode('utf-8'), users[0])

        def admin_send():
            while True:
                message = input('➤ ')
                if message == ':all_users':
                    print(self.nickname_list)
                if message != '' and message[0] == ':':
                    self.admin_help(message)
                elif message == '':
                    pass
                else:
                    message = f'<{self.nickname}>: ' + message
                    for users in self.nickname_list:
                        if users[0] != self.server_address:
                            self.sock.sendto(message.encode('utf-8'), users[0])


        receive_thread = threading.Thread(target=receive)
        admin_send_thread = threading.Thread(target=admin_send)
        receive_thread.daemon = True
        receive_thread.start()
        admin_send_thread.start()

    def admin_help(self, message):
        if message == ':help':
            print(' [:help]      show help ')
            print(' [:$shutdown]       leave the chatroom and close the program')
            print(' [:users]     show all users')
        elif message == ':$shutdown':
            print('Closing server...')
            server_close_message = 'SYSTEM: Server had been closed, your message will not be received'
            for users in self.nickname_list:
                if users[0] != self.server_address:
                    self.sock.sendto(server_close_message.encode('utf-8'), users[0])
            self.sock.close()
            sleep(1)
            exit()
        elif message == ':users':
            for users in self.nickname_list:
                print(f'\r{users[1]}\n', end='')
        else:
            message = f'<{self.nickname}>: ' + message
            for users in self.nickname_list:
                if users[0] != self.server_address:
                    self.sock.sendto(message.encode('utf-8'), users[0])

    def start(self):
        self.server()


if __name__ == '__main__':
    start = P2pChatRoom()
    start.start()
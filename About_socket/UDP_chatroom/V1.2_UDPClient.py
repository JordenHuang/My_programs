import socket
import threading
from time import sleep


class P2pChatRoom:
    def __init__(self):
        self.yourIp = socket.gethostbyname(socket.gethostname())
        self.server_Ip = input('Enter server Ip: ')
        self.port = input('Enter port (Can skip): ')
        self.nickname = input('Nickname: ')
        self.server_address = (self.server_Ip, 55655)

    def client(self):
        print('Your Ip address and port:', (self.yourIp, self.port))
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
#        self.sock.bind((self.yourIp, self.port))
        send_data = f'$Request:{self.nickname}'
        self.sock.sendto(send_data.encode('utf-8'), self.server_address)

        def help(message):
            if message == ':help':
                print(' [:help]      show help ')
                print(' [:end]       leave the chatroom and close the program')
                print(' [:users]     show all users')
            elif message == ':end':
                print('Leaving, connection lost!\nClosing...')
                leaving_message = '$:end'
                self.sock.sendto(leaving_message.encode('utf-8'), self.server_address)
                self.sock.close()
                sleep(1)
                exit()
            elif message == ':users':
                self.sock.sendto('$:users'.encode('utf-8'), self.server_address)
            else:
                message = f'<{self.nickname}>: ' + message
                self.sock.sendto(message.encode('utf-8'), self.server_address)

        def receive():
            while True:
                try:
                    recv_data, recv_addr = self.sock.recvfrom(1024)
                    recv_data = recv_data.decode('utf-8')
                    if recv_data == '$Connected successfully!':
                        print('\r' + recv_data[1:])
                        print("HINT: type ':help' to get helps\n➤ ", end='')
                    else:
                        print('\r' + recv_data + '\n➤ ', end='')
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
                    message = f'<{self.nickname}>: ' + message
                    self.sock.sendto(message.encode('utf-8'), self.server_address)


        receive_thread = threading.Thread(target=receive, daemon=True)
        receive_thread.start()
        send_thread = threading.Thread(target=send)
        send_thread.start()


    def start(self):
        try:
            self.client()
        except EOFError:
            pass


if __name__ == '__main__':
    start = P2pChatRoom()
    start.start()
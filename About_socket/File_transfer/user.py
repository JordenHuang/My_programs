import socket
import os
from time import sleep, time

#   choose mode before connect: to avoid sender have sent but receiver haven't chosen mode
mode = input('Choose mode: send or receive (s/r)? ')

#   set up user and connect to hoster
user_ip = socket.gethostbyname(socket.gethostname())
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind((user_ip, 50000))
hoster_ip = input('Enter hoster IP: ')
print('Connecting to hoster...')
sock.connect((hoster_ip, 55655))
print('Connected successfully!')
#sleep(0.75)


def file_size_convert(file_size):
    #   convert file size to more readable
    if file_size < 1024:
        return str(file_size)+' bytes'
    elif 1024 <= file_size < 1024**2:
        file_size = round(file_size/1024)
        return str(file_size)+' KB'
    elif 1024**2 <= file_size < 1024**3:
        file_size = round(file_size/1024**2)
        return str(file_size)+' MB'
    elif 1024**3 <= file_size < 1024**4:
        file_size = round(file_size/1024**3)
        return str(file_size)+' GB'


def progress_bar(total_file_size: int, received_amount: int):
    #   a progressbar
    if total_file_size <= received_amount:
        received_amount = total_file_size
    print(f'\rProgress |{"▒" * int(received_amount * 50 / total_file_size):<{50}}| {received_amount}/{total_file_size} '
          + 'bytes', end='', flush=True)


def sender():
    def get_file_name():
        #   get file name and check if the file exist
        print('\nHINT:\n"If you are using computer, you can copy the file path and paste it.\nIf you are using phone, \
    then you\'ll have to copy the file to the same directory with this program inside!"\n')
        file_name = input('File name: ')

        #if file_name == 'quit':
        #    sock.close()

        if file_name.startswith('"'):
            file_name = file_name[1:len(file_name)-1]

        if os.path.isfile(file_name):
            file = open(file_name, 'rb')
            get_file_size(file_name, file)
        else:
            print(f'"{file_name}" is NOT found')
            get_file_name()

    def get_file_size(file_name, file):
        #   get file size
        file_size = os.path.getsize(file_name)
        file_size_C = file_size_convert(file_size)

        if '\\' in file_name:
            file_name = file_name[file_name.rindex('\\') + 1:]

        file_name_and_size = file_name + ':' + str(file_size)
        print('file size:', file_size_C)
        sock.send(file_name_and_size.encode('utf-8'))
        double_check(file_name, file, file_size)

    def double_check(file_name, file, file_size):
        #   check if you send the correct file
        check = input(f'Are you sure you want to send "{file_name}" (y/n)? ')
        if check == 'n':
            file.close()
            print("If you want to send again, rerun the program!")
            pass
#            get_file_name()
        elif check == 'y':
            print('Sending file...\n')

            file_data = file.read(1024)
            sended_amount = 0
            #   show send progress
            while file_data:
                sleep(0.0025)
                sock.send(file_data)
                sended_amount += 1024
                progress_bar(int(file_size), sended_amount)
                file_data = file.read(1024)

            sleep(1)
            print('\nDONE!')
            file.close()
            sleep(1)
        else:
            double_check(file_name, file, file_size)

    get_file_name()


def receiver():
    print('Waiting for sender to send...')
    #   receiving file name and size
    file_name_and_size = sock.recv(1024)
    file_name_and_size = file_name_and_size.decode('utf-8')

    #   print file name and size
    file_name = file_name_and_size[0:file_name_and_size.index(':')]
    file_size = file_name_and_size[file_name_and_size.index(':') + 1:]
    print('\nThe incoming file name:', f'\33[31m{file_name}\033[00m')
    print('File size:', file_size_convert(int(file_size)))

    print('Receiving...\n')

    file = ''
    file_data = sock.recv(1024)

    if not file_data:
        print("Sender stopped sending the file!")
    else:
        file = open(file_name, 'wb')

    received_amount = 1024
    while file_data:
        #   show progress of the file
        if received_amount > int(file_size):
            sleep(0.0025)
            file.write(file_data)
            now = int(file_size)
            progress_bar(int(file_size), now)
            break
        received_amount += 1024
        progress_bar(int(file_size), received_amount)

        #   continue receiving
        sleep(0.0025)
        file.write(file_data)
        file_data = sock.recv(1024)
    file.close()
    sleep(0.5)
    print('\n\nDONE!')


def choose_mode(mode):
    #   If user connects to hoster successfully, then you can choose to be sender or receiver
    if mode == 's':
        try:
            sender()
        except:
            print('An error occur, server shutdown!')
        sleep(3)
        sock.close()
    elif mode == 'r':
        try:
            receiver()
        except:
            print('An error occur, connection lost!')
        sleep(3)
        sock.close()
    else:
        mode = input('Choose mode: send or receive (s/r)? ')
        choose_mode(mode)


choose_mode(mode)
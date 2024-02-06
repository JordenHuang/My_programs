import numpy as np
import PIL.Image

import os
from random import choice

import time

def encode_img(img_name_or_path:str, secret_msg:str, final_img_name:str):
    ''' params:
    img_name_or_path: the image's name like 'cat.png' or the image's absolute path\n
    secret_msg: the secret message to add into the image\n
    final_img_name: the name to store the image with secret message
    '''
    
    
    # open the source image
    image = PIL.Image.open(img_name_or_path, 'r')

    # turn it into numpy array
    img_array = np.array(list(image.getdata()))

    if image.mode == "P":  # P means, 8-bit pixels, mapped to any other mode using a color palette
        raise "Not Supported!"

    # count the channels
    channels = 4 if image.mode == 'RGBA' else 3

    width, height = image.size

    # the number of pixles in the image
    pixels = img_array.size // channels

    # add the stop indicator to show where the msg stopped when decoding
    stop_indicator = "$EoM$"

    secret_msg += stop_indicator

    # turn the secret msg into bit string
    byte_msg = ''.join(f"{ord(c):08b}" for c in secret_msg)
    bits_of_byte_msg = len(byte_msg)
    
    
    # generate the random position sequence
    position = ['0', '1']
    random_pos = [choice(position) for _ in range(bits_of_byte_msg)]
    

    # if not enough space, don't add secret msg in the image
    if bits_of_byte_msg > pixels:
        print("Not enough space")

    # else, change the R, G, B 's least significent bit to the secret bit string one by one
    else:
        index = 0
        for i in range(pixels):    
            if index < bits_of_byte_msg:
                if random_pos[index] == '0':
                    img_array[i][0] = int(bin(img_array[i][0])[2:-1] + byte_msg[index], 2)
                elif random_pos[index] == '1':
                    img_array[i][1] = int(bin(img_array[i][1])[2:-1] + byte_msg[index], 2)
                
                img_array[i][2] = int(bin(img_array[i][2])[2:-1] + random_pos[index], 2)
                index += 1
    
    # reshape the numpy array
    img_array = img_array.reshape((height, width, channels))

    # save the encoded image
    result = PIL.Image.fromarray(img_array.astype('uint8'), mode=image.mode)
    result.save(final_img_name)

    print(f"'{final_img_name}' has been created successfully")
    print(f"Path: {os.path.abspath(final_img_name)}")



def decode_img(img_name_or_path:str):
    ''' params:
    img_name_or_path: the image's name like 'cat.png' or the image's absolute path
    '''
    
    
    # open the source image
    image = PIL.Image.open(img_name_or_path, 'r')

    # turn it into numpy array
    img_array = np.array(list(image.getdata()))

    # count the channels
    channels = 4 if image.mode == 'RGBA' else 3

    pixels = img_array.size // channels
    
    secret_bits_postion = [bin(img_array[i][2])[-1] for i in range(pixels) for j in range(0, 1)]
    secret_bits_postion = ''.join(secret_bits_postion)
    
    secret_bits = ''
    
    for i in range(pixels):    
        if bin(img_array[i][2])[-1] == '0':
            secret_bits += bin(img_array[i][0])[-1]
        else:
            secret_bits += bin(img_array[i][1])[-1]
    
    secret_bits = [secret_bits[i:i+8] for i in range(0, len(secret_bits), 8)]
    
    secret_msg = [chr(int(secret_bits[i], 2)) for i in range(len(secret_bits))]
    secret_msg = ''.join(secret_msg)
    
    stop_indicator = '$EoM$'

    if stop_indicator in secret_msg:
        print("The message is: ")
        print(secret_msg[:secret_msg.index(stop_indicator)])
    else:
        print("Secret message NOT found!")



# TODO: create an easy mode function to add message at the end of the img
# TODO: 製作圖片裡藏著另一張圖片的程式
if __name__ == '__main__':
    # secret_msg = input("Enter the secret message: ")
    secret_msg = "Wow! You find the SECRET MESSAGE!\nai'you'bu'cuo',bei'ni'jie'chu'lai'le'\ntranslator: https://translate.google.com/?hl=zh-HK&sl=auto&tl=zh-TW&op=translate"
    source_img_path = 'cat_img.png'
    secret_image = 'a_cat_with_secret.png'
    
    # encode_img(source_img_path, secret_msg, secret_image)
    
    time.sleep(2)
    
    decode_img(secret_image)
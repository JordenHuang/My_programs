import numpy as np
import PIL.Image

# open the source image
image = PIL.Image.open('encoded.png', 'r')
# image_info = image.info

# turn it into numpy array
img_array = np.array(list(image.getdata()))


# count the channels
channels = 4 if image.mode == 'RGBA' else 3

pixels = img_array.size // channels

secret_bits = [bin(img_array[i][j])[-1] for i in range(pixels) for j in range(0, 1)]
secret_bits = ''.join(secret_bits)

secret_bits = [secret_bits[i:i+8] for i in range(0, len(secret_bits), 8)]

secret_msg = [chr(int(secret_bits[i], 2)) for i in range(len(secret_bits))]
secret_msg = ''.join(secret_msg)


stop_indicator = '$EoM$'

if stop_indicator in secret_msg:
    print(secret_msg[:secret_msg.index(stop_indicator)])
else:
    print("No secret message!")
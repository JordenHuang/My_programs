import time

'''print('version 1')
time.sleep(0.5)
for progress in range(1, 101):
    print('\rProgress|{} {}%'.format("▒"*(progress//3), progress), end='', flush=True)
    time.sleep(0.05)

time.sleep(1)
print('\n\nversion 2')
time.sleep(0.5)'''

file_size = 140
one_percent_of_file = 140/100.0

for progress in range(1, 101):
    print(f'\rProgress|{("▒"*(progress//3)):33}|{progress}%', end='', flush=True)
    time.sleep(0.05)

time.sleep(0.25)


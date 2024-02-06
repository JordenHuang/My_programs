import time
import msvcrt
# MyGoal(complete): press space bar to start timer, press again to stop, show the time and time count
lap_num = 0

print("q to quit, else to start timer")
while True:
    keyboard = ord(msvcrt.getch())
    if keyboard == 32:
        print("start!\n")
        starttime = time.time()
        lap_num += 1
        stop = ord(msvcrt.getch())
        if stop != 113:
            laptime = round((time.time()-starttime) , 3)
            print("lap num: " + str(lap_num))
            print("Time: " + str(laptime) + "\n")

    if keyboard == 113:
        quit()

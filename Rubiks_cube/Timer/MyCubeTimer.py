import time
import msvcrt
from pyTwistyScrambler import scrambler222, scrambler333, scrambler444, megaminxScrambler


# MyGoal(accomplish): press space bar to start timer, press again to stop, show the time and time count
# MyGoal2(accomplish): add scramble generator, and select the type of the Rubik's cube then show its scramble


class ScrambleType:
    def __init__(self, type):
        self.type = type

    def show(self):
        if self.type == '2':
            lap_num = 0
            print('2*2\nHit the spacebar to start, or q to leave\n')
            while True:
                current_lap_num = lap_num + 1
                print(f"scramble {current_lap_num}:", scrambler222.get_WCA_scramble())
                keyboard = ord(msvcrt.getch())
                if keyboard != 113:
                    print("start!\n")
                    starttime = time.time()
                    lap_num += 1
                    stop = ord(msvcrt.getch())
                    if stop != 113:
                        laptime = round((time.time() - starttime), 3)
                        print("lap num: " + str(lap_num))
                        print("Time: " + str(laptime) + "\n")
                elif keyboard == 113:
                    print('leave\n')
                    break
        elif self.type == '3':
            lap_num = 0
            print('3*3\nHit the spacebar to start, or q to leave\n')
            while True:
                current_lap_num = lap_num + 1
                print(f"scramble {current_lap_num}:", scrambler333.get_WCA_scramble())
                keyboard = ord(msvcrt.getch())
                if keyboard != 113:
                    print("start!\n")
                    starttime = time.time()
                    lap_num += 1
                    stop = ord(msvcrt.getch())
                    if stop != 113:
                        laptime = round((time.time() - starttime), 3)
                        print("lap num: " + str(lap_num))
                        print("Time: " + str(laptime) + "\n")
                elif keyboard == 113:
                    print('leave\n')
                    break
        elif self.type == '4':
            lap_num = 0
            print('4*4\nHit the spacebar to start, or q to leave\n')
            while True:
                current_lap_num = lap_num + 1
                print(f"scramble {current_lap_num}:", scrambler444.get_WCA_scramble())
                keyboard = ord(msvcrt.getch())
                if keyboard != 113:
                    print("start!\n")
                    starttime = time.time()
                    lap_num += 1
                    stop = ord(msvcrt.getch())
                    if stop != 113:
                        laptime = round((time.time() - starttime), 3)
                        print("lap num: " + str(lap_num))
                        print("Time: " + str(laptime) + "\n")
                elif keyboard == 113:
                    print('leave\n')
                    break
        elif self.type == 'meg':
            lap_num = 0
            print('Megaminx\nHit the spacebar to start, or q to leave\n')
            while True:
                current_lap_num = lap_num + 1
                print(f"scramble {current_lap_num}:", megaminxScrambler.get_WCA_scramble())
                keyboard = ord(msvcrt.getch())
                if keyboard != 113:
                    print("start!\n")
                    starttime = time.time()
                    lap_num += 1
                    stop = ord(msvcrt.getch())
                    if stop != 113:
                        laptime = round((time.time() - starttime), 3)
                        print("lap num: " + str(lap_num))
                        print("Time: " + str(laptime) + "\n")
                elif keyboard == 113:
                    print('leave\n')
                    break
        elif self.type == 'q':
            quit()
        else:
            print('Wrong enter! Enter again')


if __name__ == '__main__':
    while True:
        print('Welcome to Cube Timer!')
        choose = input('Enter 2 for 2*2, 3 for 3*3, 4 for 4*4 and meg for Megaminx, or q for quit: ')
        type = ScrambleType(choose)
        type.show()



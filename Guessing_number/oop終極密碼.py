# Object Oriented Program --> 終極密碼
from random import randint
import os


class OopGuessNumber:
    def set_min_and_max(self):
        min = input('Enter the minimal number: ')
        if len(min) == 0:
            min = 0
        max = input('Enter the maximal number: ')
        if len(max) == 0:
            max = 100
        try:
            if int(min) >= int(max):
                print('Error!! Min and Max can\'t be the same or reversed! Try again')
                return self.set_min_and_max()
            elif int(min) + 1 == int(max):
                print('Error!! There is no range to set the answer! Try again')
                return self.set_min_and_max()
            else:
                self.min = int(min)
                self.max = int(max)
                return self.min and self.max
        except ValueError:
            print('Value Error!! Try again')
            return self.set_min_and_max()

    def set_real_answer(self):
        real_answer = input('Enter the answer you want: ')
        try:
            int(real_answer)
        except ValueError:
            if len(real_answer) == 0:
                random_real_answer = randint(self.min + 1, self.max - 1)
                return random_real_answer
            else:
                print('Value Error!! Please enter again\n')
                return self.set_real_answer()

        return int(real_answer)

    def get_guess(self):
        guess = input(f'Guess a number (between {self.min} - {self.max}): ')
        try:
            int(guess)
            if self.min < int(guess) < self.max:
                pass
            else:
                print('Please enter in the correct range!')
                return self.get_guess()
        except ValueError:
            print('Please enter valid number!')
            return self.get_guess()

        self.guess = int(guess)
        return self.guess

    def play(self):
        self.set_min_and_max()
        answer = self.set_real_answer()
        os.system('cls')
#        print(self.min, self.max, answer)

        while True:
            user_guess = self.get_guess()
            if user_guess > answer:
                self.max = user_guess
                print('PASS!')
            elif user_guess < answer:
                self.min = user_guess
                print('PASS!')
            elif user_guess == answer:
                print('BOOM!!!\n')
                replay = input("Press any button to continue, or 'q' to quit: ")
                if replay == 'q':
                    break
                else:
                    return self.play()


game = OopGuessNumber()
game.play()
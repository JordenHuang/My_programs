# This program convert decimal integer number int roman number


print("This program convert decimal positive integer number into roman number(Range: 1~3999)")

def roman_numbers(num:int, position:int):
    digits = ['', "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"]
    tens_digits = ["", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"]
    hundreds_digits = ["", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"]
    thousands_digits = ["", "M", "MM", "MMM"]

    if position == 1:
        result = digits[num]
    if position == 2:
        result = tens_digits[num]
    if position == 3:
        result = hundreds_digits[num]
    if position == 4:
        result = thousands_digits[num]
        
    return result


def main():
    print("HINT: q to quit the program")
    while True:
        remaining = 0
        counter_position = 0
        result = []
        num = input("Enter an integer number: ")
        
        if num == 'q':
            break
        else:
            num = int(num)
            if num < 1:
                print("Out of range, enter again!")
                continue
            if num > 3999:
                print("Too large for this program to show, enter again!")
                continue


        while num//10 > 0:
            remaining = num%10
            num = num//10
            counter_position += 1
            result.append(roman_numbers(remaining, counter_position))

        else:
            result.append(roman_numbers(num, counter_position+1))
            print("The result is:", ''.join(result[::-1]))
    
main()
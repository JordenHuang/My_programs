from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from webdriver_manager.chrome import ChromeDriverManager
from time import sleep
from random import randint
from msvcrt import getch
from sys import exit

xreading_loggin_page = r'https://xreading.com/login/index.php'

def hidden_password(message:str, mask='*'):
    print(message, end='', flush=True)
    password = b''
    symbol = b''
    count = 0
    while True:
        symbol = getch()
        if symbol == b'\x03':  # Ctrl-C
            raise KeyboardInterrupt
        elif symbol == b'\r':  # Enter
            break
        elif symbol == b'\x1b':  # Esc
            password = b''
            break
        elif symbol == b'\b':
            if count != 0:
                print("\b \b", end='', flush=True)
                password = password[:-1]  # == password[0:len(password)-1]
                count -= 1
        else:
            print(mask, end='', flush=True)
            password += symbol
            count += 1
    print(flush=True)
    return password.decode()
    
def basic_elements():
    account = input("Enter your xreading account: ")
    password = hidden_password("Enter your password: ")
    book_page = input("Enter the book page url: ")
    secure = hidden_password("For security, please enter the secure code: ")
    if secure != account[0:8] and secure != '5eCur3_C0d3':
        print("Incorrect secure code!\nleaving")
        sleep(0.5)
        print("Press any key to continue...")
        getch()
        exit()
    print()
    return account, password, book_page

def goto_xreading(account, password):
    driver.maximize_window()
    driver.get(xreading_loggin_page)

    login_account = driver.find_element(By.NAME, 'username')
    login_password = driver.find_element(By.NAME, 'password')

    login_account.send_keys(account)
    login_password.send_keys(password)
    
    login = driver.find_element(By.CLASS_NAME, 'btn.btn-primary.btn-block.mt-4')
    login.click()
    
    
def goto_book_page(book_page):
    driver.get(book_page)


def wpm(last_word_count:int, current_word_count:int):
    now_word = driver.find_element(By.XPATH, "//div[@class='activeContents']")
    now_word = now_word.get_attribute("sectioncount")
    # print('content: ', now_word)
    
    last_word_count = current_word_count
    try:
        index = now_word.index('/')
    except ValueError:
        index = len(now_word)
    current_word_count = int(now_word[0:index])
    
    wpm = randint(wpm_min, wpm_max)
    # print(wpm, current_word_count)
    time = (current_word_count - last_word_count) / wpm * 60    # 字數/速度 * (分鐘*60=秒)
    print("Pause time: %.1f sec" %time)
    
    return last_word_count, current_word_count, time

def read():
    close_button = ''
    last_word_count, current_word_count = 0, 0
    while True:
        try:
            close_button = driver.find_element(By.CLASS_NAME, "btn.btn-primary.next-slide.pr-4.pl-4.closebuttonshow")
        except:
            close_button = ''
        
        if close_button != '':
            close_button = driver.find_element(By.CLASS_NAME, 'btn.btn-primary.close-book.pr-4.pl-4')
            close_button.click()
            print("Finished reading, close book")
            break
        else:
            last_word_count, current_word_count, time = wpm(last_word_count, current_word_count)
            time = time/5
            last_scroll = 0
            now_scroll = 270
            for i in range(1,5):
                sleep(time)
                driver.execute_script(f"window.scrollTo({last_scroll}, {now_scroll})")
                last_scroll = now_scroll
                now_scroll += 300
            sleep(time)
            next_page_button = driver.find_element(By.CLASS_NAME, 'btn.btn-primary.next-slide.pr-4.pl-4')
            next_page_button.click()
            sleep(3)
            

def main():
    print("AutoXreadingTool\n@Author: JH")
    
    global wpm_max, wpm_min
    wpm_min = 120
    wpm_max = 160
    
    account, password, book_page = basic_elements()
    
    options = Options()
    options.add_argument("--disable-notifications")
    
    global driver
    driver = webdriver.Chrome(ChromeDriverManager().install(), options=options)
    
    goto_xreading(account, password)
    sleep(3)
    
    goto_book_page(book_page)
    sleep(3)
    
    read()

    print("\a")
    sleep(1.5)
    print("\a")
    print("Press any key to continue...")
    getch()



if __name__ == '__main__':
    main()

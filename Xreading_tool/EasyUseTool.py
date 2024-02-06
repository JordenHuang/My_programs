from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from webdriver_manager.chrome import ChromeDriverManager
from time import sleep
from random import randint
from msvcrt import getch
from sys import exit
from os.path import isfile

xreading_loggin_page = r'https://xreading.com/login/index.php'


def read_info():    
    file_exist = isfile("./info.txt")
    
    if file_exist is False:
        print("Please fill in the infomation about the book in the info.txt!!")
        with open(file="info.txt", mode='w') as f:
            f.writelines("Account\n>>\nPassword\n>>\nBook URL\n>>\nMin wpm\n>>\nMax wpm\n>>\nend\n\n\n")
            f.writelines("NOTICE!\n    no space after the '>>'\n\nexample:\n    Account\n    >>123@123.com   ---Correct\n\n    Account\n    >> 123@123.com   ---Incorrect")            
        print("Press any key to continue...")
        getch()
        exit()
    else:
        with open(file="./info.txt", mode='r') as f:
            str = ''
            count = 1
            account = ''
            password = ''
            book_page = ''
            global wpm_min, wpm_max
            while str[0:3] != "end":
                str = f.readline()
                if str[0:2] == ">>":
                    if len(str) == 3:  #include the '\n'
                        print("Please fill in the infomation about the book in the info.txt!!")
                        print("Press any key to continue...")
                        getch()
                        exit()
                    else:
                        if count == 2:    
                            account = str[2:-1]
                        elif count == 4:
                            password = str[2:-1]
                        elif count == 6:
                            book_page = str[2:-1]
                        elif count == 8:
                            wpm_min = int(str[2:-1])
                        elif count == 10:
                            wpm_max = int(str[2:-1])
                count += 1
            print("\nAccount:", account)
            print("Password: secret")
            print("Book URL:", book_page)
            print("Min wpm:", wpm_min)
            print("Max wpm:", wpm_max)

    return account, password, book_page

def goto_xreading(account, password):
    # driver.maximize_window()
    driver.get(xreading_loggin_page)

    login_account = driver.find_element(By.NAME, 'username')
    login_password = driver.find_element(By.NAME, 'password')

    login_account.send_keys(account)
    login_password.send_keys(password)
    sleep(1)
    
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
                now_scroll += 405
            sleep(time)
            next_page_button = driver.find_element(By.CLASS_NAME, 'btn.btn-primary.next-slide.pr-4.pl-4')
            next_page_button.click()
            sleep(3)
            

def main():
    print("AutoXreadingTool\n@Author: JH")
    
    account, password, book_page = read_info()
    
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
    
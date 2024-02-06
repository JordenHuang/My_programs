def CT(e) :
    if len(e) > 0 :
        try :
            int(e)
            print("It's an integer-number")
            return True
        except ValueError :
            pass

        try :
            float(e)
            print("It's a float-number")
            return True
        except ValueError :
            pass
        try :
                complex(e)
                print("It's a complex-number")
                return True
        except ValueError :
                print("It's something else")
                return False
    else :
        print('You enter noting')
        return 0
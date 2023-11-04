# TODO

def get_flaot():
    while True:
        try:
            money = float(input('Change owed: '))
            if money > 0:
                return money * 100
            else:
                print('Invalid input, please enter the correct amount.')
        except ValueError:
            print("Not an integer")

def main():
    n = 0
    owed = get_flaot()
    while owed > 0:
        if owed >= 25:
            owed -= 25
            n += 1
        elif owed >= 10 and owed < 25:
            owed -= 10
            n += 1
        elif owed >= 5 and owed < 10:
            owed -= 5
            n += 1
        else:
            owed -= 1
            n += 1
    print(n)

main()

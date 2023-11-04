# TODO

def get_height():
    while True:
        try:
            height = int(input('Height: '))
            if height > 0 and height <= 8:
                return height
            else:
                print('Please enter the number 1-8')
        except ValueError:
            print('Not an integer')

def main():
    n = get_height()
    for i in range(n):
        print(' ' * (n - i - 1), end = '')
        print('#' * (i + 1))

main()
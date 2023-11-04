n = input("Please enter a string: ").strip().lower()

if 'hello' in n:
    print('$0')

elif n[0] == 'h' and 'hello' not in n:
    print('$20')

else:
    print('$100')
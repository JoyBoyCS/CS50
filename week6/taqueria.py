menu = {
    "Baja Taco": 4.25,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

sum = 0

while True:
    try:
        item = input('Item: ')

        # 把 menu 的键都转成小写来进行比较
        lower_menu = {k.lower(): v for k, v in menu.items()}

        if item.lower() in lower_menu:
            sum += lower_menu[item.lower()]
            print(f'${sum:.2f}')
        else:
            print('您的输入有误请重新输入')
    except EOFError:
        print(f"\n总计: ${sum:.2f}")
        break
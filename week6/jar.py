class Jar:
    def __init__(self, capacity=12):
        if not isinstance(capacity, int) or capacity < 0:
            raise ValueError('请输入0及0以上的正整数')
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return '🍪' * self._size

    def deposit(self, n):
        if not isinstance(n, int) or n < 0:
            raise ValueError('请输入0及0以上的正整数')
        if self._size + n > self._capacity:
            raise ValueError('已达存放上限')
        self._size += n

    def withdraw(self, n):
        if not isinstance(n, int) or n < 0:
            raise ValueError('请输入0及0以上的正整数')
        if self._size - n < 0:
            raise ValueError('盒子里面饼干数量不足,请输入更小的值')
        self._size -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size


def main():
    jar = Jar()
    print(str(jar.capacity))
    print(str(jar))
    jar.deposit(3)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))


if __name__ == "__main__":
    main()
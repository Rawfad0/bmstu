"""
Удаление узла из связанного списка
Дан класс Node для представления узла связанного списка и класс LinkedList
с методами добавления узлов в конец списка (append) и вывода списка (print_list).
Требуется реализовать метод delete_kth_from_end(self, k) класса LinkedList, который удаляет k-й узел с конца списка.
"""


class Node:
    """
    Класс узла связанного списка.
    Хранит данные и ссылку на следующий узел.
    """
    def __init__(self, data):
        self.data = data
        self.next = None


class LinkedList:
    """
    Класс связанного списка.
    """
    def __init__(self):
        self.head = None

    def append(self, data):
        """
        Добавляет новый узел с заданными данными в конец списка.
        """
        new_node = Node(data)  # Создаем новый узел
        if not self.head:  # Если список пуст
            self.head = new_node  # Новый узел становится первым
            return
        current = self.head  # Начинаем с первого узла
        while current.next:  # Идем до последнего узла
            current = current.next
        current.next = new_node  # Добавляем новый узел в конец

    def delete_kth_from_end(self, k):
        """
        Удаляет k-й узел с конца списка.

        Args:
            k: Позиция узла для удаления (считая с конца).
        """
        if self.head is None:
            return
        if k <= 0:
            return
        list_length = 1
        current = self.head
        while current.next:
            current = current.next
            list_length += 1
        if k > list_length:
            return
        if k == list_length:
            self.head = self.head.next
            return

        k = list_length - k
        current = self.head
        while k > 1:
            current = current.next
            k -= 1
        current.next = current.next.next

    def print_list(self):
        """
        Печатает все элементы списка в удобном формате.
        """
        current = self.head
        while current:
            print(current.data, end=" -> ")
            current = current.next
        print("None")


"""
Требования к методу delete_kth_from_end(self, k):
* Метод принимает один аргумент: k — целое число, представляющее позицию узла для удаления (считая с конца списка).
* Метод должен удалить k-й узел с конца списка.
* Метод должен корректно обрабатывать следующие граничные условия:
    * Пустой список (self.head is None).
    * Значение k меньше или равно 0. Список не подвергается изменениям.
    * Значение k больше длины списка. Список не подвергается изменениям.
* Метод не должен возвращать никаких значений.
* Асимптотическая сложность метода должна быть O(n), где n - длина списка. 
    Не используйте дополнительные структуры данных, увеличивающие объем памяти.
"""

# Пример использования
linked_list = LinkedList()
linked_list.append(1)
linked_list.append(2)
linked_list.append(3)
linked_list.append(4)
linked_list.append(5)

# Полученный список:
linked_list.print_list()  # Вывод: 1 -> 2 -> 3 -> 4 -> 5 -> None

linked_list.delete_kth_from_end(2)  # Удаляем 2-ой узел с конца (4)

# Список после удаления 2-го узла с конца:
linked_list.print_list()  # Вывод: 1 -> 2 -> 3 -> 5 -> None

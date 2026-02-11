"""
Система обработки задач
Представьте, что у вас есть система, которая обрабатывает задачи в порядке их поступления (FIFO).
Вам нужно реализовать систему очереди, которая поддерживает следующие операции:

* enqueue(task): Добавить задачу в очередь.
* dequeue(): Удалить задачу из очереди и вернуть сообщение "{task} удалена из очереди".
    Если задач не осталось - вернуть сообщение "Очередь пуста."
* peek(): Вернуть первую задачу в очереди без её удаления.
    Если задач не осталось - вернуть сообщение "Очередь пуста."
* is_empty(): Проверить, пуста ли очередь. Возвращает True или False.

"""


class TaskQueue:
    def __init__(self):
        self._queue = []

    def enqueue(self, task):
        self._queue.insert(0, task)

    def dequeue(self):
        if not self._queue:
            return "Очередь пуста."
        return f"{self._queue.pop()} удалена из очереди."

    def peek(self):
        if not self._queue:
            return "Очередь пуста."
        return self._queue[-1]

    def is_empty(self):
        return not self._queue


# Пример использования
task_queue = TaskQueue()
task_queue.enqueue("Задача 1")
task_queue.enqueue("Задача 2")
print(task_queue.peek())  # Вывод: "Задача 1"
print(task_queue.dequeue())  # Вывод: "Задача 1 удалена из очереди."
print(task_queue.peek())  # Вывод: "Задача 2"
print(task_queue.dequeue())  # Вывод: "Задача 2 удалена из очереди."
print(task_queue.dequeue())  # Вывод: "Очередь пуста."

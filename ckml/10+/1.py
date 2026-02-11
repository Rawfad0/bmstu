"""
История просмотров веб-браузера.
Реализуйте класс BrowserHistory, имитирующий упрощенную модель истории просмотров веб-браузера,
используя принцип стека (LIFO - Last-In, First-Out).
Класс должен обеспечивать функциональность посещения страниц и возврата к предыдущим страницам.

Класс BrowserHistory: Должен содержать следующие методы:
* visit(url): Принимает URL страницы (строка) и добавляет его в историю просмотров.
* back(): Возвращает пользователя к предыдущей странице в истории.
    Удаляет последний добавленный URL из истории.
    Если история пуста или содержит только одну страницу - ничего не происходит.
* show_current(): Возвращает текущий URL (последний посещенный). Если история пуста, возвращает None.
* show_history(): Возвращает список посещенных URL. Если история пуста, возвращает None.

"""


class BrowserHistory:
    def __init__(self):
        self._stack = []

    def visit(self, url):
        self._stack.append(url)

    def back(self):
        if len(self._stack) > 1:
            self._stack.pop()

    def show_current(self):
        if not self._stack:
            return None
        return self._stack[-1]

    def show_history(self):
        if not self._stack:
            return None
        return self._stack


# Пример использования
history = BrowserHistory()
history.visit("https://www.example.com")
history.visit("https://www.google.com")
history.visit("https://www.wikipedia.org")

print(history.show_history())  # Вывод: ['https://www.example.com', 'https://www.google.com', 'https://www.wikipedia.org']
print(history.show_current())  # Вывод: https://www.wikipedia.org

history.back()
print(history.show_history())  # Вывод: ['https://www.example.com', 'https://www.google.com']
print(history.show_current())  # Вывод: https://www.google.com

history.back()
print(history.show_history())  # Вывод: ['https://www.example.com']
print(history.show_current())  # Вывод: https://www.example.com
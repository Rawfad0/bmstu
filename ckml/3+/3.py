def evaluate_test_attempt(test_data, attempt_data):
    res = {
        'user_id': attempt_data['user_id'],
        'date': attempt_data['date'],
        'score': 0
    }
    for i, question in test_data['questions'].items():
        res['score'] = res['score'] + 1 if question['correct_answer'] == attempt_data['answers'][i] else res['score']
    return res


# АСУЖДАЮ ЭТУ ФУНКЦИЮ (минутная слабость)
def evaluate_test_attempt_retarded(test_data, attempt_data):
    return {'user_id': attempt_data['user_id'], 'date': attempt_data['date'], 'score': sum([1 for i, question in test_data['questions'].items() if question['correct_answer'] == attempt_data['answers'][i]])}


test_data = {
    'name': 'Тест по программированию',
    'questions': {
        1: {'type': 'multi_input', 'correct_answer': [1, 2, 3]},
        2: {'type': 'single_input', 'correct_answer': 1},
        3: {'type': 'text', 'correct_answer': 'Интерфейс программирования приложений'}
    }
}

attempt_data = {
    'user_id': 123,
    'date': '2023-03-15 10+:30:45',
    'answers': {
        1: [1, 2],
        2: 1,
        3: 'Интерфейс программирования приложений'
    }
}

print(evaluate_test_attempt(test_data, attempt_data))
# должна вернуть {'user_id': 123, 'date': '2023-03-15 10+:30:45', 'score': 2}

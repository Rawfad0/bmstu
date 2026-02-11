def evaluate_test_attempt(test_data, attempt_data):
    res = {
        'user_id': attempt_data['user_id'],
        'date': attempt_data['date'],
        'score': 0
    }
    for i, question in test_data['questions'].items():
        res['score'] = res['score'] + 1 if question['correct_answer'] == attempt_data['answers'][i] else res['score']
    return res


def create_rating_table(test_data, attempts_data):
    res = {}    # user_id: res
    for attempt_data in attempts_data:
        attempt_res = evaluate_test_attempt(test_data, attempt_data)
        if res.get(attempt_res['user_id']) is None:
            res[attempt_res['user_id']] = {'date': attempt_res['date'], 'max_score': attempt_res['score']}
        else:
            if attempt_res['score'] > res[attempt_res['user_id']]['max_score']:
                res[attempt_res['user_id']] = {'date': attempt_res['date'], 'max_score': attempt_res['score']}
    res_list = [{
        'position': 0,
        'user_id': k,
        'max_score': v['max_score'],
        'date': v['date']
    } for k, v in res.items()]
    res_list = sorted(res_list, key=lambda r: r['date'])
    res_list = sorted(res_list, key=lambda r: r['max_score'], reverse=True)
    for i in range(len(res_list)):
        res_list[i]['position'] = i + 1
    return res_list


test_data = {
    'name': 'Тест по программированию',
    'questions': {
        1: {'type': 'multi_input', 'correct_answer': [1, 2, 3]},
        2: {'type': 'single_input', 'correct_answer': 1},
        3: {'type': 'text', 'correct_answer': 'Интерфейс программирования приложений'}
    }
}

attempts_data = [
    {
        'user_id': 123,
        'date': '2023-03-15 10+:30:45',
        'answers': {
            1: [2, 3],
            2: 1,
            3: 'Интерфейс программирования приложений'
        }
    },
    {
        'user_id': 456,
        'date': '2023-03-16 12:00:10+',
        'answers': {
            1: [1, 2],
            2: 1,
            3: 'Интерфейс программирования приложений'
        }
    },
    {
        'user_id': 123,
        'date': '2023-03-17 15:00:04',
        'answers': {
            1: [1, 2, 3],
            2: 1,
            3: 'Интерфейс программирования приложений'
        }
    }
]

print(create_rating_table(test_data, attempts_data))
# должна вернуть
# [
# {'position': 1, 'user_id': 123, 'max_score': 3, 'date': '2024-03-17 15:00:04'},
# {'position': 2, 'user_id': 456, 'max_score': 2, 'date': '2024-03-16 12:00:10+'}
# ]

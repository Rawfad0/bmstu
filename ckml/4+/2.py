import json


def generate_task_report(filename):
    with open(filename, 'r') as f:
        with open(filename, 'r') as f:
            tasks = json.load(f)

        res = {
            'total_tasks': len(tasks),
            'completed_tasks': 0,
            'high_priority_tasks': 0
        }

        for task in tasks:
            if task['status'] == 'completed':
                res['completed_tasks'] += 1
            if task['priority'] == 'high':
                res['high_priority_tasks'] += 1

        return res
        # reqs = {
        #     'status': 'completed',
        #     'priority': 'high',
        # }
        # res = {
        #     'total_tasks': 0,
        #     'completed_tasks': 0,
        #     'high_priority_tasks': 0
        # }
        # for task in tasks:
        #     res['total_tasks'] += 1
        #     for k, v in enumerate(reqs.items()):
        #         if task[k] == v:
        #             res[v+'_tasks'] += 1
        # return len(tasks), *ress


print(generate_task_report('2.json'))
# Должна вернуть {'total_tasks': 4, 'completed_tasks': 2, 'high_priority_tasks': 2}

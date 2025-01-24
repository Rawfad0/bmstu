import json

filename_in = "/Users/Shared/users.json"
filename_out = "/Users/Shared/users_json.json"
# filename_out = "/Users/Shared/users_json2.json"

with open(filename_in, 'r') as i, open(filename_out, 'w') as o:
    while (line := i.readline()) != "":
        data = json.loads(line)
        user_id = data['user_id']
        # name = [data['last_name'], data['first_name']]
        name = {
            'last_name': data['last_name'],
            'first_name': data['first_name']
        }
        data['name'] = name
        del data['user_id'], data['last_name'], data['first_name']
        o.write(f"({user_id}, '{json.dumps(data)}'),\n")
        # o.write(f"{data}\n")


import requests
import json


def process_user_data():
    result = {"statistics": []}
    users = requests.get(f"https://jsonplaceholder.typicode.com/users/").json()

    for user in users:
        posts = requests.get(f"https://jsonplaceholder.typicode.com/users/{user['id']}/posts").json()
        post_count = len(posts)
        comment_count = 0
        # for post in posts:
        #     comments = requests.get(f"https://jsonplaceholder.typicode.com/posts/{post['id']}/comments").json()
        #     comment_count += len(comments)
        result["statistics"].append({
            "id": user['id'],
            "username": user['username'],
            "email": user['email'],
            "posts": post_count,
            "comments": comment_count
        })
    result_json = json.dumps(result)
    return requests.post(f"https://webhook.site/d68265c0-2f51-4b96-a8dc-531c43259245", result_json)


print(process_user_data())

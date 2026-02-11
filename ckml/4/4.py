import yaml


def create_config(bot_id, bot_token, *commands):
    commands_template = [{
        'description': description,
        'function': function
    } for description, function in commands]
    templates = {
        'bot_id': bot_id,
        'bot_token': bot_token,
        'commands': commands_template
    }
    return yaml.dump(templates, allow_unicode=True)


bot_id = "457"
bot_token = "1249774028390"

# Пример команд
commands = [
    ("Приветствие", "greet_user"),
    ("Получить прогноз погоды", "get_weather")
]

print(create_config(bot_id, bot_token, *commands))

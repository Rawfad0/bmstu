import json
from bs4 import BeautifulSoup
import os

htmls = os.listdir('../htmls')
for html in htmls:
    with open(f'../htmls/{html}', 'r') as f:
        content = f.read()
        if "503 Service Temporarily Unavailable" in content:
            os.remove(f'../htmls/{html}')
            continue

    with open(f'../htmls/{html}', 'r') as f:
        content = f.read()
        soup = BeautifulSoup(content, "lxml")

    # url
    url = html.replace('_', '/', 6)
    if url == "https://www.patee.ru":
        continue
    print(url)

    # title
    title = soup.find('h1').text

    # ingredients
    ingredients = []
    ingredients_n1 = soup.findAll('td', class_='c7')
    ingredients_n2 = soup.findAll('td', class_='c9')
    ingredients_q1 = soup.findAll('td', class_='c8')
    ingredients_q2 = soup.findAll('td', class_='c10')
    ingredients_q1 = ingredients_q1[:len(ingredients_q2)]
    true_length = 2*len(ingredients_q2)
    for i in range(true_length):
        ingr_n = [ingredients_n1, ingredients_n2][i % 2][i // 2]
        td = ingr_n.findAll('td')
        if len(td):
            name = td[1].text
            ingr_q = [ingredients_q1, ingredients_q2][i % 2][i // 2].text
            if ingr_q == "по вкусу":
                quantity = "по вкусу"
                unit = None
            else:
                spl = ingr_q.split()
                quantity, unit = spl[0], ' '.join(spl[1:])
            ingredients.append({
                'name': name,
                'unit': unit,
                'quantity': quantity})

    # steps
    steps = [step.text.strip('\n') for step in soup.findAll('div', class_="body")[1:]]

    # img_url
    img = soup.find('div', class_="ratio-box main-pic")
    if img is None:
        img = soup.find('div', class_="w100 blk main-pic")
    img_url = img.find('img')['src']

    # json
    recipe = {
        'URL': url,
        'Title': title,
        'Ingredients': ingredients,
        'Steps': steps,
        'IMG_URL': img_url,
    }

    html_parts = html.split('_')

    # with open(f'../recipes/{html_parts[4]}_{html_parts[6][4:]}.json', 'w') as f:
    #     json.dump(recipe, f, ensure_ascii=False)

    with open(f'../recipes/{html_parts[4]}_{html_parts[6][4:]}.txt', 'w') as f:
        f.write(f"{url}\n{title}\n{img_url}\n")
        f.write(f"{len(ingredients)}\n")
        for ingredient in ingredients:
            f.write(f"{ingredient['name']};{ingredient['unit']};{ingredient['quantity']}\n")
        f.write(f"{len(steps)}\n")
        for step in steps:
            f.write(f"{step}\n")

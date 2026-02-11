words = input().split()
substring = input().lower()
print(*list(filter(lambda s: substring in s.lower(), words)), sep='\n')

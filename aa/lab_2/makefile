unit : src/main.py tests/unit.py test_reports/
	coverage run --source=src/ -m unittest discover -s tests -p 'unit*'
	coverage report > test_reports/unit.txt

func : src/main.py tests/func.py test_reports/
	coverage run --source=src/ -m tests.func
	coverage report > test_reports/func.txt

test_reports/ :
	mkdir test_reports

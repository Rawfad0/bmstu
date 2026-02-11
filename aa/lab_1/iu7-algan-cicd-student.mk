ready/report.pdf: ready
	cp report/report.pdf ready/report.pdf

ready/stud-unit-test-report-prev.json: ./ready
	cp stud-unit-test-report-prev.json ready/stud-unit-test-report-prev.json

ready/main-cli-debug: ./ready src/micropython.py
	cp ./src/micropython.py ready/main-cli-debug.py

ready:
	mkdir ready

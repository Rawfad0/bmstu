ready/report.pdf: ./ready ./report/report.pdf
	cp ./report/report.pdf ./ready/report.pdf

ready/stud-unit-test-report-prev.json: ready ./stud-unit-test-report-prev.json
	cp ./stud-unit-test-report-prev.json ./ready/

ready/main-cli-debug: ./ready ./src/main.py
	cp ./src/* ./ready
	cp ./ready/main.py ./ready/main-cli-debug.py

ready/app-cli-debug: ./ready ./src
	touch app.exe
	cp ./app.exe ./ready/app-cli-debug

ready:
	mkdir ready

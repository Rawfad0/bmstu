build:
	dotnet build

run:
	dotnet run --project src/UserInterface

brun:
	dotnet build
	dotnet run --project src/UserInterface

test:
	dotnet tests

clean:
	dotnet clean

pdf/ИУ7-65Б-Равашдех-Фадей-РПЗ-БД.pdf: report/report.pdf
    cp $< $@

report: pdf/ИУ7-65Б-Равашдех-Фадей-РПЗ-БД.pdf
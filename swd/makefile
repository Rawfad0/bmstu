build:
	dotnet build

run:
	dotnet run --project src/WebApi/WebApi.csproj
# 	dotnet run --project src/UserInterface

brun:
	dotnet build
	dotnet run --project src/WebApi/WebApi.csproj
# 	dotnet run --project src/UserInterface

adminer:
	php -S localhost:8888

test:
	dotnet tests


.PHONY: research

research:
	dotnet build
	dotnet run --project src/UserInterface --mode Research

clean:
	dotnet clean

pdf/ИУ7-65Б-Равашдех-Фадей-РПЗ-БД.pdf: report/report.pdf
	cp $< $@

report: pdf/ИУ7-65Б-Равашдех-Фадей-РПЗ-БД.pdf

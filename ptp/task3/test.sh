test () {
	./comparator3.sh $1 $2
	echo "$1 $2 -> $?"
}

test tests/file1 tests/file2
test tests/file2 tests/file3
test tests/file3 tests/file4
test tests/file4 tests/file5
test tests/file6 tests/file7
test tests/file6 tests/file8
test tests/file7 tests/file8

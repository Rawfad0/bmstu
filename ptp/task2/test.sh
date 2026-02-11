test () {
	./comparator2.sh $1 $2
	echo "$1 $2 -> $?"
}

test tests/file1 tests/file2
test tests/file3 tests/file4
test tests/file1 tests/file4
test tests/file5 tests/file6
test tests/file7 tests/file8

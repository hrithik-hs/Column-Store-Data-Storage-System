output:
	g++ Column.cpp ColumnRecord.cpp Data.cpp Database.cpp DataEnum.cpp DataInteger.cpp DataFloat.cpp DataString.cpp Row.cpp Table.cpp TableRecord.cpp Query.cpp main.cpp -lstdc++fs
test:
	g++ Column.cpp ColumnRecord.cpp Data.cpp Database.cpp DataEnum.cpp DataInteger.cpp DataFloat.cpp DataString.cpp Row.cpp Table.cpp TableRecord.cpp test.cpp -lstdc++fs
clean:
	rm -r File
	mkdir File
	mkdir File/Sample
	touch File/Sample.db
	touch File/root
	cp -r File_copy/* File/
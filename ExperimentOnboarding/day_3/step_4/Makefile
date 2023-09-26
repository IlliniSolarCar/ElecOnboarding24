files := file1 file2
some_file: $(files)
	echo "Look at this variable: " $(files)
	touch some_file

file1:
	touch file1
file2:
	touch file2

clean:
	rm -f file1 file2 some_file

## experiment with printing variables. notice target name
argo 	:= ...
brizo 	:= ...
calypso := ...

print:
	echo $(argo)
	echo $(brizo)
	echo $(calypso)
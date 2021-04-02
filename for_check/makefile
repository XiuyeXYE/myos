

all_cpp: *.cpp
	for cpp in $^; \
	do \
  		echo $$cpp; \
  	 	g++ $$cpp -o $$cpp.out; \
	done


all_run: *.out
	for exe in $^; \
    do \
		echo ./$$exe; \
		./$$exe; \
	done

a.out: check_template_temporary.cpp
	g++ $<

run: a.out
	./$<



clean:
	rm -rf *.out
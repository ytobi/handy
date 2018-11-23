AllTest: AllTest.o handy_list_test.o handy_queue_test.o handy_stack_test.o handy_hashtbl_test.o handy_string_test.o handy_vector_test.o CuTest.o
	gcc -o AllTest AllTest.o handy_list_test.o handy_queue_test.o handy_stack_test.o handy_hashtbl_test.o handy_string_test.o handy_vector_test.o CuTest.o handy_list.o handy_queue.o handy_stack.o handy_hashtbl.o handy_string.o handy_vector.o

AllTest.o: AllTest.c
	gcc -c AllTest.c

handy_list.o: ../include/handy_list.c
	gcc -c ../include/handy_list.c
handy_queue.o: ../include/handy_queue.c
	gcc -c ../include/handy_queue.c
handy_stack.o: ../include/handy_stack.c
	gcc -c ../include/handy_stack.c
handy_hashtbl.o: ../include/handy_hashtbl.c
	gcc -c ../include/handy_hashtbl.c
handy_string.o: ../include/handy_string.c
	gcc -c ../include/handy_string.c
handy_vector.o: ../include/handy_vector.c
	gcc -c ../include/handy_vector.c

handy_list_test.o: handy_list.o handy_list_test.c
	gcc -c handy_list.o handy_list_test.c
	
handy_queue_test.o: handy_queue.o handy_queue_test.c
	gcc -c handy_queue.o handy_queue_test.c
	
handy_stack_test.o: handy_stack.o handy_stack_test.c
	gcc -c handy_stack.o handy_stack_test.c

handy_hashtbl_test.o: handy_hashtbl.o handy_hashtbl_test.c
	gcc -c handy_hashtbl.o handy_hashtbl_test.c

handy_string_test.o: handy_string.o handy_string_test.c
	gcc -c handy_string.o handy_string_test.c

handy_vector_test.o: handy_vector.o handy_vector_test.c
	gcc -c handy_vector.o handy_vector_test.c
	
CuTest.o: CuTest-1.5/CuTest.c
	gcc -c CuTest-1.5/CuTest.c
	
clean:
	rm *.o

all: sort display_sort

# displays the timings for both sorts for each sample size up to 1,000
sort: sort.cpp
	g++ sort.cpp -Wall -o sort

# displays the sorted list and timings for both sorts 
# for each sample size up to 1,000
display_sort: sort.cpp
	g++ sort.cpp -Wall -D DISPLAY -o display_sort

# displays the timings for both sorts for each sample size up to 10,000
larger_sample:
	g++ sort.cpp -Wall -D LARGER_SAMPLE_SIZE -o larger_sample

# displays the sorted list and timings for both sorts
# for each sample size up to 10,000
larger_display:
	g++ sort.cpp -Wall -D DISPLAY -D LARGER_SAMPLE_SIZE -o larger_display

clean:
	rm -f sort
	rm -f display_sort
	rm -f larger_sample
	rm -f larger_display
	rm -f *.o

*** INTENT RECOGNITION PROGRAM: WEATHER AND FACTS ***

Build (from directory): mkdir build && cmake CMakeLists.txt && make
Run the code with user input: ./weatherIntent
Run the unit testing: ./runTests



This program can take in any user input asking about the weather (in any city in the world, for any date), and will respond with the extracted intent.

Examples of questions it can take:
	- what is the weather tomorrow
	- will it be rainy on the 21 of july
	- will there be a storm in rome on the 19
	- weather newyorkcity june 22
You can also ask it for a random fact!


Notes:
	- It does not understand day numbers with letters in them (eg. 19th, 21st) but it does understand just the numbers (eg. 19, 21)
	- If the city has more than one words, input it with no spaces (eg. san juan -> sanjuan)

It can also effectuate unit testing. The tests are in the file tests/test.cpp

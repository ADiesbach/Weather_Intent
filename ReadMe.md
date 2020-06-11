*** INTENT RECOGNITION PROGRAM: WEATHER AND FACTS ***

Build (from directory): mkdir build && cmake CMakeLists.txt && make
Run: ./weatherIntent



This program can take in a user input asking about the weather (in any city in the world, for any date), and will respond with the extracted intent.

Examples of questions it can take:
	- What is the weather tomorrow?
	- Will it be rainy in lisbon?
	- Will there be a storm in rome on the 19?
You can also ask it for a random fact!


Things it does not currently understand:
	- Numbers with letters to talk about the date eg. 19th, 21st etc (it does work with 19 or 21)
	- Dates outside of the current month
	- Capital cities with two words (eg. New York, San Francisco, etc)

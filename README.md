# Image_to_Char

## What is this?

This simple program in C++ reads an image file and "draws" it using ASCII characters.

## How does it work?

Nothing too fancy, actually. This program is only able to handle PGM file as of now (first version), it agglutinates together a square block of pixels and gets its mean value (gray scale). The size of the square block used can be changed altering the `MAX_WIDTH` variable (more on that in the next section).

Having the mean value of each group of pixels, we map it for 4 different Extended ASCII characters (█, ▓, ▒ or <white_space> ) and write it to a notepad.

## How do I use it?

First, you will need a `.pgm` format of your image, which you can obtain using online conversion tools (just type 'png to pgm on DuckDuckGo' and you should be able to find it). Put the .pgm file in the 'src' folder.

Next, into the `image_to_char.cpp` file (inside `src`), change the 'capivara.pgm' string to the name of your .pgm or file, or, alternatively, keep it to run the example of the capybara, already in the folder, along with its original .png file so you can easily visualize it.

For running the program you will also need a C++ compiler. Compile all .cpp files in `src` folder and run the executable generated.

Once the program finishes running, you should be able to find a 'Text.txt' file in the project directory. Open it (and possibly zoom out using 'ctrl -') to see the "image" generated.

Note that you can also change the "resolution" of the drawing by changing the 'MAX_WIDTH' variable. A greater value generates a better "resolution".

E-mail me, if any doubts: viniciusarielarruda@tutanota.com

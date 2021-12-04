# Ghostless Pacman
An implementation of Pacman (without the ghosts) in C!

The objective of this project is to simulate the famous Pacman game but without Blink, Pinky, Inky, and Clyde. This makes the game fairly lot simple.

## Installation
<span style="color: red;">NOTE: The game currently runs on Windows only.</span>

To build and run the code from source, follow the following steps:
1. Download the source of the game by cloning this repository or by downloading it as ZIP file and extracting it to your preffered directory.
2. Head inside the cloned/extracted folder and run the **"run.bat"** file. The batch file will execute the following commands inside the directory:
```batch
gcc main.c -o main
``` 
3. Run the newly generated "main.exe" file to play the game.

## Gameplay
![General Gameplay](https://i.imgur.com/rb9HFrf.gif)

### Navigation
To control Pac-man, the characters W,S,A and D are used. W is used to make it move UP, S to move DOWN, A to go LEFT and D to move RIGHT. When Pac-man collides with any part blocks or the boundaries, the game ends and the user loses.

### Collecting Food
There will be randomly distributed across the board indicated by ‘\*’. Points will be accumulated as Pac-man will collect the food. (the number of points will be the programmer’s discretion.) Displaying the points will either be during the game or after the player collects all the food and exits the board.

### Blocks
Randomly place blocks across the board. Positions of blocks should be different every time the program is run.

### Board Exit
How will the game end with the user winning? The game will Pacman eats all the food and moves out of the board. There will be a mark on the board on any part of the border to indicate the exit point. Once it steps on the marked exit, the game is done and the player wins.

## Known Bugs
Weirdly enough, F7 moves the character to the left and F10 moves the character to the right. Pressing the right arrow key also pauses the game.

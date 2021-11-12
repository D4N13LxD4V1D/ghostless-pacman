# Ghostless Pacman
An implementation of Pacman (without the ghosts) in C!

## Gameplay
![General Gameplay](https://i.imgur.com/rb9HFrf.gif)

## Requirements
The game only runs on Windows currently.

## Running the Game
To build and run the code from source, follow the following steps:
1. Download the source of the game by cloning this repository or by downloading it as ZIP file and extracting it to your preffered directory.
2. Head inside the cloned/extracted folder and run the **"build.bat"** file. The batch file will execute the following commands inside the directory:
```batch
gcc main.c -o main
``` 
3. Run the newly generated "main.exe" file to play the game.

## Known Bugs
Weirdly enough, F7 moves the character to the left and F10 moves the character to the right. Pressing the right arrow key also pauses the game.

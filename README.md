# Music Player

This C++ program is a console-based music player that uses a circular doubly linked list to manage and play songs. It allows users to create, view, and delete playlists, as well as play songs from playlists or from a list of all songs in the directory. Key features and functionalities include:

## Key Components

1. **Node Class**:
   - Represents each song in the linked list with attributes `data`, `next`, and `previous`.

2. **Circular Doubly Linked List (circular_doubly_LL) Class**:
   - Manages the playlist using nodes. Provides functionalities to append, delete, search, and display nodes, as well as play songs.

## Key Functionalities

1. **Displaying Songs (displayNode)**:
   - Displays all the songs in the playlist.

2. **Playing Songs (playsong)**:
   - Plays a specified song using the `PlaySound` function. Allows users to play, stop, or exit the song.

3. **Searching for a Song (searchNode)**:
   - Searches for a specific song in the playlist by its name.

4. **Appending a Song (appendNode)**:
   - Adds a new song to the playlist.

5. **Deleting a Song (deleteNode)**:
   - Removes a specified song from the playlist.

6. **Loader (loader)**:
   - Displays a loading screen animation.

## Playlist Management

1. **Starting a Playlist (startplaylist)**:
   - Reads songs from a playlist file and appends them to the linked list. Allows users to navigate through songs (play next, previous, or current song).

2. **Creating a Playlist (createplaylist)**:
   - Prompts the user to enter a playlist name and add songs to it. Ensures the playlist name is unique.

3. **Creating a Favourites Playlist (createfavouriteplaylist)**:
   - Allows users to create a "Favourites" playlist by adding songs to a pre-defined `Favourites.txt` file.

4. **Viewing Playlists (viewplaylist)**:
   - Lists all the created playlists and allows the user to open and play a selected playlist.

5. **Deleting a Playlist (deleteplaylist)**:
   - Deletes a specified playlist file from the directory.

6. **Playing All Songs (playallsongs)**:
   - Displays all songs in the directory and allows users to play them sequentially or select a specific song to play.

## User Interaction

1. **Display Menu (displaymenu)**:
   - Provides a menu-driven interface for the user to choose various options like showing songs, creating playlists, viewing playlists, and exiting the program.

2. **Display Date and Time (clk)**:
   - Displays the current date and time at the start of the program.

3. **Main Function (main)**:
   - Initializes the program by displaying the date and time, showing the authors, and then displaying the main menu.

## Dependencies
- Uses various C++ standard libraries (`<bits/stdc++.h>`, `<vector>`, `<cstdlib>`, `<windows.h>`, `<fstream>`, `<dirent.h>`, `<stdio.h>`, `<ctime>`, `<sstream>`, `<conio.h>`, `<unistd.h>`, `<iomanip>`) for file handling, system commands, and date/time functionalities.
- `PlaySound` function from the `windows.h` library is used to play and stop audio files.

This program provides a comprehensive way to manage and play music playlists using a circular doubly linked list, ensuring a user-friendly experience for creating, viewing, and deleting playlists, as well as playing songs.

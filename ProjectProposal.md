# Project Proposal

### Background
We want to build the board game Mancala. In this game:
1. One player starts by picking any pocket containing stones from their own side.
2. The player will remove all the stones from that pocket, and deposit one stone at a time into neighboring pockets going counter-clockwise until the stones run out.
3. If a player encounters their own store, a stone is deposited in it.
4. If there are enough stones to go past the player’s own store, stones are deposited continuing on the other side’s pockets. However, if they encounter the other player’s store, that store is skipped over.
5. If the last stone is deposited in the player’s own store, the player gets another turn.
6. When all six pockets on one side are emptied the game ends. Each player will count the number of stones in their store. The player who has the most stones in their store wins.

![image](https://github.com/zhouhelena/cis1901-mancala/assets/66381768/54db3a9d-9f22-4ce7-8594-c91456502615)

### Technical Framework
Libraries
* Utilization of C++ Standard Libraries for input/output operations, data handling, and other basic functionalities.

If there’s time:
* Graphics Library: SFML (Simple and Fast Multimedia Library) for rendering the game board, stones, and UI elements.
* Audio Library: OpenAL for sound effects and background music.

C++ Features
* Object-Oriented Programming: The game will heavily utilize OOP concepts for structuring the game components like the Board, Player, and Game Rules.
* Standard Template Library: For efficient data handling and manipulation (e.g., vectors for storing stones in pockets).
* Smart Pointers: Managing game objects like players, pockets, or stones (e.g., unique_ptr if there's a clear single owner or shared_ptr if the ownership is shared). Managing game states like a menu state, playing state, end state.
* Templates: Generalize game elements, like a 'Pocket' class to hold different types of elements (Stones, Pebbles, custom objects).
* Console I/O Handling: For user interaction through the terminal.

### Project Structure
Class Hierarchy:
* Game: The main class to control game flow, states, player turns.
* Player: Handles player actions.
* Board: Manages the game board layout and stone distribution.
* Pocket: Represents individual pockets on the board.
* Store: Specialized pocket representing player's store.

### Timeline
* Week 1: Setup and basic structure implementation (Game, Player, Board classes).
* Week 2: Development of console-based user interface and integrate AI player.
* Week 3: Testing, debugging, and refining user interaction.


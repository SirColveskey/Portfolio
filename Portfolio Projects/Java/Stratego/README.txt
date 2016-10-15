STRATEGO README
Project by Benjamin Cooper and Benjamin Clark

Instructions:
	Rules are standard Stratego rules
	9's can move and attack in the same turn (Rule variation specification)
	Lower numbers are stronger
	Spy can only kill the 1 and only on attack
	Ties kill both pieces
	http://www.stratego.com/play/stratego-rules/

Interface:
	The game will start the player directly into piece placement for the Red player
	The Red side is the top, blue the bottom
	A piece type will appear on the mouse to be placed, and cycle through till each
	piece is placed.
	A information box will pop up to indicate the next players turn and the pieces
	will be hid.
	The game is then played turnwise by clicking and dragging (piece being moved will
	be copied onto the mouse.) Turn results (if combat occurs) will appear in the dialog
	box.

File Description:
	The game is an application because it has a main driver function, however it could be
	fairly easily converted to an applet.

Extra Features:
	Counter for pieces still remaining on each side
	Save/Load functionality (Single instance for simplicity unless you manually save the .data file)
	SUPER AWESOME GRAPHICS AND FUNNESS

General Distribution of Work:
	Benjamin Cooper - GUI Elements and Graphics Creation
	Benjamin Clark - Game Logic
	However the game was programmed pair-programming style so there is a lot of overlap


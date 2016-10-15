# Stratego
Java (cop3252) Final Project - Implementing Stratego as a GUI Java Application

This project will have included files:
- Board.png
- Blue[1-9].png
- BlueB.png
- BlueF.png
- BlueS.png
- Red[1-9].png
- RedB.png
- RedF.png
- RedS.png
- BLUE.png
- RED.png


# Classes: 
- Piece
  - Attributes:
    - string Color
    - char/int Rank
    - int Range -- Normally 1, 10 for rank == 9, 0 for rank == Flag and rank == Bomb %%
    - image Piece
    - image Insignia
  - Functions:
    - int Attack(Piece) -- returns -1 for dies, 1 for kills, 0 for draw
- Board
  - Attributes:
    - string Winner = "" -- changed upon a victor
    - Piece[10][10] Squares
    - string Turn -- Red or Blue
    - int[10] RedPieces -- 0 == bomb, 1-9, Stores the number of each piece still in the game
    - int[10] BluePeces
    - jlabel[20] Pools -- For the pieces arrays to print in the "Combatant" Boxes
  - Functions:
    - void SetupMatch() --
    - void Flip() -- Updates the displayed pieces
    - void CheckGameover() -- Makes sure there is a viable move to be made (in Stratego it's gameover if you can't move)
    - void GetMove() -- Gets the players move and checks it for compliance 
    - void Muster() -- Calls all pieces and tallies their ranks, resetting RedPieces and BluePieces
    - void FlagCapture(string Color) -- Color has captured the other teams flag and wins.
    - ***void LoadMatch() --
    - ***void SaveMatch() --
- Driver
  - Attributes:
    - Board board
    - GameMouse mouse
  - Functions:
    - void Menu()
    - void GameLoop()
-GameMouse
  - Attributes:
    - Mouse mouse
    - Piece pieceOnMouse
  - Functions:
    - void SetPiece()
    - void MakeSelection()
    - void ClearSelection()

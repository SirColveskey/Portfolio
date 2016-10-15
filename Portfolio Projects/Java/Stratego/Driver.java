
/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++Benjamin Cooper+++++++++++++++++*/
/*++++++++++++++++++++++++-and-++++++++++++++++++++++*/
/*+++++++++++++++++++Benjamin Clark++++++++++++++++++*/
/*+++++++++++++++++++++-present-+++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*

    -_-/    ,                ,
   (_ /    ||          _    ||          _
  (_ --_  =||= ,._-_  < \, =||=  _-_   / \\  /'\\
    --_ )  ||   ||    /-||  ||  || \\ || || || ||
   _/  ))  ||   ||   (( ||  ||  ||/   || || || ||
  (_-_-    \\,  \\,   \/\\  \\, \\,/  \\_-| \\,/
                                       /  \
                                      '----`

/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++-Summer 2016-++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*Welcome to Stratego! This game consists of three program files:
--Driver.java (this file)
--Piece.java
--Board.java
as well as a small library of image files.
This game has a graphical interface created using java.swing,
and loading various image files from the local directory.
*/

import java.util.Scanner;
import java.util.Arrays;
import java.util.ArrayList;
public class Driver {
	public static void main(String[] args) //This driver main initiates the game.
	{
		Board board = new Board();  //All functions used here are member functions of Board.
		board.Flip();
		board.SetupMatch();
		board.Flip();
		
	}
}

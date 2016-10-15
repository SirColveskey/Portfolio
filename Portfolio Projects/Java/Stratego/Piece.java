import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.io.Serializable;

import javax.imageio.ImageIO;

/*This file creates a class of Pieces which we use to populate the game board.*/

public class Piece implements Cloneable, Serializable{
	public String Color; //Denotes which player controls the piece.
	public int Rank; //Denotes the level of the piece.
	public int Range; //Some pieces can move across the board, others are unable to move.
	transient public BufferedImage piece; 
	transient public BufferedImage insignia;
	public Piece(String ID)
	{
		if(ID == "blank") //blank pieces occupy the empty areas of the board.
		{
			piece = null;
			insignia = null;
			Range = 0;
			Rank = -3;
			Color = "";
			return;
		}
		if(ID == "lake") //lake pieces are identical to blank pieces, except they cannot be moved through.
		{
			piece = null;
			insignia = null;
			Range = 0;
			Rank = -3;
			Color = "lake";
			return;
		}
		String firstChar = ID.substring(0,1);
		//System.out.println(firstChar);
		String lastChar = ID.substring(1,2);
		//System.out.println(lastChar);
		if(firstChar.equals("R"))
		{
			Color = "Red"; //Here we load the castle images for each red piece.
			try {
				piece = ImageIO.read(Piece.class.getResourceAsStream("/resources/RED.png"));
			} catch (IOException ex) {
				System.out.println("Error with file loading.");
				System.out.println("src/resources/RED.png");}
		}
		else if(firstChar.equals("B"))
		{
			Color = "Blue"; //Here we load the castle images for each blue piece.
			try {
				piece = ImageIO.read(Piece.class.getResourceAsStream("/resources/BLUE.png"));
			} catch (IOException ex) {
				System.out.println("Error with file loading.");}
		}
		if(lastChar.equals("S")) //the Spy is identified by a rank of 10 behind the scenes. 
		{
			Rank = 10;
		}
		else if(lastChar.equals("B")) //Bombs are identified by a rank of 0 behind the scenes. 
		{
			Rank = 0;
		}
		else if(lastChar.equals("F")) //the Flag is identified by a rank of -1 behind the scenes. 
		{
			Rank = -1;
		}
		else
		{
			Rank = Integer.parseInt(lastChar);
		}
		try {			//Here we load the specific images for each piece, showing color and rank.
			insignia = ImageIO.read(Piece.class.getResourceAsStream("/resources/"+Color+lastChar+".png"));
		} catch (IOException ex) {
			System.out.println("Error with file loading.");
			System.out.println("/resources/"+Color+lastChar+".png");}
		if(Rank == 9)
			Range = 10;
		else if(Rank == 0 || Rank == -1)
			Range = 0;
		else
			Range = 1;
	}
	
	public void Reimage() /*This function reloads the images for the game. This is important when loading a saved game. */
	{
		String lastChar;
		if(Color.equals("Red")){
			try {
				piece = ImageIO.read(Piece.class.getResourceAsStream("/resources/RED.png"));
			} catch (IOException ex) {
				System.out.println("Error with file loading.");
				System.out.println("/resources/RED.png");}
		}
		if(Color.equals("Blue")){
			try {
				piece = ImageIO.read(Piece.class.getResourceAsStream("/resources/BLUE.png"));
			} catch (IOException ex) {
				System.out.println("Error with file loading.");}}
		if(Rank == -1)
		{
			lastChar = "F";
		}
		else if(Rank == 0)
		{
			lastChar = "B";
		}
		else if(Rank == 10)
		{
			lastChar = "S";
		}
		else if(Rank == -3)
		{
			return;
		}
		else
		{
			lastChar = Rank+"";
		}
		try {
			insignia = ImageIO.read(Piece.class.getResourceAsStream("/resources/"+Color+lastChar+".png"));
		} catch (IOException ex) {
			System.out.println("Error with file loading.");
			System.out.println("/resources/"+Color+lastChar+".png");}
		
		}
	
	public int Attack(Piece other) //This short function handles all of the combat computations.
	{
		if(other.Rank == -1) //if flag attacked
			return 2;
		else if(other.Rank == 0) //if bomb attacked
		{
			if(Rank != 8) //if not a miner (8)
				return -1;
			else
				return 1;
		}
		else if(Rank == 10 && other.Rank == 1) //all other combat is a simple comparison
			return 1;
		else if(Rank < other.Rank)
			return 1;
		else if(Rank > other.Rank)
			return -1;
		else
			return 0;
	}
	
	@Override
	public Piece clone()  //a clone function for loading and moving pieces.
	{
		String color = "R";
		String rank = Rank + "";
		if(Color == "Blue")
			color = "B";
		if(Rank == 10)
			rank = "S";
		if(Rank == 0)
			rank = "B";
		if(Rank == -1)
			rank = "F";
		return new Piece(color+rank);
	}
}

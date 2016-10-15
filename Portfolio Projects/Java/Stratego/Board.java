import java.awt.Graphics;

import java.util.Arrays;
import java.util.ArrayList;
import java.awt.Font;
import java.awt.image.BufferedImage;
import java.awt.Dimension;
import java.awt.event.MouseMotionListener;
import javax.imageio.ImageIO;
import javax.swing.JLabel;
import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JButton;
import javax.swing.Box.Filler;
import java.io.File;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.ObjectInputStream;
import java.io.Serializable;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.awt.Color;
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.lang.Math;

/*This file is where the game takes place. Here we create the GUI, process user input,
and maintain information regarding the game state.*/

public class Board implements MouseListener, MouseMotionListener, Serializable{
	public Piece[][] Squares = new Piece[10][10];  //This is the main game board.
	public String Turn;							   //A string identifying which player's turn it is currently.
	public String Dialogue = "";					//The output string for printing to a JDialogueBox, used in ChangeTurns().
	public int[] RedPieces;
	public int[] BluePieces;
	public int[] Pools = new int[22];				//Used to count number of pieces in Muster().
	transient public JFrame Window;
	transient public GamePanel Canvas;
	public int X1 = -1;								//X1 and Y1 identify an initial click coordinate on Piece[][] Squares.
	public int Y1 = -1;
	public int X2 = -1;								//X2 and Y2 identify an secondary click coordinate on Piece[][] Squares.
	public int Y2 = -1;
	public int posx;								//posx and posy identify the current location of the cursor over Piece[][] Squares.
	public int posy;
	public String State;							//Identifies which stage the game is in. Red/Blue Placement, Red/Blue Turn, and Endgame.
	transient public ArrayList<Piece> activePieces; //Used to place red pieces initially.
	public int index = 0;
	transient public ArrayList<Piece> secondaryPieces; //Used to place blue pieces initially.
	public Piece[] ActiveSave;						//used to save data in activePieces when saving the game.
	public Piece[] SecondarySave;					//used to save data in secondaryPieces when saving the game.

	
	public Board()
	{
		Window = new JFrame("Stratego");
		Canvas = new GamePanel();
		Canvas.setVisible(true);
		Canvas.Save.addActionListener(new ActionListener() { //Create "Save Match" listener
			public void actionPerformed(ActionEvent e) {
				SaveMatch();
			}
		});
		Canvas.Load.addActionListener(new ActionListener() { //Create "Load Match" listener
			public void actionPerformed(ActionEvent e) {
				LoadMatch();
			}
		});
		Canvas.New.addActionListener(new ActionListener() { //Create "New Match" listener
			public void actionPerformed(ActionEvent e) {
				NewMatch();
			}
		});
		Window.add( Canvas );
		Window.setResizable(false);
		Window.pack();
		Window.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		Window.setVisible( true );	
		Turn = "Red";
		Canvas.playArea.addMouseListener(this);			//Create mouse listeners
		Canvas.playArea.addMouseMotionListener(this);
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				Squares[i][j] = new Piece("blank");  //initialize all pieces in Pieces[][] Squares to a blank Piece.
				if((j == 2 && i == 4) || (j == 3 && i == 4) || (j == 2 && i == 5) || (j == 3 && i == 5) 
						|| (j == 6 && i == 4) || (j == 7 && i == 4) || (j == 6 && i == 5) || (j == 7 && i == 5)) 
					Squares[i][j] = new Piece("lake"); //except for these 8 Pieces, which represent lakes.
					
			}
		}	
		Flip(); //Flip redraws the board. Very important!
	}
	
	public void SetupMatch()  /*This is where we set up the game by letting the players place their Pieces on the board. */
	{
		String[] pieces = {  //A list of all Pieces wich each player has.
	            "B","B","B","B","B","B", /*Bombs*/
	            "1","2","3","3",         /*Marshal, General, Colonels*/
	            "4","4","4",             /*Majors*/
	            "5","5","5","5",         /*Captians*/
	            "6","6","6","6",         /*Lieutenants*/
	            "7","7","7","7",         /*Sergant*/
	            "8","8","8","8","8",     /*Miner*/
	            "9","9","9","9","9","9","9","9", /*Scouts*/
	            "S", "F"};               /*Spy, Flag*/
		
		ArrayList<Piece> p1Pieces = new ArrayList<Piece>();  //To hold red pieces.
		ArrayList<Piece> p2Pieces = new ArrayList<Piece>();	 //To hold blue pieces.
		
		for (int i=0; i<40; ++i)  //for all 40 pieces that a player has,
		{ 							//Populate lists of pieces
		 	p1Pieces.add(new Piece("R" + pieces[i])); //create a red version of each
		 	p2Pieces.add(new Piece("B" + pieces[i])); //and a blue version of each!
		}
		secondaryPieces = p2Pieces;  //Set these new lists to their counterparts with global scope.
		activePieces = p1Pieces;
		index = 0;
		State = "Red Placement";  //Let's begin by placing the red player's pieces.
		
	} 
	
	public void Flip()  //Flip redraws the board area for us. It also hides the pieces of the player whose turn it isn't!
	{
		boolean result;
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				result = (Squares[i][j].Color.equals(Turn));  //show only Turn colored pieces.
				if(Turn.equals("reveal"))  //If it is reveal turn (Used at Endgame), display all Pieces.
					result = true;
				Canvas.grid[i][j].NewPiece(Squares[i][j],result);
			}
		}
		Canvas.repaint();  //Does the actual nitty gritty graphics drawing so we can update the board.
	}
	
	public void NewMatch() //Used to restart the game. Note this is almost entirely identical to Board().
	{
		//Window = new JFrame("Stratego");
		Canvas.setVisible(false);
		Canvas = new GamePanel();
		Canvas.setVisible(true);
		Canvas.Save.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				SaveMatch();
			}
		});
		Canvas.Load.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				LoadMatch();
			}
		});
		Canvas.New.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				NewMatch();
			}
		});
		Window.add( Canvas );
		Window.setResizable(false);
		Window.pack();
		Window.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		Window.setVisible( true );	
		Turn = "Red";
		Canvas.playArea.addMouseListener(this);
		Canvas.playArea.addMouseMotionListener(this);
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				Squares[i][j] = new Piece("blank");
				if((j == 2 && i == 4) || (j == 3 && i == 4) || (j == 2 && i == 5) || (j == 3 && i == 5) 
						|| (j == 6 && i == 4) || (j == 7 && i == 4) || (j == 6 && i == 5) || (j == 7 && i == 5))
					Squares[i][j] = new Piece("lake");
					
			}
		}	
		Flip();
		SetupMatch();  //It also calls SetupMatch()!
		Flip();
	}
	
	public void ChangeTurns() /*ChangeTurns() hides the current player's pieces, 
		displays a dialogue which describes what happened the previous turn, and then shows the next
		player's pieces, so they can take their turn. Pretty nifty! */
	{
		if(Dialogue.equals("")) //If no special events happened during the turn
		{
			Dialogue = "The current player has completed their turn. Next player, you're up!";
		}
		JPanel hold = new JPanel();
		
		JDialog turnChange = new JDialog(Window, Dialogue, true);
		turnChange.setLocationRelativeTo(Canvas.playArea);
		JOptionPane.showMessageDialog(turnChange, Dialogue);
		turnChange.getContentPane().add(hold);
		Dialogue = "";
	}
	
	public void CheckGameover() /* In Stratego, there are two special endgame conditions.
								If the player has no moveable pieces left, (Perhaps they only 
								have bombs and their flag left) they forfeit. Also, if they are
								unable to move any of their pieces during a turn (They are all pinned in
								by bombs or the flag) the player forfeits. This function checks for these conditons. */
	{	
		System.out.print("Check Gameover!");
		//check if movable pieces
		if(Turn.equals("reveal"))
			return;
		if(Turn.equals(""))
			return;
		int totalRange = 0;
		for(int i=0; i<10; ++i)
		{
			for(int j=0; j<10; ++j)
			{
				if(Squares[i][j].Color.equals(Turn))
				{
					totalRange += Squares[i][j].Range; //Finds the sum of ranges of remaining pieces of color Turn.
				}
			}
		}
		System.out.print("Total Range: " + totalRange);
		if (totalRange == 0) //If no moveable pieces, print the message and trigger endgame.
		{
			Dialogue = Turn + "player has no moveable pieces! Opponent is victorious!";
			State = "Endgame";
			Canvas.CursorPiece = new Piece("blank");
			Turn = "reveal";
			ChangeTurns();
		}
		
		
		//check if pieces are stuck
		int saveX1 = X1;  //save previous mouse data, so nothing funky happens
		int saveX2 = X2;
		int saveY1 = Y1;
		int saveY2 = Y2;
		for(int i=0; i<10; ++i)
		{
			for(int j=0; j<10; ++j)
			{
				if(Squares[i][j].Color.equals(Turn))
				{
					X1 = j;
					Y1 = i;
					
					X2 = j+1;
					Y2 = i;
					if (X2 >= 0 && X2 <= 9) 
						if (GetMove(true))
						{ /*we pass our move function hypothetical moves and see if they are valid.
							Note that we pass in 'true', which means move won't actually trigger combat or
							otherwise move pieces.*/
							System.out.print("break: " + X1 + " " + Y1 + " " + X2 + " " + Y2);
							X1 = saveX1;
							X2 = saveX2;
							Y1 = saveY1;
							Y2 = saveY2;
							return;
						}
					
					X2 = j-1;
					Y2 = i;
					if (X2 >= 0 && X2 <= 9) 
						if (GetMove(true))
						{
							System.out.print("break: " + X1 + " " + Y1 + " " + X2 + " " + Y2);
							X1 = saveX1;
							X2 = saveX2;
							Y1 = saveY1;
							Y2 = saveY2;
							
							return;
						}
					
					X2 = j;
					Y2 = i+1;
					if (Y2 >= 0 && Y2 <= 9)
						if (GetMove(true)) 
						{
							System.out.print("break: " + X1 + " " + Y1 + " " + X2 + " " + Y2);
							X1 = saveX1;
							X2 = saveX2;
							Y1 = saveY1;
							Y2 = saveY2;
							return;
						}
					
					X2 = j;
					Y2 = i-1;
					if (Y2 >= 0 && Y2 <= 9)
						if (GetMove(true)) 
						{
							System.out.print("break: " + X1 + " " + Y1 + " " + X2 + " " + Y2);
							X1 = saveX1;
							X2 = saveX2;
							Y1 = saveY1;
							Y2 = saveY2;
							return;
						}
				}
			}
		}
		if(!State.equals("Endgame"))   //if the earlier check didn't trigger endgame, print a message
		{
			Dialogue = Turn + " player has trapped all of their pieces! Opponent is victorious!";
			State = "Endgame";  //and end the game.
			Canvas.CursorPiece = new Piece("blank");
			Turn = "reveal";
			ChangeTurns();
		}
	}
	
	public boolean GetMove(boolean testRun)  /*Getmove conducts a series of checks to determine if a move is legal,
												if it is an attack move, and what the outcome of a legal move will be.*/
	{
		if(!Squares[Y1][X1].Color.equals(Turn)) //Only move own color
			return false;
		if(Squares[Y2][X2].Color.equals(Turn)) //Don't move on own color
			return false;
		if(Squares[Y2][X2].Color.equals("lake")) //Lakes!
			return false;
		if((X1 != X2 && Y1 != Y2) || (X1 == X2 && Y1 == Y2)) //Move in a straight line
			return false;
		System.out.println(X1 + " " + X2 + " " + Y1 + " " + Y2);
		if(Squares[Y1][X1].Range < Math.abs((X1 - X2) + (Y1 - Y2))) //Move in piece range
			return false;
		if (Math.abs((X1 - X2) + (Y1 - Y2)) > 1) //if movement > 1
		{
			
			if(X1 != X2) //If the movement is on X axis
			{
				int start=X1, stop=X2;
				if (X1 > X2)
				{
					start = X2;
					stop = X1;
				}
				for (int i=start+1; i<stop-1; i++) //Check intermediate spaces for obstacles 
				{
					if(!Squares[Y1][i].Color.equals("")) /*This is where lakes are important.
															You can cross over open ground, but not lakes!*/
						return false;
				}
			}
			else //If the movement is on Y axis
			{
				int start=Y1, stop=Y2;
				if (Y1 > Y2)
				{
					start = Y2;
					stop = Y1;
				}
				for (int i=start+1; i<stop-1; i++)
				{
					if(!Squares[i][X1].Color.equals(""))
						return false;
				}		
			}
		}
		if (testRun == true) //If the move was hypothetical, we have determined it is a legal move. and will not continue processing the movement.
			return true;
		//move processing:
		int result = -2;
		if(Squares[Y2][X2].Color.equals(""))
		{
			Squares[Y2][X2] = Squares[Y1][X1];
			Squares[Y1][X1] = new Piece("blank");
		}
		else
		{
			result = Squares[Y1][X1].Attack(Squares[Y2][X2]); //find attack results
		}
		if(result == 1)
		{ //Create a dialogue string to display at ChangeTurns()
			String DefRank;
			String AtkRank;
			if(Squares[Y1][X1].Rank == 10) 
				AtkRank = "Spy";
			else if(Squares[Y1][X1].Rank == 0)
				AtkRank = "Bomb";
			else
				AtkRank = Squares[Y1][X1].Rank + "";
			if(Squares[Y2][X2].Rank == 10)
				DefRank = "Spy";
			else if(Squares[Y2][X2].Rank == 0)
				DefRank = "Bomb";
			else
				DefRank = Squares[Y2][X2].Rank + "";
			Dialogue = Squares[Y1][X1].Color + " Has defeated " + Squares[Y2][X2].Color + "'s piece: " + DefRank + " with a " + AtkRank; //for ChangeTurns()
			Squares[Y2][X2] = Squares[Y1][X1];
			Squares[Y1][X1] = new Piece("blank");
		}
		if(result == -1)
		{ //Create a dialogue string to display at ChangeTurns()
			String DefRank;
			String AtkRank;
			if(Squares[Y1][X1].Rank == 10)
				AtkRank = "Spy";
			else if(Squares[Y1][X1].Rank == 0)
				AtkRank = "Bomb";
			else
				AtkRank = Squares[Y1][X1].Rank + "";
			if(Squares[Y2][X2].Rank == 10)
				DefRank = "Spy";
			else if(Squares[Y2][X2].Rank == 0)
				DefRank = "Bomb";
			else
				DefRank = Squares[Y2][X2].Rank + "";
			Dialogue = Squares[Y1][X1].Color + " Has been defeated by " + Squares[Y2][X2].Color + "'s piece: " + DefRank + " with a " + AtkRank;
			Squares[Y1][X1] = new Piece("blank");
		}
		if(result == 0)
		{ //Create a dialogue string to display at ChangeTurns()
			String DefRank;
			String AtkRank;
			if(Squares[Y1][X1].Rank == 10)
				AtkRank = "Spy";
			else if(Squares[Y1][X1].Rank == 0)
				AtkRank = "Bomb";
			else
				AtkRank = Squares[Y1][X1].Rank + "";
			if(Squares[Y2][X2].Rank == 10)
				DefRank = "Spy";
			else if(Squares[Y2][X2].Rank == 0)
				DefRank = "Bomb";
			else
				DefRank = Squares[Y2][X2].Rank + "";
			Dialogue = Squares[Y1][X1].Color + " Has tied " + Squares[Y2][X2].Color + "'s piece: " + DefRank + " with a " + AtkRank + ". Both have been defeated.";
			Squares[Y1][X1] = new Piece("blank");
			Squares[Y2][X2] = new Piece("blank");
		}
		if(result == 2)
		{ //Create a dialogue string to display at ChangeTurns()
			FlagCapture(Turn);
			Muster();
			Flip();
			return true;
		}
		Turn = "";
		Canvas.CursorPiece = new Piece("blank"); //Grab a new piece for the mouse cursor.
		Muster();
		Flip();
		ChangeTurns();
		if(State.equals("Red Turn"))
		{
			Turn = "Blue";
		}
		if(State.equals("Blue Turn"))
		{
			Turn = "Red";
		}
		if(Turn.equals("Blue"))
		{
			State = "Blue Turn";
		}
		else
		{
			State = "Red Turn";
		}
		return true;
	}
	
	public void Muster()  /*Muster() counts all of the pieces on the board, and lets us display the numbers for the players.*/
	{
		for(int i=0; i<22; i++)
		{
			Pools[i] = 0;
		}
		int increment;
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				if(Squares[i][j].Rank == -1)
					continue;
				if(Squares[i][j].Color.equals("Red"))
				{
					increment = 0;
				}
				else if(Squares[i][j].Color.equals("Blue"))
				{
					increment = 11;
				}
				else
					continue;
				Pools[increment + Squares[i][j].Rank] += 1;
			}
		}
		Canvas.UpdatePools(Pools);
	}
	
	public void FlagCapture(String Color)
	{//Create a dialogue string to display at ChangeTurns()
		Dialogue = Color + " has captured their opponent's flag and is victorious! Contratulations!";
		Turn = "reveal";
		State = "Endgame";
		Canvas.CursorPiece = new Piece("blank");
		Squares[Y2][X2] = Squares[Y1][X1];
		Squares[Y1][X1] = new Piece("blank");
		Flip();
		ChangeTurns();
	}
	
	public void LoadMatch() //Loads the serialized data from the save file.
	{	
		try
	      {
	         FileInputStream fileIn = new FileInputStream("StrategoSave.data");
	         ObjectInputStream in = new ObjectInputStream(fileIn);
	         Squares = new Piece[10][10]; //Read these things back from the file.
	         Squares = (Piece[][]) in.readObject();
	         Turn = (String) in.readObject();
	         ActiveSave = (Piece[]) in.readObject();
	         SecondarySave = (Piece[]) in.readObject();
	         State = (String) in.readObject();
	         System.out.println(State);
	         in.close();
	         fileIn.close();
	         activePieces = new ArrayList<Piece>(Arrays.asList(ActiveSave));
	         secondaryPieces = new ArrayList<Piece>(Arrays.asList(SecondarySave));
	         for(int i=0; i<10; i++){
	        	 for(int j=0; j<10; j++){
	        		 Squares[i][j].Reimage(); //Lots of reimaging
	        	 }
	         }
	         for(int i=0; i<activePieces.size(); i++){
	        	 activePieces.get(i).Reimage(); //Lots
	         }
	         for(int i=0; i<secondaryPieces.size(); i++){
	        	 secondaryPieces.get(i).Reimage(); //This was a problem
	        	 System.out.println(secondaryPieces.get(i).Color);
	         }
	          
	      }catch(IOException i) //Watch for exceptions!!
	      {
	    	 System.out.print("IOException");
	         i.printStackTrace();
	         return;
	      }catch(ClassNotFoundException c)
	      {
	         System.out.println("Board class not found");
	         c.printStackTrace();
	         return;
	      }
		Muster(); //Update muster and flip!
		Flip();
		
		
	}
	
	public void SaveMatch() //Save the current game to a file using serialization!
	{
		ActiveSave = new Piece[activePieces.size()];
		SecondarySave = new Piece[secondaryPieces.size()];
		ActiveSave = activePieces.toArray(ActiveSave);
		SecondarySave = secondaryPieces.toArray(SecondarySave);
		try {
			FileOutputStream fileOut = new FileOutputStream("StrategoSave.data"); //save here!
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(Squares); //Write these things to the file
			out.writeObject(Turn);
			out.writeObject(ActiveSave);
			out.writeObject(SecondarySave);
			out.writeObject(State);
			out.close();
			fileOut.close();
			} catch(IOException i) //exceptions to watch
		{
		 System.out.print("IOException");
		}
	}
	
	public void Blank() //Unused, see ChangeTurns()
	{
		//Show blank screen with text "Hit Space to Continue" or something of the like
		//For turn swaps
	}
	
	public void drawPiece(Graphics g){ //used to draw each Piece with it's sprites.
		g.drawImage(activePieces.get(0).insignia,posx,posy,null);
		Flip();
	}
	
	public void PlacePiece() //used to initialize the board.
	{
		if (State.equals("Red Placement"))
		{
			if (Y1 > 3)
				return;
			if (!Squares[Y1][X1].Color.equals(""))
				return;
		}
		if (State.equals("Blue Placement"))
		{
			if (Y1 < 6)
				return;
			if (!Squares[Y1][X1].Color.equals(""))
				return;
		}
		Squares[Y1][X1] = activePieces.get(0);
		activePieces.remove(0);
		if(activePieces.isEmpty())
		{
			String CurrentState = State;
			activePieces = secondaryPieces;
			Turn = "";
			Muster();
			Flip();
			X1 = Y1 = -1;
			if (CurrentState.equals("Red Placement"))
			{
				Canvas.CursorPiece = new Piece("blank");
				Flip();
				ChangeTurns();
				Turn = "Blue";
				State = "Blue Placement";
			}
			if (CurrentState.equals("Blue Placement"))
			{
				Turn = "";
				Canvas.CursorPiece = new Piece("blank");
				Flip();
				ChangeTurns();
				Turn = "Red";
				State = "Red Turn";
				CheckGameover();
			}
		}
		Muster();
		Flip();
	}
	
	
	public void mousePressed(MouseEvent e){ //Mouse action listener. Collects X1, Y1, X2, Y2.
		X1 = e.getX()/75;
		Y1 = e.getY()/75;
		System.out.print(activePieces.size());
		if(State.equals("Red Placement"))
		{
			PlacePiece();
		}
		if(State.equals("Blue Placement"))
		{
			PlacePiece();
		}
		if(State.equals("Red Turn"))
		{
			if(Y1 != -1 && X1 != -1 && Squares[Y1][X1].Color.equals("Red"))
				Canvas.CursorPiece = Squares[Y1][X1];
			else
				Canvas.CursorPiece = new Piece("blank");
				
		}
		if(State.equals("Blue Turn"))
		{
			if(Y1 != -1 && X1 != -1 && Squares[Y1][X1].Color.equals("Blue"))
				Canvas.CursorPiece = Squares[Y1][X1];
			else
				Canvas.CursorPiece = new Piece("blank");
				
		}
		
		//System.out.println("The mouse was clicked down at "+X+" "+Y);
	}
	public void mouseReleased(MouseEvent e){ //Mouse action listener.
		X2 = e.getX()/75;
		Y2 = e.getY()/75;
		
		if(State.equals("Red Turn"))
		{
			CheckGameover();
			GetMove(false);
			CheckGameover();
			Canvas.CursorPiece = new Piece("blank");
		}
		if(State.equals("Blue Turn"))
		{
			CheckGameover();
			GetMove(false);
			CheckGameover();
			Canvas.CursorPiece = new Piece("blank");
		}
		
		//System.out.println("The mouse was clicked up");	
	}
	public void mouseEntered(MouseEvent e){ //Mouse action listener.
		if(State == null)
			return;
		if (State.equals("Red Placement") || State.equals("Blue Placement"))
			Canvas.CursorPiece = activePieces.get(0);
		Flip();
		//System.out.println("The mouse has entered the building");		
	}
	public void mouseExited(MouseEvent e){ //Mouse action listener.
		X1 = Y1 = X2 = Y2 = -1;
		Canvas.CursorPiece = new Piece("blank");
		Flip();
		//System.out.println("The mouse has left the building");
	}
	public void mouseClicked(MouseEvent e){ //Mouse action listener.
		//Doesn't Matter
	}
	public void mouseDragged(MouseEvent e){ //Mouse action listener.
		Canvas.X = e.getX();
		Canvas.Y = e.getY();
		if (State.equals("Red Placement") || State.equals("Blue Placement"))
			Canvas.CursorPiece = activePieces.get(0);
		Flip();
	}
	public void mouseMoved(MouseEvent e){ //Mouse action listener.
		Canvas.X = e.getX();
		Canvas.Y = e.getY();
		if(State == null)
			return;
		if (State.equals("Red Placement") || State.equals("Blue Placement"))
			Canvas.CursorPiece = activePieces.get(0);
		Flip();
	}
	
}

class GamePanel extends JPanel { //Draw the game window and stuff!
	public int[] Selection1 = {-1,-1};
	public int[] Selection2 = {-1,-1};
	public Piece BLANK_PIECE;
	public BufferedImage bgImage;
	public PiecePanel[][] grid = new PiecePanel[10][10];
	public JPanel[] nums = new JPanel[22];
	public JLabel[] lab = new JLabel[22];
	public Box playArea;
	public Piece CursorPiece;
	public int X,Y;
	public JButton Save; //Buttons!
	public JButton Load;
	public JButton New;
	public GamePanel(){
		BLANK_PIECE = new Piece("blank");
		Box[] Base = new Box[3]; //Boxes!
		Box[] Center = new Box[3];
		Box[] Collumn = new Box[11];
		int[] CollumnHs = {215,37,65,37,37,145,37,65,37,37,25}; //Formatting for Muster panel
		int[] CollumnWs = {400,30,400,30,170,400,30,400,30,170,400};
		Box[] Logs = new Box[10];
		try {
			bgImage = ImageIO.read(Board.class.getResourceAsStream("/resources/Board.png")); //Graphics!
		} catch (IOException ex) {
			System.out.println("Error with file loading.");
		}
		for(int i=0; i<22; i++)
		{
			nums[i] = new JPanel();
			nums[i].setOpaque(false);
			lab[i] = new JLabel();
			lab[i].setText("0");
			lab[i].setFont(lab[i].getFont().deriveFont(23.0f));
			lab[i].setForeground(Color.WHITE);
			nums[i].add(lab[i]);
		}
		for(int i=0; i < 10; i++)
		{
			Logs[i] = Box.createHorizontalBox();
			//Logs[i].add(Box.createRigidArea(new Dimension(750,0)));
			for(int j=0; j<10; j++)
			{
				grid[i][j] = new PiecePanel(BLANK_PIECE,false);
				Logs[i].add(grid[i][j]);
			}
		}
		for(int i=0; i < 11; i++)
		{
			Collumn[i] = Box.createHorizontalBox();
			Collumn[i].add(Box.createRigidArea(new Dimension(CollumnWs[i],CollumnHs[i])));
		}
		//Left Collumn Pool Additions 
		Collumn[1].add(nums[0]);
		Collumn[1].add(nums[9]);
		Collumn[1].add(nums[8]);
		Collumn[1].add(nums[7]);
		Collumn[1].add(nums[6]);
		Collumn[3].add(nums[5]);
		Collumn[3].add(nums[4]);
		Collumn[3].add(nums[3]);
		Collumn[3].add(nums[2]);
		Collumn[3].add(nums[1]);
		Collumn[4].add(nums[10]);
		Collumn[6].add(nums[11]);
		Collumn[6].add(nums[20]);
		Collumn[6].add(nums[19]);
		Collumn[6].add(nums[18]);
		Collumn[6].add(nums[17]);
		Collumn[8].add(nums[16]);
		Collumn[8].add(nums[15]);
		Collumn[8].add(nums[14]);
		Collumn[8].add(nums[13]);
		Collumn[8].add(nums[12]);
		Collumn[9].add(nums[21]);
		Collumn[1].add(Box.createRigidArea(new Dimension(15,0)));
		Collumn[3].add(Box.createRigidArea(new Dimension(15,0)));
		Collumn[6].add(Box.createRigidArea(new Dimension(15,0)));
		Collumn[8].add(Box.createRigidArea(new Dimension(15,0)));
		//Center Panel
		Center[0] = Box.createVerticalBox();
		Center[0].add(Box.createRigidArea(new Dimension(405,0)));
		Center[1] = Box.createVerticalBox();
		playArea = Center[1];
		//Center[1].addMouseListener(this);
		//Center[1].add(new JButton("Button Y"));
		Center[1].add(Box.createRigidArea(new Dimension(750,0)));
		//Center[1].add(new JButton("Button Y"));
		Center[2] = Box.createVerticalBox();
		//Center[2].add(new JButton("Button Z"));
		Center[2].add(Box.createRigidArea(new Dimension(45,0)));
		//Center[2].add(new JButton("Button Z"));
		Base[0] = Box.createHorizontalBox();
		Base[0].add(Box.createRigidArea(new Dimension(0,75)));
		Save = new JButton("Save Game");
		Base[0].add(Save);
		Load = new JButton("Load Game");
		Base[0].add(Load);
		Base[1] = Box.createHorizontalBox();
		Base[1].add(Box.createRigidArea(new Dimension(0,750)));
		for(Box x : Collumn)
		{
			//x.setBorder(BorderFactory.createLineBorder(Color.black));
			Center[0].add(x);
		}
		for(Box x : Logs)
		{
			Center[1].add(x);
		}
		for(Box x : Center)
		{
			//x.setBorder(BorderFactory.createLineBorder(Color.black));
			Base[1].add(x);
		}
		Base[2] = Box.createHorizontalBox();
		Base[2].add(Box.createRigidArea(new Dimension(0,75)));
		New = new JButton("New Game");
		Base[2].add(New);
		BoxLayout boxLayout = new BoxLayout(this, BoxLayout.Y_AXIS);
		setLayout(boxLayout);
		for(Box x : Base)
		{
			//x.setBorder(BorderFactory.createLineBorder(Color.black));
			add(x);
		}
	}
	
	public void UpdatePools(int[] Pools) 
	{
		for(int i=0; i<22; i++)
		{
			lab[i].setText(Integer.toString(Pools[i]));
		}
	}
	
	public void paintComponent(Graphics g) //Graphics stuff
	{
		super.paintComponent(g);
		g.drawImage(bgImage, 0, 0, null);
		if(CursorPiece != null){
			if(!CursorPiece.Color.equals("")){
				g.drawImage(CursorPiece.insignia, X + 360, Y + 40, null);
			}}
	}
	
	public Dimension getPreferredSize() //for window
	{
		return new Dimension(1200,900);
	}
}

class PiecePanel extends JPanel{ //Used to contain the bits for a Piece and its images
	public BufferedImage Castle;
	public BufferedImage Rank;
	public boolean YourTurn;
	public PiecePanel(Piece piece, boolean Turn)
	{
		YourTurn = Turn;
		Castle = piece.piece;
		Rank = piece.insignia;
		setOpaque(false);
	}
	
	public void NewPiece(Piece piece, boolean Turn)  //Lets us grab a new piece with image info
	{
		YourTurn = Turn;
		Castle = piece.piece;
		Rank = piece.insignia;
	}
	
	public void paintComponent(Graphics g)  //You know, for painting and stuff.
	{
		super.paintComponent(g);
		if(Castle != null)
			g.drawImage(Castle, 0, 0, null);
		if(YourTurn)
		{
			if(Rank != null)
				g.drawImage(Rank, 0, 0, null);
		}
	}
	
	public Dimension getPreferredSize() 
	{
		return new Dimension(75,75);
	}
}

/*
 * Name: Benjamin Cooper
 * Project: 4 - Java w/ swing
 * Description: This project implements a GUI java program which performs 3 basic functions.
 *    It generates a scene, generates a random array of circles (up to five) and can browse your
 *    file system.
 * Reference: Figure 22.11 by Ditel et. all for setting up the DesktopFrame and basic panel integration.
 */
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.Random;
import javax.swing.JFrame;
import javax.swing.JDesktopPane;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JInternalFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JLabel;
import java.io.File;

public class DesktopFrame extends JFrame //Note: Needs to be renamed to DesktopFrame & Main edited
{
   private JDesktopPane theDesktop;

   // set up GUI
   public DesktopFrame()
   {
      super( "Homework 4" );//Calls super constructor and titles the frame
//sets up the menu system
      JMenuBar bar = new JMenuBar(); // create menu bar
      JMenu createMenu = new JMenu( "Create" ); // add create menu
      JMenu quitMenu = new JMenu( "Quit" ); //add quit menu
      JMenuItem fileList = new JMenuItem( "File Listing" );
      JMenuItem picture = new JMenuItem( "Picture" );
      JMenuItem ranPic = new JMenuItem( "Randomized Picture" );
      JMenuItem quitItem = new JMenuItem( "Quit Program" );
//Arranges the menu system
      createMenu.add( fileList ); // add new frame item to Add menu
      createMenu.add( picture );
      createMenu.add( ranPic );
      quitMenu.add( quitItem );
      bar.add( createMenu ); // add the create menu to menu bar
      bar.add( quitMenu ); //adds the quit menu to the menu bar.
      setJMenuBar( bar ); // set menu bar for this application

      theDesktop = new JDesktopPane(); // create desktop pane
      add( theDesktop ); // add desktop pane to frame
    
      // set up listener for fileList menu item
      fileList.addActionListener(

         new ActionListener() // anonymous inner class
         {  
            // display new internal window
            public void actionPerformed( ActionEvent event ) 
            {
            	 JInternalFrame frame = new JInternalFrame("File List .", true, true, true, true );
				  fileLister panel = new fileLister();//fills the pane with the file lister panel
				  frame.add( panel, BorderLayout.CENTER );
				  frame.pack();
				  
				  theDesktop.add( frame );
				  frame.setVisible( true );
				  panel.textField.addActionListener(
						  new ActionListener()
						  {
							  public void actionPerformed( ActionEvent event )
							  {
								  frame.setTitle("File List " + panel.textField.getText());//changes the frame title
							  }
						  });
			} // end method actionPerformed
         } // end anonymous inner class
      ); // end call to addActionListener
      
      //Listener to quit the program
      quitItem.addActionListener(
    		  
    		  new ActionListener()
    		  {
    			  public void actionPerformed( ActionEvent event )
    			  {
    				  System.exit(0);
    			  }
    		  }
    	  );
      //Listener to call the random circle generation panel
      ranPic.addActionListener(
    		  
    		  new ActionListener()
    		  {
    			  public void actionPerformed( ActionEvent event )
    			  {
    				  JInternalFrame frame = new JInternalFrame("Internal Frame", true, true, true, true );
    				  circlePanel panel = new circlePanel();
    				  frame.add( panel, BorderLayout.CENTER );
    				  frame.pack();
    				  
    				  theDesktop.add( frame );
    				  frame.setVisible( true );
    			  }
    		  }
    		  );
      //Listener to call the scene generation panel
      picture.addActionListener(
    		  
    		  new ActionListener()
    		  {
    			  public void actionPerformed( ActionEvent event )
    			  {
    				  JInternalFrame frame = new JInternalFrame("Internal Frame", true, true, true, true );
    				  scenePanel panel = new scenePanel();
    				  frame.add( panel, BorderLayout.CENTER );
    				  frame.pack();
    				  
    				  theDesktop.add( frame );
    				  frame.setVisible( true );
    			  }
    		  }
    		  );
   } // end constructor DesktopFrame
} // end class DesktopFrame
//Class to display the preset scene
class scenePanel extends JPanel
{
	public scenePanel()
	{

	}

	public void paintComponent( Graphics g )
	{
		super.paintComponent( g );
		super.setBackground(Color.BLUE);//sets bg color as instructed
		Color brown = new Color(165,42,42);//a custom brown color
		g.setColor(brown);
		g.fillRect((int)Math.ceil(0 * this.getSize().width),(int)Math.ceil( .9 * this.getSize().height),(int)Math.ceil( 1 * this.getSize().width),(int)Math.ceil( .1 * this.getSize().height));
		g.setColor(Color.yellow);//up to now the background has been made, the ground has been made, and the sun's color has been set
		int scaler; //these calculations are to allow for relative positioning on the window
		if(this.getSize().width > this.getSize().height)
		{
			scaler = this.getSize().width;
		}
		else//this prioritizes the larger dimension for the sun
		{
			scaler = this.getSize().height;
		}
		g.fillOval((int)Math.ceil(.7 * this.getSize().width),(int)Math.ceil( .1 * this.getSize().height),(int)Math.ceil( .25 * scaler),(int)Math.ceil( .25 * scaler));
	}
	//arbitrary size
	public Dimension getPreferredSize()
	{
		return new Dimension( 300,300 );
	}
}
//This class performs similarly to the above, but with a random aspect
class circlePanel extends JPanel
{
	private static Random generator = new Random();
	private int maxCirc = 5;
	
	public circlePanel()
	{

	}
	//It is worth noting this causes new generation every refresh -- but this is per instructions
	public void paintComponent(Graphics g)
	{
		int circles = generator.nextInt(maxCirc-1) + 1;
		super.paintComponent(g);
		super.setBackground(Color.GRAY);
		for(int i = 0; i < circles; i++)
		{//color is randomly generated, number of circles is randomly generated, seeds are used to keep the circles all in frame
			Color rColor = new Color(generator.nextInt(255),generator.nextInt(255),generator.nextInt(255));
			g.setColor(rColor);
			int seedW = generator.nextInt(50);
			int seedH = generator.nextInt(50);
			int seedX = generator.nextInt(100-seedW);
			int seedY = generator.nextInt(100-seedH);
			g.fillOval((int)Math.ceil(((seedX)/100.0 * this.getSize().width)) , (int)Math.ceil(((seedY)/100.0 * this.getSize().height)), (int)Math.ceil((seedW/100.0 * this.getSize().width)), (int)Math.ceil((seedH/100.0 * this.getSize().height)));
			//g.fillOval((int)Math.ceil((.2 * this.getSize().width)) , (int)Math.ceil((.3 * this.getSize().height)), (int)Math.ceil((.5 * this.getSize().width)), (int)Math.ceil((.3 * this.getSize().height)));
			//g.fillOval(10+i,10+i,10,10);
		};
	}
	//arbitrary size
	public Dimension getPreferredSize()
	{
		return new Dimension( 300,300 );
	}
}
//The fileLister class uses a JLabel and JTextField in order to accomplish directory search
class fileLister extends JPanel
{
	private String directory;
	private JLabel text;
	public JTextField textField;
	public fileLister()
	{
		super.setLayout(new FlowLayout(FlowLayout.LEFT));
		directory = ".";
		textField = new JTextField(".",35);
		String data = getData(directory);
		text = new JLabel(data);
		super.add(textField);
		super.add(text);
		textField.addActionListener(//action listener listens for enter by default
				new ActionListener()
				{
					public void actionPerformed(ActionEvent event)
					{
						directory = textField.getText();//loads the input and calls the function on enter
						String data = getData(directory);
						text.setText(data);
					}
				});
	}
	//could have been left out but kept in for consistency. Also of note, calling the super instead of leaving blank fixed some errors.
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
	}
	
	public String getData(String directory)
	{//The label can take HTML format, so we use this here to implement line breaks.
		String ret = "<html><pre>------------------------------------------------------------<br>Directory Contents :<br>------------------------------------------------------------<br>";
		File dir;//The border is dual funtional, for some reason input would cut out when using tabs, the borders prevent that and allow for good deliniation.
		//if(directory != ".")
		//{
			dir = new File(directory);
		//}
		//else
		//{
		//	dir = new File(System.getProperty("user.dir"));
		//}
		if(!dir.exists())
		{
			return "Invalid Directory!";
		}
		File[] files = dir.listFiles();
		for(File f : files)
		{
			ret = ret + f.getName() + "\t-\t";
			if(f.isDirectory())
			{
				ret = ret + "Directory<br>";
			}
			else
			{
				ret = ret + f.length() + " bytes<br>";
			}
		}
		ret = ret + "------------------------------------------------------------</pre></html>";
		return ret;
	}//This class could probably use a scroll bar, however it was not listed in requirements
	public Dimension getPreferredSize()
	{//Arbitrary size
		return new Dimension( 400,600 );
	}
}
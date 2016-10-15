import javax.swing.JFrame;

public class HW4Main {
	public static void main( String args[] )
	{ 
	   DesktopFrame dFrame = new DesktopFrame();  
	   dFrame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
	   dFrame.setSize( 800, 600 ); // set frame size
	   dFrame.setVisible( true ); // display frame
	}
}

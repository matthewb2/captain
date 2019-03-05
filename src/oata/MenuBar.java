package oata;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.io.File;
import java.util.Iterator;
import java.util.Vector;

import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTree;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.TreeModelEvent;
import javax.swing.event.TreeModelListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;
 
public class MenuBar {
	public static void main(String[] args) {

	      
        JMenuBarEx ex = new JMenuBarEx();
        ex.setVisible(true);
  
	}
	
}

	
class JMenuBarEx extends JFrame  implements ActionListener, 
MouseListener, MouseMotionListener, MouseWheelListener,
KeyListener, ListSelectionListener  {
 
	private JFrame frame;  
    private JMenuItem   open, exit, about, random, deletefile, resize, save, saveas;
    private JMenuItem   fullscreen, delete, previous, next;
    private JFileChooser fc;
    private JLabel jl;
    private JLabel fjl;
    
  public JMenuBarEx() {
	   setTitle("Default Menu Application");
       
       //setLayout(new BorderLayout());
     
       
       // size of frame
       setSize(600,550);
        
       setVisible(true);
       
       setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       
       JMenuBar menuBar = new JMenuBar();
       JMenu menu1    = new JMenu("File");
       menu1.setMnemonic('F');
       
       ImageIcon icon_open = new ImageIcon(getClass().getResource("res/folder.png"));
       open     = new JMenuItem("Open Folder", icon_open);

       menu1.add(open);
       menuBar.add(menu1);
             
      	
       
       JMenu menu2    = new JMenu("Edit");
       
           
       
       menuBar.add(menu2);
       menu2.setMnemonic('E');
       
       deletefile     = new JMenuItem("Delete File");
       menu2.add(deletefile);
       
       resize     = new JMenuItem("Resize");
       menu2.add(resize);
       
      
       JMenu menu3    = new JMenu("View");
       menu3.setMnemonic('V');
       
       menuBar.add(menu3);
       fullscreen     = new JMenuItem("Full Screen");
       menu3.add(fullscreen);
       JMenu menu4    = new JMenu("Help");
       menu4.setMnemonic('H');
       about     = new JMenuItem("About");
       about.setMnemonic('A');
       menu4.add(about);
       
       menuBar.add(menu4);
       
       setJMenuBar(menuBar);	    
		
		this.addKeyListener(this);
		 //String[] fruits= {};
    }

@Override
public void valueChanged(ListSelectionEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void keyPressed(KeyEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void keyReleased(KeyEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void keyTyped(KeyEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void mouseWheelMoved(MouseWheelEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void mouseDragged(MouseEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void mouseMoved(MouseEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void mouseClicked(MouseEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void mouseEntered(MouseEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void mouseExited(MouseEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void mousePressed(MouseEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void mouseReleased(MouseEvent arg0) {
	// TODO Auto-generated method stub
	
}

@Override
public void actionPerformed(ActionEvent arg0) {
	// TODO Auto-generated method stub
	
};
}
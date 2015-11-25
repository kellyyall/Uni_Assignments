import java.util.Scanner;
import java.util.ArrayList;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

import org.newdawn.slick.SlickException;

/** To get the items' positions from a text file.*/
public class Read_items {
	/** File name*/
	private File filename;
	
	/** Build array lists to store the items' x and y position.*/
	ArrayList<Integer> Shieldx = new ArrayList<Integer>();
	ArrayList<Integer> Shieldy = new ArrayList<Integer>();
	ArrayList<Integer> Repairx = new ArrayList<Integer>();
	ArrayList<Integer> Repairy = new ArrayList<Integer>();
	ArrayList<Integer> Firepowerx = new ArrayList<Integer>();
	ArrayList<Integer> Firepowery = new ArrayList<Integer>();
	/** itemnames in the text file.*/
	private String itemname;
	
	/** check if there's a new line.*/
	private boolean right=true;
	/** item's initial x position*/
	private int x;
	/** item's initial y position*/
	private int y;
	
	/** File path*/
	private static final String FILE_PATH = Game.ASSETS_PATH + "/data/item.txt";
	/** Set a scanner*/
	private Scanner fileIn;
	
	/** Start reading file*/
	public Read_items()
		throws SlickException{
			filename= new File(FILE_PATH);
		}

	/** Reading file*/
	public void read_items(){		 
		try{
			FileInputStream stream = new FileInputStream(filename);
			fileIn = new Scanner(stream);
			while(right){
				itemname = fileIn.next();		     
					if(itemname.equals("Shield")){
						x=fileIn.nextInt();
						Shieldx.add(x);					
						y=fileIn.nextInt();					
						Shieldy.add(y);																							
						fileIn.nextLine();					
					}		     
					if(itemname.equals("Repair")){
						x=fileIn.nextInt();
						Repairx.add(x);					
						y=fileIn.nextInt();					
						Repairy.add(y);			
					} 
					if(itemname.equals("Firepower")){
						x=fileIn.nextInt();
						Firepowerx.add(x);					
						y=fileIn.nextInt();					
						Firepowery.add(y);																							
						fileIn.nextLine();					
						
					}  
				if(!fileIn.hasNextLine()){
						right=false;			
					}				
		}
		}
		catch (FileNotFoundException e){
			System.out.println("File not found.");
			System.exit(0);			
		}		
		fileIn.close();	
	}	
}


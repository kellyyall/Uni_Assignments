import org.newdawn.slick.SlickException;

/** Control all the items status. */
public abstract  class Item extends GameObject{
	 /** First, should draw all the items on the map. */
	 protected boolean draw=true;
	 
	 /** If player's position is in that range, then player can pick up the item.*/
	 private static final double PICKUP_RANGE=50;
	 
	 /** Create an item object.
	  * @param x The item's x position.
	  * @param y The item's y position.
	  * @param imgPath The item's image path.
	  * */
	 public Item (double x,double y, String imgPath)
		throws SlickException{
			super(x,y,imgPath);
		}
	 	 
	/** Check if the item has been picked up, if yes, then stop drawing that item
     * and change the player's stats.
     * @param player Need player's position to see if the item's been picked up.
     */			    
	public void pickup(Player player){
		if(Math.abs(x-player.getX())<PICKUP_RANGE && Math.abs(y-player.getY())<PICKUP_RANGE && draw==true){								draw=false;
			this.changestuff(player);	
		}			
	}
		
	/** Change player's stats.*/
	public abstract void changestuff(Player player);
}

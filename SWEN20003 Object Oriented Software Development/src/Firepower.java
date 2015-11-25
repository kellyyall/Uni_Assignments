import org.newdawn.slick.SlickException;

/** Present all the firepowers.*/
public class Firepower extends Item {

	/** Firepower image*/
	private static final String FIREPOWER_PATH= Game.ASSETS_PATH + "/items/firepower.png";

	/** Create a firepower object.
	 * @param x The firepower's x position;
	 * @param y The firepower's y position;
	 * @throws SlickException
	 */
	public Firepower(double x, double y)
		throws SlickException{
			super(x,y,FIREPOWER_PATH);
		}
	
	/** Change player's stats.
	 * @param player Need to call method in the player class
	 */
	public void changestuff(Player player){
		 player.changefirepower();
	}

	
}


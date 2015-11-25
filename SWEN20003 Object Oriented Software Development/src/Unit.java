import org.newdawn.slick.SlickException;

/** Present all the units. */
public abstract class Unit extends GameObject{
	
	/** all the units have their own shield number. */
	protected int shield;
	/** all the units have their own full shield number.*/
	protected int maxShield;
	
	/** See if the unit is dead or not.
	 *  If they are, then need to stop rendering it.
	 *  */
	protected boolean draw=true;
	
	/** Within that range, unit's can touch each other, cause damage.*/
	private static final double PICKUP_RANGE=50;
		
	/** Create an unit object.
	 * @param x The unit's x position.
	 * @param y The unit's y position.
	 * @param imgPath The unit's image path.
	 * @param maxShield The unit's full shield number.
	 * */
	public Unit (double x,double y, String imgPath, int maxShield)
		throws SlickException{
			super(x,y,imgPath);
			this.shield = maxShield;
			this.maxShield = maxShield;
		}
	/** Check if the unit touch each other.
	 * @param player Need player's position to check if they collide.
	 */
	public void crash(Player player,World world){
		if(Math.abs(x-player.getX())<PICKUP_RANGE && Math.abs(y-player.getY())<PICKUP_RANGE && draw==true){	
			draw=false;
			this.changestat(player);	
		}
		else if (world.terrainBlocks(x-halfWidth(), y-halfHeight()) || world.terrainBlocks(x+halfWidth(), y+halfHeight()) || world.terrainBlocks(x+halfWidth(), y-halfHeight()) || world.terrainBlocks(x-halfWidth(), y+halfHeight())){
	         draw=false;
	    }
	}
    /** Change player's stats. */
	public abstract void changestat(Player player);

}
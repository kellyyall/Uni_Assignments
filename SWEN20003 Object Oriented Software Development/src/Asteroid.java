import org.newdawn.slick.SlickException;

/** Present all the asteroids. */
public class Asteroid extends Enemy{
    /** Asteroid's image */
	private static final String ASTEROIDIMG= Game.ASSETS_PATH + "/units/asteroid.png";
	/** Asteroid's full shield number.*/
	private static final int AST_FULL_SHIELD = 24;
    
	/**Create an asteroid.
	 * @param x The asteroid's x position.
	 * @param y The asteroid's y position.
	 * @throws SlickException
	 */
	public Asteroid(double x,double y)
		throws SlickException{
			super(x,y,ASTEROIDIMG,AST_FULL_SHIELD);		
		}
	
	/** Update asteroid's position.
	 * @param delta Time passed since last frame (milliseconds).
	 * @param world The world the asteroid is on (to check blocking).
	 * @param cam The current camera (to check blocking).
	 * @param player The player (to call player's class method).
	 * */
	public void update(int delta, World world, Camera cam,Player player){
		double x = this.getX();
        double y = this.getY();
        if (x > cam.getLeft() && x < cam.getRight() - 1 && y > cam.getTop() && y < cam.getBottom() - 1){
        	 y += (delta) * getSpeed();
        }
        //collision, the same as the player.
        moveto(world, x, y);
	}
     /** Asteroid's moving downward at speed of 0.2*/
	private double getSpeed(){
	        return 0.2;
	    }
	 
    /** Check collision with the wall.
     * @param world The world the asteroid is on (to check blocking).
     * @param x New x coordinate.
     * @param y New y coordinate.
     * */
    private void moveto(World world, double x, double y){
        if (!world.terrainBlocks(x-halfWidth(), y+halfHeight()) && !world.terrainBlocks(x+halfWidth(), y-halfHeight()) && !world.terrainBlocks(x-halfWidth(), y-halfHeight()) && !world.terrainBlocks(x+halfWidth(), y+halfHeight())){
            this.setX(x);
            this.setY(y);
        }

       else if (!world.terrainBlocks(this.getX()-halfWidth(), y-halfHeight()) && !world.terrainBlocks(this.getX()+halfWidth(), y+halfHeight()) && !world.terrainBlocks(this.getX()+halfWidth(), y-halfHeight()) && !world.terrainBlocks(this.getX()-halfWidth(), y+halfHeight())){
            this.setY(y);
        }

        else if (!world.terrainBlocks(x+halfWidth(), this.getY()-halfHeight()) && !world.terrainBlocks(x-halfWidth(), this.getY()-halfHeight()) && !world.terrainBlocks(x+halfWidth(), this.getY()+halfHeight()) && !world.terrainBlocks(x-halfWidth(), this.getY()+halfHeight())){
            this.setX(x);
        }
    }

    /** When collided with the player, need to change player's stats.
	 * @param player Need player to call the methods in player class.
	 * */
	public void changestat(Player player) {
		player.change_asteroiddamage();
	}
}

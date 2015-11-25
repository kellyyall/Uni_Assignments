import java.util.ArrayList;

import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;
import org.newdawn.slick.SlickException;
/** Present the boss*/
public class Boss extends Enemy {
	/** Boss's image.*/
	private static final String BOSSIMG= Game.ASSETS_PATH + "/units/boss.png";
	/** Boss's full shield number.*/
	private static final int BOSS_FULL_SHIELD = 100;
	
	/** Set boss's cooldown to 0.*/
    private int cooldown=0;
    /**Build a arraylist to store all the enemy missiles that have been created.*/
    ArrayList<Missile> arraymissile = new ArrayList<Missile>();

    /** Create a Boss.*/
	public Boss(double  x,double y)
		throws SlickException{
		  super(x,y,BOSSIMG,BOSS_FULL_SHIELD);		
		}
	/** Update boss's movement, and set the missile's cooldown timer*/
	public void update(int delta, World world, Camera cam,Player player) throws SlickException{
		double x = this.getX();
        double y = this.getY();
        if (x > cam.getLeft() && x < cam.getRight() - 1 && y > cam.getTop() && y < cam.getBottom() - 1){
        	 x += (delta) * getSpeed();
        	 if(cooldown<=0){
             	EnemyMissile addMissile = new EnemyMissile(this.getX(),this.getY());
             	world.addEnemyMissile(addMissile);
             	cooldown = 60;
             	} else {
             		cooldown -= delta;
             	}
          	//Collision with wall, the same as the player.
          	moveto(world, x, y);
        	 }
        }

	
	/** the boss's moving at speed of 0.2*/
	private double getSpeed(){
	        return 0.2;
        }
	 
	 /** Check collision with the wall
	 * @param world The world the boss is on (to check blocking).
     * @param x New x coordinate.
     * @param y New y coordinate.
     * */
    private void moveto(World world, double x, double y){
        if (!world.terrainBlocks(x-halfWidth()-1, y+halfHeight()-1) && !world.terrainBlocks(x+halfWidth()-1, y-halfHeight()-1) && !world.terrainBlocks(x-halfWidth()-1, y-halfHeight()-1) && !world.terrainBlocks(x+halfWidth()-1, y+halfHeight()-1)){
            this.setX(x);
            this.setY(y);
        }

       else if (!world.terrainBlocks(this.getX()-halfWidth()-1, y-halfHeight()-1) && !world.terrainBlocks(this.getX()+halfWidth()-1, y+halfHeight()-1) && !world.terrainBlocks(this.getX()+halfWidth()-1, y-halfHeight()-1) && !world.terrainBlocks(this.getX()-halfWidth()-1, y+halfHeight()-1)){
            this.setY(y);
        }

        else if (!world.terrainBlocks(x+halfWidth()-1
        		, this.getY()-halfHeight()-1) && !world.terrainBlocks(x-halfWidth()-1, this.getY()-halfHeight()-1) && !world.terrainBlocks(x+halfWidth()-1, this.getY()+halfHeight()-1) && !world.terrainBlocks(x-halfWidth()-1, this.getY()+halfHeight()-1)){
            this.setX(x);
        }
    }

	public void changestat(Player player) {	
	}
}

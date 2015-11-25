/* SWEN20003 Object Oriented Software Development
 * Space Game Engine (Sample Project)
 * Author: Matt Giuca <mgiuca>
 */

import java.util.ArrayList;

import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.tiled.TiledMap;

/** Represents the entire game world.
 * (Designed to be instantiated just once for the whole game).
 */
public class World
{
    /** Map, containing terrain tiles. */
    private TiledMap map;
    
    /** The player's ship. */
    private Player player;
    /** The camera. */
    private Camera camera;
    /** The panel. */
    private Panel panel;
    /** Read Unit.txt */    
	private Read_file read_file;
	/** Read Item.txt */
	private Read_items read_items;
	
	/** Store all the enemies into an ArrayList. */
	private ArrayList<Enemy> enemies = new ArrayList<Enemy>();
	/** Store all the player missiles into an ArrayList. */
	private ArrayList<Missile> missiles = new ArrayList<Missile>();
	/** Store all the items into an ArrayList. */
	private ArrayList<Item> items = new ArrayList<Item>();
	/** Store all the enemy missiles into an ArrayList. */
	private ArrayList<EnemyMissile> enemymissile = new ArrayList<EnemyMissile>();

    /** Get the width of the game world in pixels. */
    public int getWidth()
    {
        return map.getWidth() * map.getTileWidth();
    }

    /** Get the height of the game world in pixels. */
    public int getHeight()
    {
        return map.getHeight() * map.getTileHeight();
    }

    /** Create a new World object. */
    public World()
    throws SlickException
    {
        map = new TiledMap(Game.ASSETS_PATH + "/map.tmx", Game.ASSETS_PATH);
        
        player = new Player(1296, 13716);
        // Create a camera, centred and with the player at the bottom
        camera = new Camera(this, player);
        
        panel = new Panel();
        
        read_file = new Read_file();
		read_file.read_file();
		
		read_items = new Read_items();
		read_items.read_items();
		
		//Add all the drones to the enemies ArrayList with the start positions.
		int droneIndex = read_file.Dronex.size();
		for(int l=0; l<droneIndex; l++){
			enemies.add(new Drone(read_file.Dronex.get(l), read_file.Droney.get(l)));
		}
		//Add all the fighters to the enemies ArrayList with the start positions.
		int fighterIndex = read_file.Fighterx.size();
		for(int n=0; n<fighterIndex; n++){
			enemies.add(new Fighter(read_file.Fighterx.get(n), read_file.Fightery.get(n)));
		}
		//Add all the asteroids to the enemies ArrayList with the start positions.
		int asteroidIndex = read_file.Asteroidx.size();
		for(int r=0; r<asteroidIndex; r++){
			enemies.add(new Asteroid(read_file.Asteroidx.get(r), read_file.Asteroidy.get(r)));
		}
		//Add boss to the enemies ArrayList.
		enemies.add(new Boss(1301,144));
		
		
		//Add all the shields to the item ArrayList.
		int shieldIndex = read_items.Shieldx.size();
		for(int m=0; m<shieldIndex; m++){
			items.add(new Shield(read_items.Shieldx.get(m), read_items.Shieldy.get(m)));
		}
		//Add all the repairs to the item ArrayList.
		int repairIndex = read_items.Repairx.size();
		for(int p=0; p<repairIndex; p++){
			items.add(new Repair(read_items.Repairx.get(p), read_items.Repairy.get(p)));
		}
		//Add all the firepowers to the item ArrayList.
		int firepowerIndex = read_items.Firepowerx.size();
		for(int q=0; q<firepowerIndex; q++){
			items.add(new Firepower(read_items.Firepowerx.get(q), read_items.Firepowery.get(q)));
		}		
    }

    /** True if the camera has reached the top of the map. */
    public boolean reachedTop()
    {
        return camera.getTop() <= 0;
    }

    /** Update the game state for a frame.
     * @param dir_x The player's movement in the x axis (-1, 0 or 1).
     * @param dir_y The player's movement in the y axis (-1, 0 or 1).
     * @param delta Time passed since last frame (milliseconds).
     */
    public void update(double dir_x, double dir_y, boolean isFiring,int delta)
    throws SlickException
    {
        // Move the camera automatically
        camera.update(delta);

        // Move the player automatically, and manually (by dir_x, dir_y)
        player.update(this, camera, dir_x, dir_y,isFiring, delta);
        
        // Centre the camera (in x-axis) over the player and bound to map
        camera.follow (player);
		
        // Update each single object in the enemies ArrayList.
		for(Enemy e:enemies){
			e.crash(player,this);
			e.update(delta, this, camera,player);
		}
		// Update each single object in the missiles ArrayList.
		for(Missile m: missiles){
			m.update(delta, this, camera);
		}
		// Update each single object in the items ArrayList.
		for(Item i: items){
			i.pickup(player);
		}
		// Update each single object in the enemymissile ArrayList.
		for(EnemyMissile em:enemymissile){
			em.update(delta, this, camera);
		}       
    }

    /** Render the entire screen, so it reflects the current game state.
     * @param g The Slick graphics object, used for drawing.
     * @param textrenderer A TextRenderer object.
     */
    public void render(Graphics g)
    throws SlickException
    {
        // Calculate the camera location (in tiles) and offset (in pixels)
        int cam_tile_x = (int) camera.getLeft() / map.getTileWidth();
        int cam_offset_x = (int) camera.getLeft() % map.getTileWidth();
        int cam_tile_y = (int) camera.getTop() / map.getTileHeight();
        int cam_offset_y = (int) camera.getTop() % map.getTileHeight();
        // Render w+1 x h+1 tiles (where w and h are 12x9; add one tile extra
        // to account for the negative offset).
        map.render(-cam_offset_x, -cam_offset_y, cam_tile_x, cam_tile_y,
            getScreenTileWidth()+1, getScreenTileHeight()+1);
        
        player.render(g, camera);
        
        panel.render(g, player.getshield(), player.getfullshield(), player.getfire_number());
        
        // Render each single object in the enemies ArrayList.
        for(Enemy e:enemies){
        	if(e.draw==true){
			e.render(g, camera);
        	}
		}
        // Render each single object in the missiles ArrayList.
        for(Missile m:missiles){
        	m.render(g, camera);
        }
        // Render each single object in the items ArrayList.
        for(Item i:items){
        	if(i.draw==true){
        		i.render(g,camera);
        	}
        }
        // Render each single object in the enemymissile ArrayList.
        for(EnemyMissile em:enemymissile){
        	em.render(g, camera);
        }        
    }
    
    /** Add play missile m to the missile ArrayList. */
    public void addMissile(Missile m){
        	missiles.add(m);
        }
    /** Add enemy missile em to the enemymissile ArrayList. */
    public void addEnemyMissile(EnemyMissile em){
    	    enemymissile.add(em);
    }
    
    /** Determines whether a particular map location blocks movement due to
     * terrain.
     * @param x Map x coordinate (in pixels).
     * @param y Map y coordinate (in pixels).
     * @return true if the location blocks movement due to terrain.
     */
    public boolean terrainBlocks(double x, double y)
    {
        int tile_x = (int) x / map.getTileWidth();
        int tile_y = (int) y / map.getTileHeight();
        // Check if the location is off the map. If so, assume it doesn't
        // block (potentially allowing ships to fly off the map).
        if (tile_x < 0 || tile_x >= map.getWidth()
            || tile_y < 0 || tile_y >= map.getHeight()){
        	
        return true;
        }
        // Get the tile ID and check whether it blocks movement.
        int tileid = map.getTileId(tile_x, tile_y, 0);
        String block = map.getTileProperty(tileid, "block", "0");
        return Integer.parseInt(block) != 0;
    }

    /** Get the width of the screen in tiles, rounding up.
     * For a width of 800 pixels and a tilewidth of 72, this is 12.
     */
    private int getScreenTileWidth()
    {
        return (Game.SCREENWIDTH / map.getTileWidth()) + 1;
    }

    /** Get the height of the screen in tiles, rounding up.
     * For a height of 600 pixels and a tileheight of 72, this is 9.
     */
    private int getScreenTileHeight()
    {
        return (Game.SCREENHEIGHT / map.getTileHeight()) + 1;
    }
}

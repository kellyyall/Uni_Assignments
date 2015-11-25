//Kelly Yang -- id 566123

package aiproj.fencemaster.kya;
import java.io.PrintStream;
import java.util.ArrayList;
import aiproj.fencemaster.*;

public class kya implements Player, Piece{
	public int color, max, min;
	static ArrayList<Integer> Blackx = new ArrayList<Integer>();
	static ArrayList<Integer> Blacky = new ArrayList<Integer>();
	static ArrayList<Integer> Whitex = new ArrayList<Integer>();
	static ArrayList<Integer> Whitey = new ArrayList<Integer>();
	static ArrayList<Move> Movelist = new ArrayList<Move>();
	public int dimension;
	public int color;
	
	public int getWinner() {
		return INVALID;
	}

	/** Simply initialise the player */
	public int init(int n, int p) {
		if(p!=BLACK && p!=WHITE){
			return INVALID;
		}
		dimension=n;
	    color=p;		
		return 0;
	}

	/** Make a move by the player */
	public Move makeMove() {
		Move onemove=new Move();
		boolean makemove=true;
		while(makemove){
			onemove.Row=(int)(Math.random()*(2*dimension-1));
			//Determine the col by each row.
			if(onemove.Row>=0 && onemove.Row<=dimension-1){
				onemove.Col=(int)(Math.random()*(dimension+onemove.Row));
			}
			if(onemove.Row>=dimension && onemove.Row<=2*dimension-2){
				int Low = onemove.Row-dimension+1;
				int High = 2*dimension-1;
				onemove.Col=(int) (Math.random()*(High-Low)+Low);
			}
			onemove.P=color;
			
			/* Making a move next to its same color priority. */
			if(validmoves(onemove)){
				if (Movelist.size()>1){
					for (Move inlist : Movelist){
						if (inlist.P == onemove.P){
							if (IsNext(inlist.Row, inlist.Col, onemove.Row, 
									onemove.Col, dimension)){
								makemove = false;
							}
						}
					} 
					if (makemove == true && Movelist.size() > (dimension)*dimension ){
						makemove = false;
					}
				}else
				makemove=false;
			}
		}Movelist.add(onemove);
		return onemove;
	}
	
	/** Check if the move is already on board, if yes-move's valid, if not-invalid*/
	public boolean validmoves(Move checkmove){
		for(Move inlist: Movelist){
			if(checkmove.Row==inlist.Row && checkmove.Col==inlist.Col){
				return false;
			}
		}		
		return true;	
	}


	/** Check if the opponent move is valid */
	public int opponentMove(Move m) {	
		/*Not valid if it's already a piece on the board.*/
		for (Move inlist : Movelist){
			if(m.Col==inlist.Col && m.Row==inlist.Row){
				return INVALID;
			}
		}
		/*Not valid if the m move is out the board */
		if((m.Row>=0 && m.Row<=dimension-1) && (m.Col<0 || m.Col>(dimension+m.Row))){
			return INVALID;
		}
		if((m.Row>=dimension && m.Row<=2*dimension-2) && (m.Col<(m.Row-dimension+1) ||
				m.Col>( 2*dimension-1))){
			return INVALID;
		}
		/*else return ok and add the move to movelist for further use.*/
		else{
			Movelist.add(m);
			return 0;
		}
	}

	/** Print the Board */
	public void printBoard(PrintStream output) {
		int i,r;
		int n=dimension, prow=0;
		while(prow<=(2*n-2)){
			/* Print top half of the board */
			if(prow<=n-1){
				for(i=0;i<=(n+prow)-1;i++){
					boolean ispiece=false;
					for(Move inlist: Movelist){
						if(inlist.Row==prow && inlist.Col==i){
							System.out.print(inlist.P+" ");													
							ispiece=true;
						}							
					}
					if(!ispiece){
						System.out.print("- ");	
					}
					
				}	
				System.out.print("\n");
			}
			/* Print bottom half of the board */
			else if(prow>=n){
				for(r=prow-n+1;r<=(2*n-2);r++){
					boolean ispiece=false;
					for(Move inlist: Movelist){
						if(inlist.Row==prow && inlist.Col==r){
							System.out.print(inlist.P+" ");													
							ispiece=true;
						}							
					}
					if(!ispiece){
						System.out.print("- ");	
					}
				}		
				System.out.print("\n");				
			}		    
			prow++;
		}
	}
	
	/** Check if two piece are neighbors.
     * @param w and z - x,y positions of one chess.
     * @param x and y - x.y positions of another chess.
     */
	public static  boolean IsNext(Integer w, Integer z, Integer x, Integer y, Integer N){		
		Integer difx, dify;
		difx = x - w;
	    dify = y - z;		
	    if (x <= ((2*N - 2)/2)){
			if(( ((difx == -1)) && ((dify == 0) || (dify == -1)))
				|| ((difx == 1)) && ((dify == 0) || (dify == 1)) ||
				((difx == 0) && ((dify == 1) || (dify == -1))) ){
				return true; 
			}
		}
		else if(( ((difx == 1)) && ((dify == 0) || (dify == -1))) 
				|| (((difx == -1)) && ((dify == 0) || (dify == 1))) 
				|| ((difx == 0) && ((dify == 1) || (dify == -1))) ){
				return true; 
			}		
		return false;			
	}

	/* MiniMax function */	
	public int MiniMax(int cutoff, int row, int col, int P, ArrayList<Move> state){
		int n = 0, i =0, aux = dimension; 
		cutoff ++;
		if (P == 1){			
			Whitex.add(row);
			Whitey.add(col);
		}
		if (P == 2){			
			Blackx.add(row);
			Blacky.add(col);
		}
		int eval  = getWinner(); 
		//test if its the maximum depth
		if (cutoff == 4){ 
			return 0;
		}				
		/*test if its a terminal node (have a winner), if the winner is the player return positive value.*/
		if (eval == P){
			cutoff = 0;
			return 1;	
		}
		/* test if its a terminal node (have a winner), if the winner is the opponent return negative value.*/
		else if (eval>0){ 
			cutoff = 0;
			return -1;
		}
		// if its a players move
		else if (P == color){		
			while(n <= (2*dimension-2)){
				for (i=0; i< aux; i++){
					for(Move inlist : Movelist){
					// check if the move has not been made yet						
						if(inlist.Row == n && inlist.Col == i){
						}else{										
							if (P==2){
								P=1;
							}else{
								P=2;
							}
							//opponent node evaluation
							int best_value = MiniMax (cutoff, inlist.Row, inlist.Col, P, state);
							//find the biggest minimax value between the nodes												
							if (best_value > max){ 
								max = best_value;
							}
						}
					}
					if(n < (2*dimension-2)/2){
						aux++;
					}else{
						aux--;
						n++;
					}		
					Move onemove=new Move();
					onemove.Col = col;
					onemove.Row = row;
					onemove.P = P;
					state.add(onemove); 
					return max;			
				}else{		
				//opponent's move
					while(n <= (2*dimension-2)/2){
						for (i=0; i< aux; i++){
							for(Move inlist : Movelist){
								if(inlist.Row == n && inlist.Col == i){							
								}else{								
									if(P==2){
										P=1;
									}else{
										P=2;
									}
									int worst_value = MiniMax (cutoff ++, inlist.Row, inlist.Col, P, state);
									//find the lowest minimax value between the nodes							
									if (worst_value < min){
										min = worst_value;
									}
								}
							}
							if(n < (2*dimension-2)/4){
								aux ++;
							}else{
								aux--;
								n++;
							}
							Move onemove=new Move();
							onemove.Col = col;
							onemove.Row = row;
							onemove.P = P;
							state.add(onemove);
							return min;
						}	
					}
				}
			}
		}
	}

package eins_e;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Iterator;

public class Random implements Iterable<Integer>{
	int z = 1, m = 256, a = 17;
	@Override
	public Iterator<Integer> iterator() {
		return new RandomIterator();
	}
	
	public Iterator<Integer> iterator(int keim, int modul, int faktor){
		this.z = keim;
		this.m = modul;
		this.a = faktor;
		return new RandomIterator();
	}
	
	
	private class RandomIterator implements Iterator<Integer>{

		@Override
		public boolean hasNext() {
			return true;
		}

		@Override /*X(n+1)=(aX(n)+ c)mod m */
		public Integer next() {
			if(hasNext()){
				return 0 + (int)(Math.random()*Integer.MAX_VALUE);
			}
//			int q = m/a;
//			int r = m%a;
//			int h = a*(z%q)-r*(z/q); 
//		        /* Java rundet hier automatisch zu nächstkleineren ganzen Zahl */
//			if(h >= 0){
//			    z = h; /* Ausgangswert der nächsten Auswertung */
//			    return z;
//			}
//			else{
//			    z = h+m; /* Ausgangswert der nächsten Auswertung */
//			    return z;
//			}
			throw new UnsupportedOperationException("gibts ned.");
		}

		@Override
		public void remove() {}
		
	}

    static public void main(String[] args){
    	String eingabe = null;
    	Random lkg = new Random();
    	Iterator<Integer> iter = lkg.new RandomIterator();
    	int i, count = 0;
    	
    	BufferedReader console = new BufferedReader(new InputStreamReader(System.in));
		
		do{
			System.out.println("Mit der Entertaste generieren Sie eine Zufallszahl.");
			try {
				eingabe = console.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}
			count++;
	    	i =iter.next();
	    	System.out.println(count + ".ter Wert: " + i);
		}while(eingabe.hashCode() == 0);
    	
    }

}
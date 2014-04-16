package eins_f;

import java.io.FileReader;
import java.io.Reader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.Iterator;

public class ReaderIterable implements Iterable<Character>{
	private static Reader reader;
	private int n;
	
	@Override
	public Iterator<Character> iterator() {
		return new ReaderIterator();
	}
	
	public ReaderIterable(Reader r){
		reader = new BufferedReader(r);
		try{
			n = reader.read();
		}catch(IOException e){
			n =- 1;
		}
	}

	private class ReaderIterator implements Iterator<Character>{
		
		public Character next(){
			Character result = new Character((char)n);
			try{
				n = reader.read();
			}catch(IOException e){
				n = -1;
				System.out.println("Konnte nicht gelesen werden.");
			}
			return result;
		}

		public boolean hasNext(){
			return n != -1;
		}

		public void remove(){}
	}
	
	public static void main(String[] args) throws IOException {
    	ReaderIterable ri = new ReaderIterable(new FileReader("/home/steph/workspace/PMT/Aufgabe 1/src/eins_f/test.txt"));
    	
		for (Character c:ri){
			System.out.println(c);
		}
    }
}

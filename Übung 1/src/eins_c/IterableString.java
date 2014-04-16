package eins_c;

import java.util.Iterator;

public class IterableString implements Iterable<Character>{
	private String testString;
	
	@Override
	public Iterator<Character> iterator() {
		return new ItString();
	}
	
	public IterableString(){
		this.testString = "Hallo Welt";
	}
	
	private class ItString implements Iterator<Character>{
		private int index = 0;
		@Override
		public boolean hasNext() {
			return index < testString.length();
		}

		@Override
		public Character next() {
			return testString.charAt(index++);
		}

		@Override
		public void remove() {}
		
	}
	
	public static void main(String[] args) {
		IterableString is = new IterableString();
		Iterator<Character> stringIterator = is.new ItString();
		char zeichen;
		
		System.out.println("Durchlaufe den String zeichenweise:\n");
		while(stringIterator.hasNext()){
			zeichen = stringIterator.next();
			System.out.print("'" + zeichen + "' ");
		}

	}

}

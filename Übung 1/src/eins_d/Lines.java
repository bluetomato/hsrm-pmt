package eins_d;

import java.util.Iterator;

public class Lines implements Iterable<String>{
	private String s;
	private String[] stringArray;

	@Override
	public Iterator<String> iterator() {
		return new LineIterator();
	}
	
	public Lines(String text){
		this.s = text;
		stringArray = s.split("\n");
	}

	private class LineIterator implements Iterator<String>{
		int index = 0;
		
		@Override
		public boolean hasNext() {
			return index < stringArray.length;
		}

		@Override
		public String next() {
			return stringArray[index++];
		}

		@Override
		public void remove() {}
		
	}
	
	public static void main(String[] args) {
		Lines lines = new Lines("Hallo\ndas ist ein Teststring\nmit mehreren Zeilen.\nNatürlich.\nWas denkst denn du!");
		Iterator<String> lineIterator = lines.new LineIterator();
		String st;
		System.out.println("Zeilenweise den String ausgeben:\n");

		while(lineIterator.hasNext()){
			st = lineIterator.next();
			System.out.println(st);
		}

	}
}

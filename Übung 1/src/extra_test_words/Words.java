package extra_test_words;

import java.util.Iterator;
import java.util.StringTokenizer;

public class Words implements Iterable<String>{
	private String testString;
	private StringTokenizer	stringToken;
	@Override
	public Iterator<String> iterator() {
		return new WortIterator();
	}
	
	public Words(){
		this.testString = "Hallo Welt";
		this.stringToken = new StringTokenizer(testString);
	}
	public class WortIterator implements Iterator<String>{

		@Override
		public boolean hasNext() {
			return stringToken.hasMoreTokens();
		}

		@Override
		public String next() {
			return stringToken.nextToken();
		}

		@Override
		public void remove() {}
		
	}
	
	

}

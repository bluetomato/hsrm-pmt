package extra_words;

import java.util.Iterator;

public class WordsTest {
	public static void main(String[] args){
		Words words = new Words();
		Iterator<String> wordIterator = words.new WortIterator();
		String ausgabe;
		
		System.out.println("Ausgabe der Lines (Worte):\n");
		while(wordIterator.hasNext()){
			ausgabe = wordIterator.next().toString();
			System.out.println("'" + ausgabe + "' ");
		}
	}

}

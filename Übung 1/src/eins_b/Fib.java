package eins_b;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Iterator;

public class Fib implements Iterable <Integer>{
	//1, 1, 2, 3, 5 usw (zwei zahlen davor zusammen addiert)
	private class FibIt implements Iterator <Integer>{
		private int b0 = 0;
		private int b1 = 1;
		
		@Override
		public boolean hasNext() {
			if(b0 + b1 >= 0){
				return true;
			}else{
				return false;
			}
		}

		@Override
		public Integer next() {
			int ret = b0 + b1;
			b0 = b1;
			b1 = ret;
			return ret;
		}

		@Override
		public void remove() {}
	}
	
	@Override
	public Iterator<Integer> iterator() {
		return new FibIt();
	}
	
	public static void main(String[] args) {
		String eingabe = null;
		int max_zeilen = 10;
		int hurtz = 1;
		
		Fib fib = new Fib();
		Iterator<Integer> fibIt = fib.new FibIt();
		BufferedReader console = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Wie viele Ziffern möchten Sie ausgeben lassen?");
		try {
			eingabe = console.readLine();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		max_zeilen = Integer.parseInt(eingabe);
		
		for(int i = 0; i <= max_zeilen; i++){

			System.out.println(hurtz + "\n");
			hurtz = fibIt.next();
		}
		
//		int count = 0;
//		ALLE FIBONACCI-ZAHLEN OHNE NEXT
//		for(int i : fib){
//			if(count >= max_zeilen){
//				break;
//			}
//			count++;
//			System.out.println(i);
//		}
//		System.out.println("\n");
	}
}

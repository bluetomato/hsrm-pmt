package eins_a;
import java.util.Iterator;


public class IntRange implements Iterable <Integer>{
	Iterator<Integer> iterator = new IntegerRange();
	int value; 
	int max_zahlen = Integer.MAX_VALUE;
	int aktNum;
	int til;
	int steps;
	
	@Override
	public Iterator<Integer> iterator() {
		return new IntegerRange();
	}

	public IntRange(){
		this(0);
		
	}

	public IntRange(int from){
		this(from, Integer.MAX_VALUE-1); //-1 wegen Überlauf, da man bei 0 anfängt zu zählen
	}

	public IntRange(int from, int to){
		this(from, to+1, 1);
	}

	public IntRange(int from, int to, int step){
		this.aktNum = from;
		this.til = to+1;
		this.steps = step;
	}
	private class IntegerRange implements Iterator <Integer>{
		
		@Override
		public boolean hasNext() {
			return aktNum < til;
		}

		@Override
		public Integer next() {
			int res = aktNum;
			aktNum = aktNum + steps;
			return res;
		}

		@Override
		public void remove() {}

	}
	
	public static void main(String[] args) {
		//IntRange ir = new IntRange();
		//IntRange ir = new IntRange(7);
		//IntRange ir = new IntRange(3,9);
		
		IntRange ir = new IntRange(2,20,2);
	
		for(int i: ir){
			System.out.println(i);
		}
	}

}

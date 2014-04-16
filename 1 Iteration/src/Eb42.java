import java.util.Iterator;


public class Eb42 implements Iterable<Integer>{

	@Override
	public Iterator<Integer> iterator() {
		return new EinsBis42();
	}
	
	private class EinsBis42 implements Iterator <Integer>{
		int letzte_zahl = 0;
		
		@Override
		public boolean hasNext() {
			//Vorbedingung checken
			if(!hasNext()){ 
				throw new RuntimeException("Lass das, du Arsch.");
			}
			return true;
		}

		@Override
		public Integer next() {
			return ++letzte_zahl;
		}

		@Override
		public void remove() {
			// TODO Auto-generated method stub
			
		}
		
	}
	
	public static void main(String[] args){
		Eb42 outer = new Eb42();
		Iterator <Integer> it = outer.new EinsBis42();
		while(it.hasNext()){
			int e = it.next();
			System.out.println(e);
		}
	}

}

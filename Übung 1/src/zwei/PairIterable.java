package zwei;

import java.util.Iterator;

public class PairIterable<A,B> implements Iterable<Pair<A,B>>{

	Iterable<A> iterableA;
	Iterable<B> iterableB;
	
	public PairIterable(Iterable<A> it1, Iterable<B> it2){
		this.iterableA = it1;
		this.iterableB = it2;
	}

	@Override
	public Iterator<Pair<A, B>> iterator() {
		return new PairIterator();
	}
	
	private class PairIterator implements Iterator <Pair<A,B>>{
		Iterator<A> ita = iterableA.iterator();
		Iterator<B> itb = iterableB.iterator();
		
		@Override
		public boolean hasNext() {
			return ita.hasNext() && itb.hasNext();
		}

		@Override
		public Pair<A, B> next() {
			A retOne = ita.next();
			B retTwo = itb.next();
			return new Pair<A,B>(retOne, retTwo);
		}

		@Override
		public void remove() {}

	}

}

package eins;

import java.util.Iterator;

public class TwoDimIterable<A,B> implements Iterable<Pair<A,B>> {
	Iterable<A> iteratorA;
	Iterable<B> iteratorB;
	
	public TwoDimIterable(Iterable<A> it1, Iterable<B> it2){
		this.iteratorA = it1;
		this.iteratorB = it2;
	}
	
	private class TwoIterator implements Iterator<Pair<A,B>>{
		Iterator<A> ita = iteratorA.iterator();
		Iterator<B> itb = iteratorB.iterator();
		A a = ita.next();
		
		@Override
		public boolean hasNext() {
			return ita.hasNext() || itb.hasNext();
		}

		@Override
		public Pair<A,B> next() {
			if(itb.hasNext()){
				return new Pair<A,B>(a, itb.next());
			}
			else{
				itb = iteratorB.iterator();
				a = ita.next();
				return new Pair<A,B>(a, itb.next());
			}
		}

		@Override
		public void remove() {}
	}

	@Override
	public Iterator<Pair<A,B>> iterator() {
		return new TwoIterator();
	}

}

package zwei;

import java.util.Iterator;

public class Interleave<A> implements Iterable<A>, Iterator<A> {
	Iterable<A> it1;
	Iterable<A> it2;
	int count = 0;
	
	public Interleave(Iterable<A> it1, Iterable<A> it2){
		this.it1 = it1;
		this.it2 = it2;
	}
	@Override
	public Iterator<A> iterator() {
		return this;
	}

	@Override
	public boolean hasNext() {
		return it1.iterator().hasNext() && it2.iterator().hasNext();
	}

	@Override
	public A next() {
		this.count++;
		if(this.count % 2 == 0){
			return it2.iterator().next();
		}else{
			return it1.iterator().next();
		}
	}

	@Override
	public void remove() {}

}

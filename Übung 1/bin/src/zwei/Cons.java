package zwei;

import java.util.Iterator;

public class Cons<E> implements Iterable <E>, Iterator<E>{
	E head;
	Iterable<E> tail;
	
	public Cons(E head, Iterable<E> tail){
		this.head = head;
		this.tail = tail;
	}
	
	@Override
	public Iterator<E> iterator() {
		return this;
	}
	
	int counter = 0;
		
	@Override
	public boolean hasNext() {
		counter++;
		if(counter > 1){
			return tail.iterator().hasNext();
		}else{
			return true;
		}
	}

	@Override
	/*Der Iterator zu dieser Klasse soll beim ersten Aufruf von
	next() das Element head zurück geben und anschließend die Elemente des Iterators
	von tail*/
	public E next() {
		counter++;
		if(counter > 1){
			return tail.iterator().next();
		}else{
			return head;
		}
	}

	@Override
	public void remove() {}
}

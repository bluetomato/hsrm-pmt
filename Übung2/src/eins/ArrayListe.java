package eins;

import java.util.Iterator;

import eins.Iterable;

public class ArrayListe<A> implements Iterable<A>{
	A[] array;
	private int size;
	
	@SuppressWarnings("unchecked")
	ArrayListe(){
		this.size = 0;
		this.array = (A[]) new Object[5];
	}
	
	@SuppressWarnings("unchecked")
	ArrayListe(A... xs){
		this.size = 0;
		this.array = (A[]) new Object[5];
		
		for(A x:xs){
			add(x);
		}
	}
	
	/* Größe ist 0? -> leer, ansonsten ist etwas drin. */
	boolean isEmpty(){
		if(size == 0){
			return false;
		}
		return true;
	}
	
	/* Gibt Größe zurück (die size wird jedesmal hochgerechnet, wenn ein Element hinzugefügt wird) */
	public int length(){
		return size;
	}
	
	/* Gibt A an der indexstelle zurück */
	public A get(int index){
		return array[index];
	}
	
	@SuppressWarnings("unchecked")
	void add(A element){
		/* Wenn size größergleich Größe des Array */
		if(size >= array.length){
			/* Neues Array mit der doppelten Länge */
			A[] newArray = (A[]) new Object[array.length*2];
			/* Jedes Element des alten Arrays in das neue Array kopieren */
			for(int i = 0; i < array.length; i++){
				newArray[i] = array[i];
			}
			array = newArray; 
		}
		array[size] = element;
		++size;
	}
	
	@Override
	public Iterator<A> iterator() {
		return new SuperCoolerIterator();
	}
	
	
	private class SuperCoolerIterator implements Iterator<A>{
		int index = 0;
		
		@Override
		public boolean hasNext() {
			return index < size;
		}

		@Override
		public A next() {
			A ret = get(index);
			index++;
			return ret;
		}
		
	}
}

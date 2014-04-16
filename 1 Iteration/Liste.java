package eins;

import eins.Iterable;

import java.util.Iterator;
import java.util.function.Consumer;

public class Liste <A> implements Iterable<A>{
	A head;
	Liste<A> tail;
	
	@Override
	public Iterator<A> iterator() {
		throw new UnsupportedOperationException("gibts ned.");
	}
	
	Liste(A head, Liste<A> tail){
		this.head = head;
		this.tail = tail;
	}
	
	Liste(){
		this(null, null);
	}
	
	Liste(A... xs){ //beiebig viele A's
		for(A x:xs){
			add(x);
		}
	}
	
	boolean isEmpty(){
		return head == null && tail == null;
	}
	
	//die liste kann das selbst, braucht keinen iterator?!
	public int length(){
		if(isEmpty()){
			return 0;
		}
		return tail.length()+1;
	}
	
	boolean contains(A element){
		if(isEmpty()){
			return false;
		}
		if(head.equals(element)){
			return true;
		}
		return tail.contains(element);
	}
	
	void machtAlle(Consumer<A> c){
		if(!isEmpty()){
			c.accept(head);
			tail.machtAlle(c);
		}
	}
	
	Liste<A> add(A element){
		if(isEmpty()){
			head = element;
			tail = new Liste<>();
		}else{
			tail.add(element);
		}
		return this;
	}
	
	public static void main(String[] args){
		Liste<Character> cs = new Liste<>();
		System.out.println(cs.length());
		cs = new Liste("R", cs);
		System.out.println(cs.length());
		
		cs.add(' ').add('U').add('N');
		Liste<Integer> xs = new Liste<>(1,17,3,32);
		xs.machtAlle((x)->{System.out.println(x*x);});
	}
}

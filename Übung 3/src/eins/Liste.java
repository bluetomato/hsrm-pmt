package eins;

import java.util.function.Consumer;
import java.util.Iterator;

import eins.OurList;

class Liste<A> implements OurList<A>{
	
	private A head;
	private OurList<A> tail;
	private int size;
	
	public Liste(A head, OurList<A> tail) {
		this.head = head;
		this.tail = tail;
		this.size = 0;
	}
	
	public Liste() {
		this(null, null);
	}
	
	@SuppressWarnings("unchecked")
	public Liste(A... xs) {
		for (A x:xs) {
			add(x);
			size++;
		}
	}
	
	@Override 
	public String toString() {
		if (this.isEmpty()) {
			return "";
		}else{
			return "["+this.head.toString()+"]" +this.tail.toString();
		}
	}

	@Override
	public boolean isEmpty() {
		if (size == 0) {
			return true;
		}
		return false;
	}

	@Override
	public A head() {
		return head;
	}

	@Override
	public OurList<A> tail() {
		return tail;
	}

	/* Berechnet Länge der Liste */
	@Override
	public int length() {
		return size;
	}

	/* Wird wahr, wenn ein Element der Liste gleich dem übergebenen Argument ist. */
	@Override
	public boolean contains(A el) {
		if (isEmpty()){
			return false;
		}
		if (head.equals(el)){
			return true;
		}
		return tail.contains(el);
	}

	/* Wendet die Methode des Consumer-Objekts auf alle Elemente an. */
	@Override
	public void machtAlle(Consumer<A> c) {
		if(!isEmpty()){
			c.accept(head);
			tail.machtAlle(c);
		}		
	}

	/* Modifiziert die Liste, indem am Ende das neue Element hinzugefügt wird. */
	@Override
	public OurList<A> add(A el) {
		if (isEmpty()){
		    head = el;
		    tail = new Liste<>();
		}else{
		    tail.add(el);
		}
		size++;
		return this;
	}
	
	/* Gibt die Teilliste zurück, die entsteht, wenn die ersten i Elemente von
der Liste genommen werden. Ist i zu groß, so wird eine leere Liste zurück
gegeben. */
	@Override
	public OurList<A> drop(int i) {
		OurList<A> tmp = new Liste<>();
		if(i > size || i < 0){
			return tmp;
		} else if(i == 0){
			return this;
		}
		
		while(i <= (size-1)){
			tmp.add(this.get(i));
			i++;
		}
		return tmp;
	}

	/* Gibt die Teilliste bestehend aus den ersten i Elementen zurück. */
	@Override
	public OurList<A> take(int i) {
		return sublist(0, i);
	}

	/* Gibt eine Teilliste zurück, die von dem Index start beginnt und die
spezifizierte Länge hat. Ist die Liste zu kurz, wird eine entsprechend
kürzere bis hin zur leeren Liste zurück gegeben. */
	@Override
	public OurList<A> sublist(int start, int length) {
		OurList<A> tmp = new Liste<>();
		if(start > size || start == length || start > length){
			return tmp;
		} else if(length >= size){
			return this;
		}
		
		while(start <= (length-1)){
			tmp.add(this.get(start));
			start++;
		}
		return tmp;
	}
	
	/* Gibt an, an welchem Index ein bestimmtes Element liegt. Ist das Element
nicht enthalten, so wird -1 zurück gegeben. */
	public int indexOf(A el) {
		OurList<A> tmp = this;
		int i = 0;
		while(!tmp.isEmpty()) {
			if(tmp.head().equals(el)) {
				return i;
			}
			i++;
			tmp = tmp.tail();
		}
		return -1;
	}
	

	/* Gibt das Element an einem bestimmten Index zurück. Ist der Index zu
groß, so wird null zurück gegeben. */
	@Override
	public A get(int index) {
		if (this.isEmpty() || index < 0 || index > size) {
			return null;
		}
		if (index == 0) {
			return this.head;
		} else{
			return this.tail.get(index-1);
		}
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
	
	
	
	public static void main(String[] args) {
		OurList<String> li = new Liste<String>("H", new Liste<String>("A", new Liste<String>("L", new Liste<String>("L", new Liste<String>("O", new Liste<>())))));	
		System.out.println(li);
		
		OurList<String> li2 = new Liste<>();
		li2.add("W");
		li2.add("E");
		li2.add("L");
		li2.add("T");
		li2.add(".");
		li2.add(".");
		li2.add(".");
		System.out.println(li2);
		
		int li3 = li.length();
		System.out.println("Länge der 1. Liste: "+li3);
		
		int li4 = li2.length();
		System.out.println("Länge der 2. Liste: "+li4);
		
		System.out.println("Contains 'T': "+li2.contains("T"));
		System.out.println("Contains 'Z': "+li2.contains("Z"));
		System.out.println("Contains 'null': "+li.contains(""));
		
		System.out.println("IndexOf 'W': "+li2.indexOf("W"));
		System.out.println("IndexOf 'Z': "+li2.indexOf("Z"));
		System.out.println("IndexOf 'T': "+li2.indexOf("T"));
		System.out.println("IndexOf 'null': "+li.indexOf(""));
		System.out.println("IndexOf 'O': "+li.indexOf("O"));
		
		System.out.println("Get Index '0': "+li2.get(0));
		System.out.println("Get Index '-1': "+li2.get(-1));
		System.out.println("Get Index '3': "+li2.get(3));
		System.out.println("Get Index '10': "+li2.get(10));

		System.out.println("Sublist '0-2': "+li2.sublist(0,2));
		System.out.println("Sublist '3-5': "+li2.sublist(3,5));
		System.out.println("Sublist '3-15': "+li2.sublist(3,15));
		System.out.println("Sublist '4-2': "+li2.sublist(4,2));
		System.out.println("Sublist '2-8': "+li2.sublist(2,8));
		
		System.out.println("Take '4': "+li2.take(4));
		System.out.println("Take '8': "+li2.take(8));
		
		System.out.println("Drop '1': "+li2.drop(1));
		System.out.println("Drop '3': "+li2.drop(3));
		System.out.println("Drop '-1': "+li2.drop(-1));
		System.out.println("Drop '10': "+li2.drop(10));

	}

}
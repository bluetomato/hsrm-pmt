package ü1;



import java.util.Iterator;

public class Cons <E> implements Iterator<E>,Iterable <E>{
    
    E head;
    Iterable<E> tail;
    int count;
    
    Cons (Iterable<E> tail, E head){
        this.head = head;
        this.tail = tail;
        count = 0;
    }
    
    @Override
    public Iterator<E> iterator() {
        return this;
    }

    @Override
    public boolean hasNext() {
        if (count == 0){
            return true;
        }else{
            return this.tail.iterator().hasNext();
        }
        
    }

    @Override
    public E next() {
        if (count == 0){
            count++;
            return head;
        }else{
            return this.tail.iterator().next();
        }
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
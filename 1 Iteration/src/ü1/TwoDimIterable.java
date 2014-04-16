package ü1;
import java.util.Iterator;

public class TwoDimIterable <A,B> implements Iterator<Pair<A,B>>,Iterable<Pair<A,B>>{

    Iterable<A> it1;
    Iterable<B> it2;
    
    TwoDimIterable (Iterable<A> it1, Iterable <B> it2){
        this.it1=it1;
        this.it2 = it2;
    }
    @Override
    public boolean hasNext() {
        return it1.iterator().hasNext()&&it2.iterator().hasNext();
    }

    @Override
    public void remove() {
        System.out.println("NEIN!");
    }

    @Override
    public Pair<A, B> next() {
        return new Pair(it1.iterator().next(),it2.iterator().next());
    }

    @Override
    public Iterator<Pair<A, B>> iterator() {
        return this;
    }


    
}
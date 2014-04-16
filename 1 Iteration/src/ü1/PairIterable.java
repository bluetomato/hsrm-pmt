package ü1;
import java.util.Iterator;

public class PairIterable<A,B> implements Iterable<Pair<A,B>>,Iterator<Pair<A,B>>{
    
    Iterable<A> it1;
    Iterable<B> it2;
    
    public PairIterable(Iterable<A> it1,Iterable<B> it2){
        this.it1= it1;
        this.it2 = it2;
    }
    
    @Override
    public Iterator<Pair<A,B>> iterator() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public boolean hasNext() {
        return it1.iterator().hasNext()&&it2.iterator().hasNext();
        
    }

    @Override
    public Pair<A, B> next() {
        A result1 = it1.iterator().next();
        B result2 = it2.iterator().next();
        return new Pair<A,B>(result1,result2);
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
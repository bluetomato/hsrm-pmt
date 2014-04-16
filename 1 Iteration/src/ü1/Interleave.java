package ü1;
import java.util.Iterator;

public class Interleave<A> implements Iterable<A>,Iterator<A>{

    Iterable<A> it1,it2;
    int count;
    
    Interleave(Iterable<A> it1, Iterable<A> it2){
        this.it1=it1;
        this.it2=it2;
        this.count = 1;
    }
    
    @Override
    public Iterator<A> iterator() {
        return this;
    }

    @Override
    public boolean hasNext() {
        return it1.iterator().hasNext()&&it2.iterator().hasNext();
    }

    @Override
    public A next() {
        if (this.count%2!=0){
            count++;
            return it1.iterator().next();
        }else{
            count++;
            return it2.iterator().next();
        }
    }

    @Override
    public void remove() {
       System.out.println("NEIN!NEIN!NEIN!");
    }
    
}
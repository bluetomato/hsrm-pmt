package ü1;
import java.util.Iterator;

public class IntRange implements Iterable<Integer>,Iterator<Integer>{
    
    int currentNumber;
    int limit;
    int steps;
    

    IntRange (int from,int to,int steps){
        this.currentNumber = from;
        this.limit = to;
        this.steps =steps;
    }
    
    IntRange (int from,int to){
        this (from,to,1);
    }
    
    IntRange (int from){
        this (from,25000000);
    }
    
    IntRange(){
        this(0);
    }
    
    @Override
    public Iterator iterator() {
        return this;
    }

    @Override
    public boolean hasNext() {
        return this.currentNumber<=this.limit;
    }

    @Override
    public Integer next() {
        int result= currentNumber;
        this.currentNumber = this.currentNumber + this.steps;
        return result;
    }

    @Override
    public void remove() {
        
    }
    
}
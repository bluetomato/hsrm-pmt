package ü1;
import java.util.Iterator;

public class Random implements Iterable <Integer>, Iterator <Integer>{
    
    Integer m,a,b,y1;
    Integer lastNumber;
    Integer count;
    
    Random (int m,int a, int b , int y1){
        this.m = m;
        this.a = a;
        this.b = b;
        this.y1 = y1;
        this.lastNumber = y1;
        this.count = 0;
    }
    
    @Override
    public Iterator<Integer> iterator() {
        return this;
    }

    @Override
    public boolean hasNext() {
        return true;
    }

    @Override
    public Integer next() {
        if (this.count == 0){
            this.count++;
            return y1;          
        }else{
            int result = (this.a*this.lastNumber+this.b)%m;
            this.lastNumber = result;
            this.count++;
            return result;
        }
    }

    @Override
    public void remove() {
        
    }
    
}
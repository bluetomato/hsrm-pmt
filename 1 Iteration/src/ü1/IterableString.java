package ü1;

import java.util.Iterator;

public class IterableString  implements Iterable<Character>,Iterator<Character>{
    
    String string;
    int counter;
    public IterableString(String string){
        this.string=string;
        this.counter = 0;
    }
    
    @Override
    public Iterator<Character> iterator() {
        return this;
    }

    @Override
    public boolean hasNext() {
        return this.counter < this.string.length();
    }

    @Override
    public Character next() {
        Character result = this.string.charAt(counter);
        counter++;
        return result;
    }

    @Override
    public void remove() {
        
    }
    
}
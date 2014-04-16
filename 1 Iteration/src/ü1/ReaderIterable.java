package ü1;
import java.io.IOException;
import java.io.Reader;
import java.util.Iterator;


public class ReaderIterable implements Iterable<Character>,Iterator<Character>{
    Reader reader;
    int readed;
    int count;
    ReaderIterable (Reader r){
        this.reader = r;
        this.count=0;
    }
    
    @Override
    public Iterator<Character> iterator() {
        if (count == 0){
            count++; 
            return this;
        }else{
            throw new RuntimeException("Fehler");
        }

    }

    @Override
    public boolean hasNext() {
        try {
            
            this.readed = reader.read();
            return this.readed >= 0;
        } catch (IOException ex) {
            return false;
        }
    }

    @Override
    public Character next() {
        try {
            int i = reader.read();
            return (char) i;
        } catch (IOException ex) {
            return 'a';
        }
        
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
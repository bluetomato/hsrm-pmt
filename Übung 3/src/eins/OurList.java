package eins;
import java.util.function.Consumer;
public interface OurList<A> extends Iterable<A> {
    boolean isEmpty();
    A head();
    OurList<A> tail();

    int length();
    boolean contains(A el);
    void machtAlle(Consumer<A> c);
    OurList<A> add(A el);
 
    OurList<A> drop(int i);
    OurList<A> take(int i);
    OurList<A> sublist(int start, int length);
    int indexOf(A el);
    A get(int index);

}


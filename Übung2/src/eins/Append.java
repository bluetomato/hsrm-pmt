package eins;

import java.util.Iterator;


public class Append<E> implements Iterable<E> {

    Iterable<E> xs;
    Iterable<E> ys;

    public Append(Iterable<E> xs, Iterable<E> ys) {
      this.xs = xs;
      this.ys = ys;
    }

  @Override
  public Iterator<E> iterator() {
    return new MyIt();
  }

  public class MyIt implements Iterator<E> {

    Iterator<E> xsIt = xs.iterator();
    Iterator<E> ysIt = ys.iterator();

    @Override
    public boolean hasNext() {
      return xsIt.hasNext() || ysIt.hasNext();
    }

    @Override
    public E next() {
      if (xsIt.hasNext()) return xsIt.next();
      return ysIt.next();
    }

    @Override public void remove() {}
  }
}


public abstract class AbstractIterator<A> implements java.util.Iterator<A> {

  public abstract boolean schleifenTest();
  public abstract void schleifeWeiterschalten();
  public abstract A schleifenWert();

  public A next(){
    A result = schleifenWert();
    schleifeWeiterschalten();
    return result;
  }

  public boolean hasNext(){
    return schleifenTest();
  }

  public void remove(){
    throw new UnsupportedOperationException();
  }
}


import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class AppendTest{
  public static void main(String[] args) {
    for (int i:new Append<>(new IntegerRange(1,15),new IntegerRange(47,52))){
      System.out.println(i);
    }

    List<String> xs = new LinkedList<>();
    xs.add("Freunde");
    xs.add("Roemer");
    xs.add("Landsleute");

    List<String> ys = new ArrayList<>();
    ys.add("leiht");
    ys.add("mir");
    ys.add("Euer");
    ys.add("Ohr");

    for (String s:new Append<>(xs,ys)){
      System.out.println(s.toUpperCase());
    }
  }
}


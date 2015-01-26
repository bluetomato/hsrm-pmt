
public class Test {
	public static void main(String[] args) throws Exception{
		Agenda testKalender = new Agenda();
		testKalender.addEntry("2014-05-27 15:00:00.0", 30, "Test 1", "Ort 1");
		testKalender.addEntry("2014-05-28 16:00:00.0", 90, "Test 2", "Ort 2");
		testKalender.addEntry("2014-05-29 17:00:00.0", 180, "Test 3", "Ort 3");
		testKalender.addEntry("2014-05-30 18:00:00.0", 240, "Test 4", "Ort 4");
		
		testKalender.writeToXML("testKalender.xml");
		testKalender.readFromXML("testKalender.xml");
		Agenda testKalender1 = new Agenda();
		testKalender1.readFromXML("testKalender.xml");
		System.out.println(testKalender1);
	}
}

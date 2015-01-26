import java.time.DayOfWeek;
import java.time.Instant;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.time.Month;
import java.time.Period;
import java.time.Year;
import java.time.ZoneId;
import java.time.ZoneOffset;
import java.time.ZonedDateTime;
import java.time.temporal.ChronoUnit;
import java.util.TimeZone;


public class test {
	public void greetingDemo(Instant instant, ZoneId zoneId) { 
		LocalTime localTime = instant.atZone(zoneId).toLocalTime(); 
		if (localTime.isBefore(LocalTime.parse("09:00"))) { 
			System.out.println("Guten Morgen!"); 
		} else if (localTime.isBefore(LocalTime.parse("17:00"))) { 
			System.out.println("Guten Tag!"); 
		} else { 
			System.out.println("Guten Abend!"); 
		} 
	}

	public static void main(String[] args) {
		//geburtstag
		LocalDate myBirthday = LocalDate.of(1989, Month.SEPTEMBER, 27);
		System.out.println(myBirthday);
		
		//an welchem wochentag bin ich geboren?
		DayOfWeek day = myBirthday.getDayOfWeek();
		System.out.println(day);
		
		//war das jahr ein schaltjahr?
		boolean LeapYear = Year.of(myBirthday.getYear()).isLeap();
		System.out.println("Dein Geburtsjahr " + myBirthday.getYear() + " ist " + (LeapYear ? "ein ":"kein ") + "Schaltjahr.");
		
		//wie alt bin ich jetzt in tagen/stunden/minuten/nanosekunden?
		LocalDate today = LocalDate.now();
		Period period = Period.between(myBirthday, today);
		long periodDays = ChronoUnit.DAYS.between(myBirthday, today);
		long periodWeeks = ChronoUnit.WEEKS.between(myBirthday, today);
		System.out.println("Du bist heute " + period.getYears() + " Jahre, " + period.getMonths() + " Monate und " + period.getDays() + " Tage alt.");
		System.out.println("Das sind " + periodDays + " Tage.");
		System.out.println("Das sind " + periodWeeks + " Wochen.");
		
		//in wieviel tagen ist mein nächster geburtstag?
		LocalDate nextBirthday = myBirthday.withYear(today.getYear());
		if(nextBirthday.isBefore(today) || nextBirthday.isBefore(today)){
			nextBirthday = nextBirthday.plusYears(1);
		}
		period = Period.between(today, nextBirthday);
		System.out.println("Bis zu deinem Geburtstag sind es noch " + period.getMonths() + " Monate und " + period.getDays() + " Tage.");
		periodDays = ChronoUnit.DAYS.between(today, nextBirthday);
		System.out.println("Das sind " + periodDays + " Tage.");
		
		//bin ich älter als meine freudin? wenn ja, wieviel.
		LocalDate friendsBirthday = LocalDate.of(1985, Month.JUNE, 6);
		boolean amIolder = myBirthday.isBefore(friendsBirthday);
		System.out.println("Ich habe am "+ myBirthday + " Geburtstag und bin somit " + (amIolder ? "älter" : "jünger") + ", als mein am " + friendsBirthday + " geborener Freund.");
		
		//ich möchte meine freundin um 24 uhr in sydney anrufen (zum geburtstag gratulieren)
		LocalDate friendsBirthdaySydney = LocalDate.of(1990, Month.JUNE, 3);
		System.out.println("Geburtstag meiner Freundin in Sydney am: " + friendsBirthdaySydney);
		
		//zeit und datum bei freundin in sydney
		ZonedDateTime todaySydney = ZonedDateTime.of(LocalDateTime.now(), ZoneId.of("Australia/Sydney"));
		System.out.println("Gerade in Sydney: " + todaySydney);
		
		/*
		LocalDateTime now= LocalDateTime.now( ); 
		System.out.println("now: " + now);
		// Aktuelles Datum LocalDate.of(2013, Month.DECEMBER, 24);
		System.out.println(LocalTime.of(14, 00)); 
		System.out.println(LocalTime.parse("10:15:30"));
		
		LocalDate theDate = now.toLocalDate(); 
		System.out.println("thedate: " + now.getDayOfYear());
		//Month month = timePoint.getMonth();
		//Da immutable, immer neue Instanzen erzeugt
		LocalDateTime before = now.withYear(2013);
		System.out.println(before);
		//LocalDateTime soon = new.plusWeeks(1);
		//LocalDateTime wednesday = now.with(TemporalAdjusters.previousOrSame(ChronoUnit.WEDNESDAY));
		LocalDateTime truncatedTime = now.truncatedTo(ChronoUnit.DAYS);
		System.out.println(truncatedTime);
		
		ZoneId id = ZoneId.of("Europe/Berlin");
		ZonedDateTime zoned = ZonedDateTime.of(LocalDateTime.now(), id);
		System.out.println(zoned);*/
	}

}

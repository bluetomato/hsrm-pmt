import java.sql.Timestamp;
import java.time.*;

/**
 * 
 * @author Stephanie Scholl & Alexander Koch
 *
 */
public class CalEntry{
	private LocalDateTime start;
	private Duration duration;
	private String description;
	private String location;
	
	public CalEntry(LocalDateTime start, Duration duration, String description, String location){
		super();
		this.start = start;
		this.duration = duration;
		this.description = description;
		this.location = location;
	}
	
	public String toString(){
		return "---------------------\nTermin\nBeschreibung: "+description+"\nOrt: "+location+"\nStart: "+Timestamp.valueOf(start)+"\nDauer: "+(int)(duration.toMinutes()/60)+"Std, "+duration.toMinutes()%60+"min\n---------------------\n";
	}
	
	public LocalDateTime getStart(){
		return start;
	}
	
	public Duration getDuration(){
		return duration;
	}
	
	public String getDescription(){
		return description;
	}
	
	public String getLocation(){
		return location;
	}
}

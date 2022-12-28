package 객지프_팀플4;


import java.time.LocalDate;
import java.time.Period;

public class Assignment {
	private String subjectName;
	private String title;
	private int endDate;
	private int priority;
	private int difficulty;
	private String memo;

	//getter
	public String getSubjectName() {
		return this.subjectName;
	}
	
	public String getTitle() {
		return this.title;
	}
	
	public int endDate() {
		return this.endDate;
	}
	
	public int getDDay() {
		LocalDate today = LocalDate.now();
		LocalDate thisDay = LocalDate.of(2022,this.endDate/100,this.endDate%100);
		Period between = Period.between(today, thisDay);
		return between.getDays();
	}
	
	public int getPriority() {
		return this.priority;
	}
	
	public int getDifficulty() {
		return this.difficulty;
	}
	
	public String getMemo() {
		return this.memo;
	}
	
	Assignment(String subject, String title, int enddate, int priority, int difficulty, String memo) {
		this.subjectName = subject;
		this.title = title;
		this.endDate = enddate;
		this.priority = priority;
		this.difficulty = difficulty;
		this.memo = memo;
	}
}